#include <stack>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/min-stack/
/*
155. Min Stack

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

- push(x) -- Push element x onto stack.
- pop() -- Removes the element on top of the stack.
- top() -- Get the top element.
- getMin() -- Retrieve the minimum element in the stack.

Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

Observation:
Push, pop and top are O(1) on stack already. The question is how getMin can be done in O(1).

What if we track current min from the bottom of the stack to current level? This indicates the min
among values that remain on the stack. Maintaining this can be done in O(1). Since we know the min at top,
when a new element is added, simply comparing its value with the min on top.
*/
class MinStack {
private:
	stack<std::pair<int, int> > stk;
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		if (true == this->stk.empty())this->stk.emplace(std::make_pair(x, x));
		else this->stk.emplace(std::make_pair(x, std::min(x, this->stk.top().second)));
	}

	void pop() {
		if (false == this->stk.empty())this->stk.pop();
	}

	int top() {
		return this->stk.top().first;
	}

	int getMin() {
		return this->stk.top().second;
	}
};

/**
* Your MinStack object will be instantiated and called as such:
* MinStack obj = new MinStack();
* obj.push(x);
* obj.pop();
* int param_3 = obj.top();
* int param_4 = obj.getMin();
*/