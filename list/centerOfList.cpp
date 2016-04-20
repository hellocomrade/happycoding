#include <list>
#include <vector>
#include <iostream>
using namespace std;

/*
Assuming we don't know the size of the list, find the center element
*/
int centerOfList(list<int> &L)
{
	list<int>::const_iterator slow, fast, end;
	slow = fast = L.begin();
	end = L.end();
	while (fast != end)
	{
		++fast;
		if (fast != end)
		{
			++fast;
			++slow;
		}
	}
	return *slow;
}
void testCenterOfList()
{
	vector<int> vec({ 1, 2, 3, 4, 5, 6 });
	list<int> lst;
	lst.insert(lst.begin(), vec.begin(), vec.end());
	cout << "Expect 4: " << centerOfList(lst) << endl;

	vector<int> vec1({ 1, 2, 3, 4, 5 });
	list<int> lst1;
	lst1.insert(lst1.begin(), vec1.begin(), vec1.end());
	cout << "Expect 3: " << centerOfList(lst1) << endl;

	vector<int> vec2({ 1 });
	list<int> lst2;
	lst2.insert(lst2.begin(), vec2.begin(), vec2.end());
	cout << "Expect 1: " << centerOfList(lst2) << endl;
}
