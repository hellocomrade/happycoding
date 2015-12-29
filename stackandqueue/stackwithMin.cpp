#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

/*
How would you design a stack which, in addition to push and pop, also has a
function min which returns the minimum element? Push, pop and min should all
operate in 0(1) time.
*/
template<typename T>
class StackWithO1Min
{
private:
	stack<T> workStk;
	stack<T> trackStk;
	T minVal;
public:
	StackWithO1Min(T maxvalue) :minVal(maxvalue){}
	void push(const T& t)
	{
		if (t <= minVal)
		{
			trackStk.push(t);
			minVal = t;
		}
		workStk.push(t);
	}
	T top()
	{
		return workStk.top();
	}
	void pop()
	{
		if (workStk.top() == trackStk.top())
			trackStk.pop();
		workStk.pop();
	}
	void min()
	{
		return trackStk.top();
	}
};