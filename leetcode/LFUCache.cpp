#include <cassert>
#include <tuple>
#include <list>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/lfu-cache/
/*
460. LFU Cache

Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item.
For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:

Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache( 2 ); //capacity

cache.put(1, 1);

cache.put(2, 2);

cache.get(1);       // returns 1

cache.put(3, 3);    // evicts key 2

cache.get(2);       // returns -1 (not found)

cache.get(3);       // returns 3.

cache.put(4, 4);    // evicts key 1.

cache.get(1);       // returns -1 (not found)

cache.get(3);       // returns 3

cache.get(4);       // returns 4

Observations:

This is related to leetcode 146 (LRU Cache). LFU Cache, by its definition:

https://en.wikipedia.org/wiki/Least_frequently_used

will evict Least Frequently Used entry first. The goal is to make both geter and
setter in O(1) time complexity.

Such an implementation is on paper here: http://dhruvbird.com/lfu.pdf

It shares the same idea of LRU Cache: a hash map, Map1, is maintained that the value for
each entry contains the information of its weight. For this case, it's the reference
to the node on a list which links all entries that have been accessed for k times. One list
is obviously not enough since k could be from 0 to INT_MAX. A collection of lists can be
stored in a hash map, Map2, as well, the key is the number of accesses. Or, a vector will do as well
if test cases were set in a way that each entry won't be accessed extensively.

As for O(1), Map1 is keyed by Cache key and its value is a tuple: (Cache Value, Number of Access so far, Iterator to the list node)
[Number of Access so far] is an index to Map2 and [Iterator to the list node] is a pointer to the specific node
on the list that using [Number of Access so far] as key on Map2. One can tell both Map2[Number of Access so far]
and Map2[Number of Access so far].erase(Iterator to the list node) are O(1) operation.

One may notice that insertion and deletion are typical operations on lists here and entries in Map1 hold
iterators to those lists that may be retrieved before subsequent insertion and deletion. What's the status of these
iterators? This involves C++ Iterator Invalidation Rules defined in C++03:

https://stackoverflow.com/questions/6438086/iterator-invalidation-rules

For list:

- Insertion: All iterators and references unaffected [23.2.2.3/1]
- Erasure: Only the iterators and references to the erased element is invalidated [23.2.2.3/3]

Comparing with other STL data structures, list's iterator is very resistant to change.

Another key issue is: while Map1 reaches the capacity, the LFU entry shall be removed and such an entry shall
be discovered in O(1). Furturemore, in order to break a tie, LRU should be identified in O(1) as well.

Using the same trick in LRU cache, for the list in Map2, newly create node is always added at the head, so the tail of the list is the LRU.

In order to find the LFU in O(1), one shall know the first entry on Map2 with an non-empty list if keys are sorted in ascending order.
Of course, scanning the Map2 sequentially will do the job but would suffer O(N) time complexity. By taking a closer
look on the problem, one may notice:

- The intial [evict index] on Map2 is always 0;
- While the cache entry is accessed, its presence on Map2 will be removed from Map2[Number of Access so far]
and added to Map2[1 + Number of Access so far]. During this process:

if [Number of Access so far] == [evict index] and Map2[evict index] is empty after removal, [evict index] shall be increased by 1.

As for adding new cache entry, [evict index] is pushed back to 0 since new entry is considered never used.

My first attempt was failed and I was stuck on it for a while. Then I discovered that there is one piece missing and it's not
mentioned anywhere in the problem statement or example:

When a duplicate cache entry is introduced, for example, adding [1, 1] then adding [1, 2]. What should happen when [1, 2] is added:

When a duplicate is introduced, considering the entry is accessed first (This means its [Number of Access so far] shall be increased by 1),
then updating its value on Map1.
*/
class LFUCache {
private:
	int capacity;
	int evictLevel;
	unordered_map<int, std::tuple<int, int, list<int>::iterator> > entries;
	unordered_map<int, list<int> > frequencyList;
public:
	LFUCache(int capacity) : capacity(capacity), evictLevel(0), entries(), frequencyList() {
		this->frequencyList.emplace(0, std::move(list<int>()));
	}

	int get(int key) {
		int ans = -1, idx = -1;
		if (1 == this->entries.count(key)) {
			ans = std::get<0>(this->entries[key]);
			idx = std::get<1>(this->entries[key]);
			this->frequencyList[idx].erase(std::get<2>(this->entries[key]));
			if (idx == this->evictLevel && 0 == this->frequencyList[idx].size()) this->evictLevel++;
			if (0 == this->frequencyList.count(idx + 1)) this->frequencyList.emplace(idx + 1, std::move(list<int>()));
			this->frequencyList[++idx].push_front(key);
			std::get<1>(this->entries[key]) = idx;
			std::get<2>(this->entries[key]) = this->frequencyList[idx].begin();
		}
		return ans;
	}

	void put(int key, int value) {
		if (1 > this->capacity) return;
		if (1 == this->entries.count(key)) {
			this->get(key);
			std::get<0>(this->entries[key]) = value;
			return;
		}
		if (this->capacity == this->entries.size()) {
			this->entries.erase(this->frequencyList[this->evictLevel].back());
			this->frequencyList[this->evictLevel].pop_back();
		}
		this->frequencyList[0].push_front(key);
		this->entries.emplace(key, std::move(std::make_tuple(value, 0, this->frequencyList[0].begin())));
		this->evictLevel = 0;
	}
};

/**
* Your LFUCache object will be instantiated and called as such:
* LFUCache obj = new LFUCache(capacity);
* int param_1 = obj.get(key);
* obj.put(key,value);
*/
void TestLFUCache() {
	LFUCache lfc0(0);
	lfc0.put(0, 0);
	assert(-1 == lfc0.get(0));
	LFUCache lfc1(2);
	lfc1.put(1, 11);
	lfc1.put(2, 22);
	assert(11 == lfc1.get(1));
	lfc1.put(33, 33);
	assert(-1 == lfc1.get(2));
}
/*
Test cases:

["LFUCache","put","put","get","put","get","get","put","get","get","get"]
[[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]
["LFUCache","put","put","get","put","get","get","put","get","get","get"]
[[3],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]
["LFUCache","put","put","get","put","get","get","put","get","get","get"]
[[1],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]
["LFUCache","put","put","get","put","get","get","put","get","get","get"]
[[5],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]
["LFUCache","put","get"]
[[0],[0,0],[0]]
["LFUCache","put","put","put","put","get"]
[[2],[3,1],[2,1],[2,2],[4,4],[2]]
["LFUCache","put","put","put","put","get"]
[[2],[2,1],[3,1],[2,2],[4,4],[2]]
["LFUCache","put","put","get","put","put","put","get"]
[[2],[2,1],[3,1],[2],[2,2],[3,2],[4,4],[2]]
["LFUCache","put","put","get","put","put","put","get"]
[[2],[2,1],[3,1],[3],[2,2],[2,2],[4,4],[2]]

Outputs:

[null,null,null,1,null,-1,3,null,-1,3,4]
[null,null,null,1,null,2,3,null,-1,3,4]
[null,null,null,-1,null,-1,3,null,-1,-1,4]
[null,null,null,1,null,2,3,null,1,3,4]
[null,null,-1]
[null,null,null,null,null,2]
[null,null,null,null,null,2]
[null,null,null,1,null,null,null,2]
[null,null,null,1,null,null,null,2]
*/