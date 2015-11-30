#include "stdafx.h"
#include <cassert>
#include <stack>
#include <list>
#include <vector>
#include <iostream>

//yes, stl list has size(), but we just pretend we don't know that
//so we can practice the "faster runner/slow runner" trick
bool isListPalindrome(list<int> &lst)
{
    assert(lst.size() > 0);
    list<int>::iterator slow = lst.begin(), fast = lst.begin();
    stack<int> stk4HalfList;
    while (fast != lst.end())
    {
	stk4HalfList.push(*slow);
	++slow;
	//std::advance will throw exception if mvoing 2 step forward can't be done, say move over end()
	//std::advance(fast,2);
	++fast;
	//if ++fast hist the end(), we have odd number of elem in the list
	//in this case, we have a cental element that we don't need to compare
	//we could either pop the top from the stack or move slow 1 step back
	if (fast == lst.end())
	{
	    //--slow;
	    stk4HalfList.pop();
	    break;
	}
	else
	    ++fast;
    }
    //we only need to compare the first half of list, which is on the stack with the second half, which 
    //is referenced by slow
    while (false == stk4HalfList.empty())
    {
	if (stk4HalfList.top() == *slow)
	{
	    stk4HalfList.pop();
	    ++slow;
	}
	else
	    break;
    }
    return stk4HalfList.empty();
}
void testIsListPalindrome()
{
	vector<int> vec({ 1, 2, 3, 3, 2, 1 });
	list<int> lst;
	lst.insert(lst.begin(), vec.begin(), vec.end());
	cout << "Expect 1: " << isListPalindrome(lst) << endl;
	
	vector<int> vec1({ 1, 2, 3, 2, 1 });
	lst.clear();
	lst.insert(lst.begin(), vec1.begin(), vec1.end());
	cout << "Expect 1: " << isListPalindrome(lst) << endl;

	vector<int> vec2({ 1, 2, 1 });
	lst.clear();
	lst.insert(lst.begin(), vec2.begin(), vec2.end());
	cout << "Expect 1: " << isListPalindrome(lst) << endl;

	vector<int> vec3({ 1, 1 });
	lst.clear();
	lst.insert(lst.begin(), vec3.begin(), vec3.end());
	cout << "Expect 1: " << isListPalindrome(lst) << endl;

	vector<int> vec4({ 1 });
	lst.clear();
	lst.insert(lst.begin(), vec4.begin(), vec4.end());
	cout << "Expect 1: " << isListPalindrome(lst) << endl;

	vector<int> vec5({ 1, 2, 1, 2 });
	lst.clear();
	lst.insert(lst.begin(), vec5.begin(), vec5.end());
	cout << "Expect 0: " << isListPalindrome(lst) << endl;

	vector<int> vec6({ 1, 2, 1, 2, 3 });
	lst.clear();
	lst.insert(lst.begin(), vec6.begin(), vec6.end());
	cout << "Expect 0: " << isListPalindrome(lst) << endl;
}
