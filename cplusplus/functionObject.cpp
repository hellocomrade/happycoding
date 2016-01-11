#include <set>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

class Person
{
private:
	string firstName;
	string lastName;
public:
	Person(const string &f, const string &l) :firstName(f), lastName(l){}
	string FirstName()const{ return this->firstName; }
	string LastName()const{ return this->lastName; }
};
class PersonSortFun
{
public:
	bool operator ()(const Person &p1, const Person &p2)const
	{
		/* a person is less than another person
		* - if the last name is less
		* - if the last name is equal and the first name is less
		*/
		//weird way to implement the above conditions. Why not use == directly?
		return p1.LastName()<p2.LastName() ||
			(!(p2.LastName()<p1.LastName()) &&
			p1.FirstName()<p2.FirstName());

	}
};
typedef bool(*PersonCMP)(const Person &p1, const Person &p2);
bool Operator(const Person &p1, const Person &p2)
{
	return p1.LastName()<p2.LastName() ||
		(!(p2.LastName()<p1.LastName()) &&
		p1.FirstName()<p2.FirstName());
}

class Nth {    //function object that returns true for the nth call
private:
	int nth;          //call for which to return true
	int count;        //call counter
public:
	Nth(int n) : nth(n), count(0) {
	}
	bool operator() (int) {
		return ++count == nth;
	}
};

void testFunctionObj()
{
	//PersonCMP p = Operator;
	//set<Person, p> pset;//error, a type is expected
	/*
	template < class T,                        // set::key_type/value_type
	class Compare = less<T>,        // set::key_compare/value_compare
	class Alloc = allocator<T>      // set::allocator_type
	> class set;

	set template's second argument requires a function object，
	typedef std::set<Person, PersonCMP> PersonSet;
	won't generate a compile time error，since PersonCMP p，p(a1,a2) is valid.
	runtime will have "reference to 0x00000 invalid pointer", since PersonCMP never get a chance
	to be instantiated.
	*/
	typedef std::set<Person, PersonSortFun> PersonSet;
	PersonSet ps;
	Person p1("Guan", "Wang");
	Person p2("Joe", "Joe");
	Person p3("Jane", "Joe");
	Person p4("Jeff", "Mcauly");
	ps.insert(p1);
	ps.insert(p2);
	ps.insert(p3);
	ps.insert(p4);
	auto itor = ps.begin();
	for (; itor != ps.end(); ++itor)
		cout << itor->FirstName() << "," << itor->LastName() << std::endl;

	/*
	The algorithm uses find_if() to find the first element that should be removed.
	However, it then uses a copy of the passed predicate op to process the remaining elements if any.
	Here, Nth in its original state is used again and it also removes the third element of the remaining
	elements, which is in fact the sixth element.

	This behavior is not a bug. The standard does not specify how often a predicate might be copied
	internally by an algorithm. Thus, to get the guaranteed behavior of the C++ standard library you
	should not pass a function object for which the behavior depends on how often it is copied or called.
	Thus, if you call a unary predicate for two arguments and both arguments are equal,
	then the predicate should always yield the same result. That is, a predicate should not change its
	state due to a call, and a copy of a predicate should have the same state as the original.
	To ensure that you can't change the state of a predicate due to a function call, you should declare
	operator () as constant member function.
	*/
	list<int> coll;
	//insert elements from 1 to 9
	for (int i = 1; i <= 9; ++i)
		coll.push_back(i);
	for (auto i : coll)
		std::cout << i;
	std::cout << std::endl;
	list<int>::iterator pos;
	//remove_if will conduct "removing" by overwritting the container by ignoring all elements
	//that is agreed by the "predicate"
	//so for the code below, if col.erase() is commented out
	//result will be (3 and 6 should be removed,remember Nth() is not a real predicate since its behavior
	//changed from one run to another, which doesn't follow the convention of a predicate):
	//123456789
	//124578989
	pos = remove_if(coll.begin(), coll.end(),   //range
		Nth(3));                   //remove criterion
	coll.erase(pos, coll.end());
	//C++11,for getting a modifiable object, use for (auto& i: path)
	for (auto i : coll)
		std::cout << i;
	std::cout << std::endl;

}