#include <future>
#include <atomic>
#include <chrono>

using namespace std;

//https://leetcode.com/problems/print-in-order/
/*
1114. Print in Order

Suppose we have a class:

public class Foo {
  public void first() { print("first"); }
  public void second() { print("second"); }
  public void third() { print("third"); }
}
The same instance of Foo will be passed to three different threads. Thread A will call first(), thread B will call second(), and thread C will call third().
Design a mechanism and modify the program to ensure that second() is executed after first(), and third() is executed after second().



Example 1:

Input: [1,2,3]
Output: "firstsecondthird"
Explanation: There are three threads being fired asynchronously. The input [1,2,3] means thread A calls first(), thread B calls second(), and thread C calls third().
"firstsecondthird" is the correct output.

Example 2:

Input: [1,3,2]
Output: "firstsecondthird"
Explanation: The input [1,3,2] means thread A calls first(), thread B calls third(), and thread C calls second(). "firstsecondthird" is the correct output.


Note:

We do not know how the threads will be scheduled in the operating system, even though the numbers in the input seems to imply the ordering.
The input format you see is mainly to ensure our tests' comprehensiveness.

Observations:

Foo1 is one may do if drunk :) Yes, you can get this done using whatever synchronization means might work here. Foo1 is one of the most dummiest one by pulling. It's interesting
to see that if one is gentle with leetcode ang assigns a longer waiting period in sleep_for, say 100 ms, TLE will be rewarded by leetcode... Therefore, just pulling hard :)

Foo is a new discovery for me. I didn't know C++ supports promise-like style, even though it's availabale since C++11... The way it works here though is more likely to be Java's CompletableFuture
than the traditional promise in Javascript. The barrier is actually the Future object.

- The promise object is the asynchronous provider and is expected to set a value for the shared state at some point.
- The future object is an asynchronous return object that can retrieve the value of the shared state, waiting for it to be ready, if necessary.

Obviously, Promise and Future shall be used by different threads. One for setter, the other is for getter.
*/
class Foo {
private:
	promise<void> barrier1;
	promise<void> barrier2;
public:
	Foo() {

	}

	void first(function<void()> printFirst) {
		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		barrier1.set_value();
	}

	void second(function<void()> printSecond) {
		barrier1.get_future().get();
		// printSecond() outputs "second". Do not change or remove this line.
		printSecond();
		barrier2.set_value();
	}

	void third(function<void()> printThird) {
		barrier2.get_future().get();
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
	}
};
class Foo1 {
private:
	std::atomic<int> order;
public:
	Foo1(): order(1) {

	}

	void first(function<void()> printFirst) {
		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		order += 1;
	}

	void second(function<void()> printSecond) {
		while (order != 2)
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		// printSecond() outputs "second". Do not change or remove this line.
		printSecond();
		order += 1;
	}

	void third(function<void()> printThird) {
		while (order != 3)
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
	}
};