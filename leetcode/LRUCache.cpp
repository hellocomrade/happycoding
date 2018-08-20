#include <unordered_map>
#include <list>

using namespace std;

//https://leetcode.com/problems/lru-cache/
/*
146. LRU Cache

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.

put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache(2); //capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

Observations:

LRU cache based upon the idea that the least recently used cache is the first to be removed if have to. In order to
achieve O(1) on both get and put operation, a special designed data structure is needed to do:

1. Put new key in the cache in O(1);
2. Track the age of the cache in O(1);
3. Update the age ofthe cache if visited or updated in O(1);
4. Remove the oldest cache in O(1);

A hashtable to store key/value appears to be an option, age can be attached with value as a pair. However, updating age
is a concern. In this implmentation, every time a cache is used/updated, the ages of all other caches have to be updated
accordingly. That is an O(N) operation. Therefore, another data structure has to be introduced:

Deque, which allows adding/removing elements from both end and depending on the implementation, potentially removing an element
only takes O(1) if it's backed by a linked list. C++ STL list is such an implementation.

1. If a new element is added, push it to the front of the queue;
2. If an existing element is updated, removing it from the queue first and then push it to the front of the queue;
3. If have to remove an element (LRU), always pop from the end of the queue;

One can tell all three operations are O(1).

On the other hand, in hash table, key is the cache key, value is a pair of cache value and the node reference of the
element on the deque. In C++'s case, it's an iterator of list<int>. This is because the definition of std::list::erase

iterator erase (iterator position);

Which takes an iterator. This iterator is needed for updating cache. In this scenario, the updated cache (not LRU) can
be identified on the queue and removed in O(1) if hash table has the iterator stored as part of the value. Other than that,

1. Hash table adds cache key/value and the iterator after the cache key is pushed on to the queue, O(1)
2. Hash table removes chace key/value for LRU, O(1)

Java has a LinkdHashMap supports building LRU cache. Take a look on its removeEldestEntry protected method.
*/
class LRUCache {
private:
	int capacity;
	unordered_map<int, std::pair<int, list<int>::iterator>> cache;
	list<int> queue;
	void updateCacheAge(int key) {
		queue.erase(cache[key].second);
		queue.push_front(key);
		cache[key].second = queue.begin();
	}
public:
	LRUCache(int capacity) : capacity(capacity) {}

	int get(int key) {
		int ans = -1;
		if (1 == cache.count(key)) {
			ans = cache[key].first;
			this->updateCacheAge(key);
		}
		return ans;
	}

	void put(int key, int value) {
		if (1 == cache.count(key)) {
			cache[key].first = value;
			this->updateCacheAge(key);
		}
		else {
			if (this->capacity == queue.size()) {
				cache.erase(queue.back());
				queue.pop_back();
			}
			queue.push_front(key);
			cache.emplace(key, std::make_pair(value, queue.begin()));
		}
	}
};

/**
* Your LRUCache object will be instantiated and called as such:
* LRUCache obj = new LRUCache(capacity);
* int param_1 = obj.get(key);
* obj.put(key,value);
*/
/*
Test cases:

["LRUCache","put","get"]
[[1],[2,1],[2]]
["LRUCache","put","put","get","put","get","put","get","get","get"]
[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
["LRUCache","put","put","put","put","get","get"]
[[2],[2,1],[1,1],[2,3],[4,1],[1],[2]]
["LRUCache","get","put","get","put","put","get","get"]
[[2],[2],[2,6],[1],[1,5],[1,2],[1],[2]]

Outputs:

[null,null,1]
[null,null,null,1,null,-1,null,-1,3,4]
[null,null,null,null,null,-1,3]
[null,-1,null,-1,null,null,2,6]
*/