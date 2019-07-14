#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

//https://leetcode.com/problems/print-foobar-alternately/
/*
1115. Print FooBar Alternately

Suppose you are given the following code:

class FooBar {
  public void foo() {
	for (int i = 0; i < n; i++) {
	  print("foo");
	}
  }

  public void bar() {
	for (int i = 0; i < n; i++) {
	  print("bar");
	}
  }
}

The same instance of FooBar will be passed to two different threads. Thread A will call foo() while thread B will call bar().
Modify the given program to output "foobar" n times.

Example 1:

Input: n = 1

Output: "foobar"

Explanation: There are two threads being fired asynchronously. One of them calls foo(), while the other calls bar(). "foobar" is being output 1 time.

Example 2:

Input: n = 2

Output: "foobarfoobar"

Explanation: "foobar" is being output 2 times.

Observations:

This is a new section on leetcode: Concurrency. I am not sure if this is OJ is a good way to test concurrency considering the
fact that thread execution is "unpredictable" at OJ level so accepted submission could be faulty. For example, the following
submission: https://leetcode.com/problems/print-foobar-alternately/discuss/334071/C%2B%2B-mutex-solution.

class FooBar {
private:
	int n;
	mutex m1, m2;
public:
	FooBar(int n) {
		this->n = n;
		m1.lock();
		m2.lock();
	}

	void foo(function<void()> printFoo) {
		m1.unlock();
		for (int i = 0; i < n; i++) {
			m1.lock();
			// printFoo() outputs "foo". Do not change or remove this line.
			printFoo();
			m2.unlock();
		}
	}

	void bar(function<void()> printBar) {
		for (int i = 0; i < n; i++) {
			m2.lock();
			// printBar() outputs "bar". Do not change or remove this line.
			printBar();
			m1.unlock();
		}
	}
};

It uses two mutex locks to synchronize thread operation. Pretty smart idea, but it doesn't really work at least for POSIX. Why?
According to pthread doc, mutex shall always be locked and unlocked by the same thread. Otherwise, the result is undefined...

leetcode "thinks" this is an accepted solution coz it only checeks the output, which could be correct for an execution. But,
the code itself is faulty!

The correct solution in pthread world using C/C++ is condition variable, pthread_cond_wait(3) and it is always companied
by pthread_mutex_lock(3), an example may look like:

pthread_mutex_t count_lock;
pthread_cond_t count_nonzero;
unsigned count;

decrement_count()
{
	pthread_mutex_lock(&count_lock);
	while (count == 0)
		pthread_cond_wait(&count_nonzero, &count_lock);
	count = count - 1;
	pthread_mutex_unlock(&count_lock);
}

increment_count()
{
	pthread_mutex_lock(&count_lock);
	if (count == 0)
		pthread_cond_signal(&count_nonzero);
	count = count + 1;
	pthread_mutex_unlock(&count_lock);
}

thread must acquire the lock on the mutex first, then if pthread_cond_wait is called since the shared condition the thread is waiting on
is not met, pthread_cond_wait will block the thread and unlock on the mutex so other threads may have the opportunity to
execute and potentially update the shared condition current thread is waiting for. pthread_cond_wait atomically releases the associated mutex lock before blocking,
and atomically acquires it again before returning.

In typical use, a condition expression is evaluated under the protection of a mutex lock. When the condition expression is false, the thread blocks on the condition variable.
The condition variable is then signaled by another thread when it changes the condition value. This causes one or all of the threads waiting on the condition to unblock and to try to acquire the mutex lock again.

Because the condition can change before an awakened thread returns from pthread_cond_wait(), the condition that caused the wait must be retested before the mutex lock is acquired.
The recommended test method is to write the condition check as a while() loop that calls.

Once the condition is met, waiting threads are waken up, racing for mutex lock, then the winner has the opportunity to update the shared condition.

On the other hand, the waiting threads can be waken up using pthread_cond_signal(3) or pthread_cond_broadcast(3). Call pthread_cond_signal() under the protection of the same mutex used with the condition variable being signaled.
Otherwise, the condition variable could be signaled between the test of the associated condition and blocking in pthread_cond_wait(), which can cause an infinite wait.

OK, enough introduction in pthread domain. How about C++ STD?

https://en.cppreference.com/w/cpp/thread/condition_variable

C++ has <mutex>, <condition_variable>

The condition_variable class is a synchronization primitive that can be used to block a thread, or multiple threads at the same time,
until another thread both modifies a shared variable (the condition), and notifies the condition_variable.

The thread that intends to modify the variable has to:

1. Acquire a std::mutex (typically via std::lock_guard)
2. Perform the modification while the lock is held
3. Execute notify_one or notify_all on the std::condition_variable (the lock does not need to be held for notification)

Even if the shared variable is atomic, it must be modified under the mutex in order to correctly publish the modification to the waiting thread.

Any thread that intends to wait on std::condition_variable has to:

1. Acquire a std::unique_lock<std::mutex>, on the same mutex as used to protect the shared variable
2. Execute wait, wait_for, or wait_until. The wait operations atomically release the mutex and suspend the execution of the thread.
3. When the condition variable is notified, a timeout expires, or a spurious wakeup occurs, the thread is awakened, and the mutex is atomically reacquired.
   The thread should then check the condition and resume waiting if the wake up was spurious.

std::condition_variable works only with std::unique_lock<std::mutex>; this restriction allows for maximal efficiency on some platforms.
std::condition_variable_any provides a condition variable that works with any BasicLockable object, such as std::shared_lock.

Condition variables permit concurrent invocation of the wait, wait_for, wait_until, notify_one and notify_all member functions.

Finally, let's talk about this problem: in order to output "foo" "bar" in that order, both threads will wait on the shared condition
and both will execute if the turn is on then notify the status change for the other thread. In this regard, they both have to:

1. Acquire a std::unique_lock<std::mutex>, on the same mutex as used to protect the shared variable
2. Execute wait. The wait operations atomically release the mutex and suspend the execution of the thread.
3. When the condition variable is notified by the other thread, the thread is awakened, and the mutex is atomically reacquired.
   The thread will then check the condition and resume waiting if the wake up was spurious. Or print its token, update the shared condition,
   then notify the other thread for execution.

In terms of implementation, classic while loop wrapping wait works or condition_variable's wait also accept a lambda function.
It's a predicte to tell if the thread should be waken.
*/
class PrintFooBarAlternately {
private:
	int n;
	bool isFoo;
	std::mutex mtx;
	std::condition_variable cv;
public:
	PrintFooBarAlternately(int n) : isFoo(true) {
		this->n = n;
	}

	void foo(function<void()> printFoo) {
		std::unique_lock<std::mutex> lock(mtx);
		for (int i = 0; i < n; i++) {
			//while (false == isFoo) cv.wait(lock);
			cv.wait(lock, [this]()->bool {return true == isFoo; });
			// printFoo() outputs "foo". Do not change or remove this line.
			printFoo();
			isFoo = false;
			cv.notify_one();
		}
	}

	void bar(function<void()> printBar) {
		std::unique_lock<std::mutex> lock(mtx);
		for (int i = 0; i < n; i++) {
			//while (true == isFoo) cv.wait(lock);
			cv.wait(lock, [this]()->bool {return false == isFoo; });
			// printBar() outputs "bar". Do not change or remove this line.
			printBar();
			isFoo = true;
			cv.notify_one();
		}
	}
};
/*
Test cases:

1
2
3
4
5
6
7
8
9
10

Outputs:

"foobar"
"foobarfoobar"
"foobarfoobarfoobar"
"foobarfoobarfoobarfoobar"
"foobarfoobarfoobarfoobarfoobar"
"foobarfoobarfoobarfoobarfoobarfoobar"
"foobarfoobarfoobarfoobarfoobarfoobarfoobar"
"foobarfoobarfoobarfoobarfoobarfoobarfoobarfoobar"
"foobarfoobarfoobarfoobarfoobarfoobarfoobarfoobarfoobar"
"foobarfoobarfoobarfoobarfoobarfoobarfoobarfoobarfoobarfoobar"
*/