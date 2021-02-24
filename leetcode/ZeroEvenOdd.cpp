#include <mutex>
#include <condition_variable>

using namespace std;

//https://leetcode.com/problems/print-zero-even-odd/
/*
1116. Print Zero Even Odd

Suppose you are given the following code:

class ZeroEvenOdd {
  public ZeroEvenOdd(int n) { ... }      // constructor
  public void zero(printNumber) { ... }  // only output 0's
  public void even(printNumber) { ... }  // only output even numbers
  public void odd(printNumber) { ... }   // only output odd numbers
}

The same instance of ZeroEvenOdd will be passed to three different threads:

Thread A will call zero() which should only output 0's.

Thread B will call even() which should only ouput even numbers.

Thread C will call odd() which should only output odd numbers.

Each of the threads is given a printNumber method to output an integer. Modify the given program to output the series 010203040506... where the length of the series must be 2n.



Example 1:

Input: n = 2

Output: "0102"

Explanation: There are three threads being fired asynchronously. One of them calls zero(), the other calls even(), and the last one calls odd(). "0102" is the correct output.

Example 2:

Input: n = 5

Output: "0102030405"

Observations:

This is a three threads synchronization if one doesn't take the shortcut, which considering 0 as the prefix of any printed numbers.

Semaphore would be my first choice for this, however it's a C++20 feature and it's not supported by my environment...

The second option is mutex/condition_variable. I have seen most of implementation using only 1 lock. However, some of them are based upon the assumption that waiting thread can
pick up the lock before the thread zero regain the lock (in those impl and mine, the for loop in zero controls the value for printing), which is wrong. Since the lock in zero is in a
for loop, it's possible zero may regain the lock before other threads wake up. In that case, other threads will have to keep waiting until the lock can be acquired, See ZeroEvenOdd2.

****Update on 2-24-2021****
The statement above is actually wrong. My colleague (https://github.com/kjmcclain) pointed out the second lock/condition is not necessary since the first lock/condition can be reused,
if we have to something like ZeroEvenOdd2. See ZeroEvenOdd for the revised version. Also, he indicated that the unique_lock can be moved out of the for loop since wait will
unlock the lock automatically. Combining these two points, ZeroEvenOdd looks much better if it still can be as fancy as ZeroEvenOdd1.


A smarter way to do this, if only needs one mutex is run numbers (for loop) independently in all three threads. The condtion for waking up is changed accordingly. See ZeroEvenOdd1 I copied from someone on leetcode.


One more thing to point out is: unique_lock will automatically lock on the mutex unless std::defer is given. It will also automatically unlock the mutex while it's out of the scope.
*/
class ZeroEvenOdd {
private:
	int n;
	int nextValue;
	bool next;
	bool hasValue;
	mutex mutex1;
	condition_variable condition1;
public:
	ZeroEvenOdd(int n) : mutex1(), condition1() {
		this->n = n;
		this->next = false;
		this->hasValue = false;
		this->nextValue = 0;
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(function<void(int)> printNumber) {
		unique_lock<mutex> lck1(this->mutex1);
		for (int i = 1; i <= this->n + 1; ++i) {
			if (i <= n)
				printNumber(0);
			this->nextValue = i;
			this->hasValue = true;
			this->condition1.notify_all();
			if (i <= n) {
				this->next = false;
				this->condition1.wait(lck1, [this]() -> bool { return this->next; });
			}
		}
	}

	void print(function<void(int)> printNumber, function<bool()> predicate) {
		unique_lock<mutex> lck1(mutex1);
		while (true) {
			this->condition1.wait(lck1, [&]() -> bool { return this->hasValue == true && (predicate() == true || this->nextValue > this->n); });
			if (this->nextValue > this->n)
				break;
			printNumber(this->nextValue);
			this->hasValue = false;
			this->next = true;
			this->condition1.notify_all();
		}
	}

	void even(function<void(int)> printNumber) {
		this->print(printNumber, [this]() -> bool { return (this->nextValue & 1) == 0; });
	}

	void odd(function<void(int)> printNumber) {
		this->print(printNumber, [this]() -> bool { return (this->nextValue & 1) == 1; });
	}
};
class ZeroEvenOdd1 {
private:
	int n;
	std::mutex mut;
	std::condition_variable cond;
	int count;

public:
	ZeroEvenOdd1(int n) : count(0) {
		this->n = n;
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(function<void(int)> printNumber) {
		for (int i = 0; i < n; i++)
		{
			unique_lock<mutex> lock(mut);
			cond.wait(lock, [this] {return count % 2 == 0; });
			printNumber(0);
			count++;
			lock.unlock();
			cond.notify_all();
		}
	}

	void even(function<void(int)> printNumber) {
		for (int i = 2; i <= n; i = i + 2)
		{
			unique_lock<mutex> lock(mut);
			cond.wait(lock, [this] {return count % 4 == 3; });
			printNumber(i);
			count++;
			lock.unlock();
			cond.notify_all();
		}
	}

	void odd(function<void(int)> printNumber) {
		for (int i = 1; i <= n; i = i + 2)
		{
			unique_lock<mutex> lock(mut);
			cond.wait(lock, [this] {return count % 4 == 1; });
			printNumber(i);
			count++;
			lock.unlock();
			cond.notify_all();
		}
	}
};
class ZeroEvenOdd2 {
private:
	int n;
	int nextValue;
	bool next;
	bool hasValue;
	mutex mutex1;
	mutex mutex2;
	condition_variable condition1;
	condition_variable condition2;
public:
	ZeroEvenOdd2(int n) : mutex1(),
		mutex2(),
		condition1(),
		condition2()
	{
		this->n = n;
		this->next = false;
		this->hasValue = false;
		this->nextValue = 0;
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(function<void(int)> printNumber) {
		unique_lock<mutex> lck1(this->mutex1, std::defer_lock);
		for (int i = 1; i <= this->n + 1; ++i) {
			if (i <= n)
				printNumber(0);
			lck1.lock();
			this->nextValue = i;
			this->hasValue = true;
			this->condition1.notify_all();
			lck1.unlock();
			if (i <= n) {
				unique_lock<mutex> lck2(this->mutex2);
				this->next = false;
				this->condition2.wait(lck2, [this]() -> bool { return this->next; });
			}
		}
	}

	void print(function<void(int)> printNumber, function<bool()> predicate) {
		unique_lock<mutex> lck1(mutex1);
		while (true) {
			this->condition1.wait(lck1, [&]() -> bool { return this->hasValue == true && (predicate() == true || this->nextValue > this->n); });
			if (this->nextValue > this->n)
				break;
			printNumber(this->nextValue);
			this->hasValue = false;
			unique_lock<mutex> lck2(this->mutex2);
			this->next = true;
			this->condition2.notify_all();
		}
	}

	void even(function<void(int)> printNumber) {
		this->print(printNumber, [this]() -> bool { return (this->nextValue & 1) == 0; });
	}

	void odd(function<void(int)> printNumber) {
		this->print(printNumber, [this]() -> bool { return (this->nextValue & 1) == 1; });
	}
};
/*
Test cases:

0
1
2
3
4
5

Outputs:

""
"01"
"0102"
"010203"
"01020304"
"0102030405"
*/