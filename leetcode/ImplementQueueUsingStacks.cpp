#include <stack>

using namespace std;

//https://leetcode.com/problems/implement-queue-using-stacks/
/*
232. Implement Queue using Stacks

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Notes:
You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).

Observation:
Classic interview question.
2 stacks are necessary. The first one used for taking new elements, the second one for top() and pop(), which
means the elements in the second stacks are in the order of FIFO.

This is achieved by poping elements from stack 1 and push them into stack 2. This only occurs if stack 2
is empty. So, overall time complexity is still close to O(1).

As for push(), it's O(1) and always hits stack 1
*/
class ImplementQueueUsingStacks {
private:
	stack<int> s1;
	stack<int> s2;
	void move()
	{
		if (true == s2.empty())
		{
			while (false == s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
	}
public:
	// Push element x to the back of queue.
	void push(int x) {
		s1.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		//if(this.empty() == true)return;
		this->move();
		s2.pop();
	}

	// Get the front element.
	int peek(void) {
		this->move();
		return s2.top();
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return s1.empty() && s2.empty();
	}
};