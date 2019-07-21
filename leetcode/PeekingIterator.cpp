#include <vector>

using namespace std;

//https://leetcode.com/problems/peeking-iterator/
/*
284. Peeking Iterator

Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().

Example:

Assume that the iterator is initialized to the beginning of the list: [1,2,3].

Call next() gets you 1, the first element in the list.


Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.

You call next() the final time and it returns 3, the last element.

Calling hasNext() after that should return false.

Follow up: How would you extend your design to be generic and work with all types, not just integer?

Hints:

- Think of "looking ahead". You want to cache the next element.
- Is one variable sufficient? Why or why not?
- Test your design with call order of peek() before next() vs next() before peek().
- For a clean implementation, check out: https://github.com/google/guava/blob/703ef758b8621cfbab16814f01ddcc5324bdea33/guava-gwt/src-super/com/google/common/collect/super/com/google/common/collect/Iterators.java#L1125

Observations:

If you actually peek the peek hints, you probably can carry out the solution immediately :)

Since touching given vector is absolutely not allowed, there is no way to peek the next value unless Iterator::next() is
called and the value is then cached. Simply caching the next value during PeekingIterator::peek() might not be sufficient
to maintain the order. A second boolean variable is necessary to let the following operations know if PeekingIterator has
a cached value therefore no Iterator::next() should be invoked.

In the nutshell, PeekingIterator simply maintain the behaviors of base class Iterator with the read advance. Therefore, side effects
should be taken care of as edge cases, for example:

1. Calling peek() multiple times continuously;
2. peek() then next() v.s. next() then peek();
3. peek() the last element on nums then check hasNext()

All these edge cases require the second boolean memeber variable, this->hasVal, as the guide.

Notes: the implementation of Iterator is not given. Therefore, compilation can be done but no way to link and run it.
*/
namespace PeekingIterator {
	// Below is the interface for Iterator, which is already defined for you.
	// **DO NOT** modify the interface for Iterator.

	class Iterator {
		struct Data;
		Data* data;
	public:
		Iterator(const vector<int>& nums);
		Iterator(const Iterator& iter);
		virtual ~Iterator();
		// Returns the next element in the iteration.
		int next();
		// Returns true if the iteration has more elements.
		bool hasNext() const;
	};


	class PeekingIterator : public Iterator {
	private:
		int nextVal;
		bool hasVal;
	public:
		PeekingIterator(const vector<int>& nums) : Iterator(nums), hasVal(false) {
			// Initialize any member here.
			// **DO NOT** save a copy of nums and manipulate it directly.
			// You should only use the Iterator interface methods.

		}

		// Returns the next element in the iteration without advancing the iterator.
		int peek() {
			if (false == this->hasVal) {
				this->nextVal = Iterator::next();
				this->hasVal = true;
			}
			return this->nextVal;
		}

		// hasNext() and next() should behave the same as in the Iterator interface.
		// Override them if needed.
		int next() {
			return true == hasVal ? this->hasVal = false, this->nextVal : Iterator::next();
		}

		bool hasNext() const {
			return Iterator::hasNext() || this->hasVal;
		}
	};
}
/*
Test cases:

["PeekingIterator","next","peek","next","next","hasNext"]
[[[1,2,3]],[],[],[],[],[]]
["PeekingIterator","peek","next"]
[[[1]],[],[]]
["PeekingIterator","peek","peek","next","hasNext"]
[[[1]],[],[],[],[]]
["PeekingIterator","hasNext","peek","peek","next","next","peek","peek","next","hasNext","peek","hasNext","next","hasNext"]
[[[1,2,3,4]],[],[],[],[],[],[],[],[],[],[],[],[],[]]

Outputs:

[null,1,2,2,3,false]
[null,1,1]
[null,1,1,1,false]
[null,true,1,1,1,2,3,3,3,true,4,true,4,false]
*/