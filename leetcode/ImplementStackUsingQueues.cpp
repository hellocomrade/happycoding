#include <queue>

using namespace std;

//https://leetcode.com/problems/implement-stack-using-queues/
/*
225. Implement Stack using Queues

Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Notes:
You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).

Observations:
This can be compared with Implement Queue using Stack.

Again, two queues are needed. The difference comparing with "Implement Queue using Stack" is that all nasty work are done
in push. Here is the deal:

Both queues are taking push() one after another. After push is done on one queue, the elements stored in the other queue,
which is considered as previous result in FILO order are appended to queue one. After this process, we will
have a queue with elements in FILO order.

A flag is used to track which queue to push. No queue is allowed to be pushed on continuously.
*/
class ImplementStackUsingQueues {
private:
	queue<int> q1, q2;
	int i;
	void move(queue<int>& p1, queue<int>& p2)
	{
		while (p2.empty() == false)
		{
			p1.push(p2.front());
			p2.pop();
		}
	}
public:
	ImplementStackUsingQueues() :i(0){}
	// Push element x onto stack.
	void push(int x) {
		if (0 == i)
		{
			q1.push(x);
			this->move(q1, q2);
		}
		else
		{
			q2.push(x);
			this->move(q2, q1);
		}
		i = (i == 0) ? 1 : 0;
	}

	// Removes the element on top of the stack.
	void pop() {
		q1.empty() ? q2.pop() : q1.pop();
	}

	// Get the top element.
	int top() {
		return q1.empty() ? q2.front() : q1.front();
	}

	// Return whether the stack is empty.
	bool empty() {
		return q1.empty() && q2.empty();
	}
};