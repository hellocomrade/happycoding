#include <mutex>
#include <functional>
#include <condition_variable>

using namespace std;

//https://leetcode.com/problems/fizz-buzz-multithreaded/
/*
1195. Fizz Buzz Multithreaded

You have the four functions:

printFizz that prints the word "Fizz" to the console,

printBuzz that prints the word "Buzz" to the console,

printFizzBuzz that prints the word "FizzBuzz" to the console, and

printNumber that prints a given integer to the console.

You are given an instance of the class FizzBuzz that has four functions: fizz, buzz, fizzbuzz and number. The same instance of FizzBuzz will be passed to four different threads:

Thread A: calls fizz() that should output the word "Fizz".

Thread B: calls buzz() that should output the word "Buzz".

Thread C: calls fizzbuzz() that should output the word "FizzBuzz".

Thread D: calls number() that should only output the integers.

Modify the given class to output the series [1, 2, "Fizz", 4, "Buzz", ...] where the ith token (1-indexed) of the series is:

"FizzBuzz" if i is divisible by 3 and 5,

"Fizz" if i is divisible by 3 and not 5,

"Buzz" if i is divisible by 5 and not 3, or

i if i is not divisible by 3 or 5.

Implement the FizzBuzz class:

- FizzBuzz(int n) Initializes the object with the number n that represents the length of the sequence that should be printed.
- void fizz(printFizz) Calls printFizz to output "Fizz".
- void buzz(printBuzz) Calls printBuzz to output "Buzz".
- void fizzbuzz(printFizzBuzz) Calls printFizzBuzz to output "FizzBuzz".
- void number(printNumber) Calls printnumber to output the numbers.


Example 1:

Input: n = 15

Output: [1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz",13,14,"fizzbuzz"]

Example 2:

Input: n = 5

Output: [1,2,"fizz",4,"buzz"]


Constraints:

- 1 <= n <= 50

Observations:

The only hurdle of this straightforward problem is to understand that each thread will only calls the corresponding functions once. Therefore, one
must implement the loop to maintain the print till greater than n.
*/
class FizzBuzz {
private:
	int n;
	int i;
	mutex mtx;
	condition_variable cv;

	void process(const function<void()>& callback, const function<bool()>& predicate) {
		while (i <= n) {
			unique_lock<mutex> lck(mtx);
			cv.wait(lck, [this, &predicate]() -> bool { return this->i > this->n || predicate(); });
			cv.notify_all();
			if (i > n)
				break;
			callback();
			++i;
		}
	}
public:
	FizzBuzz(int n) : i(1), mtx(), cv() {
		this->n = n;
	}

	// printFizz() outputs "fizz".
	void fizz(function<void()> printFizz) {
		process(printFizz, [this]() -> bool { return this->i % 3 == 0 && this->i % 5 != 0; });
	}

	// printBuzz() outputs "buzz".
	void buzz(function<void()> printBuzz) {
		process(printBuzz, [this]() -> bool { return this->i % 3 != 0 && this->i % 5 == 0; });
	}

	// printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
		process(printFizzBuzz, [this]() -> bool { return this->i % 3 == 0 && this->i % 5 == 0; });
	}

	// printNumber(x) outputs "x", where x is an integer.
	void number(function<void(int)> printNumber) {
		process([this, &printNumber]() -> void { printNumber(this->i); }, [this]() -> bool { return this->i % 3 != 0 && this->i % 5 != 0; });
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
11
12
13
14
15

Outputs:

[1]
[1,2]
[1,2,"fizz"]
[1,2,"fizz",4]
[1,2,"fizz",4,"buzz"]
[1,2,"fizz",4,"buzz","fizz"]
[1,2,"fizz",4,"buzz","fizz",7]
[1,2,"fizz",4,"buzz","fizz",7,8]
[1,2,"fizz",4,"buzz","fizz",7,8,"fizz"]
[1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz"]
[1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11]
[1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz"]
[1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz",13]
[1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz",13,14]
[1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz",13,14,"fizzbuzz"]
*/