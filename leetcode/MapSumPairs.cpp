#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

//https://leetcode.com/problems/map-sum-pairs
/*
677. Map Sum Pairs

Implement a MapSum class with insert, and sum methods.

For the method insert, you'll be given a pair of (string, integer). The string represents the key and the integer represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.

For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs' value whose key starts with the prefix.

Example 1:
Input: insert("apple", 3), Output: Null

Input: sum("ap"), Output: 3

Input: insert("app", 2), Output: Null

Input: sum("ap"), Output: 5

Observations:

This question came to me through the training section on leetcode for Trie. Therefore, implementing Trie is the first thing to do.
More precisely, this is a Prefix Trie.

https://leetcode.com/explore/learn/card/trie/150/introduction-to-trie/1045/

To make the sum operation more efficiently, we store accumulated sum value at each node, so we don't have to reach the leaves to collect
sum values. Instead, once we identify the existence of the prefix, the sum value can be retrieved from the Tire Node ends at the given prefix.

Two complications:

- Shall the root node (no letter at all) accumulates sum value as well? By playing with leetcode test cases, it appears to be the case. So, extra
codes are necessary to make sure root node get all sum values accumulated.

- "If the key already existed, then the original key-value pair will be overridden to the new one." For the following cases:
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["aa",3], ["a"], ["aa",2], ["a"]]

The correct answer is: [null,null,3,null,2], which means the sum values on the path "aa" are reset after the same string "aa" was inserted for the second time!

Well, we will have to figure out a way that is able to not only accumulate the sum but update the sum as well in this case.

The solution is an extra hash table, key is the given strings, value is the sum. So when "aa" is given for the second time, we know it was inserted before
and we know the sum for the previous insertion is 3. Now, in order to update the existing path "aa", we only need to get the difference patched:

diff = new_sum_value - previous_sum_value

In this "aa" case, diff = -1.

For the regular cases, diff = new_sum_value since previous_sum_value is 0. So this approach can cover both regular and edge cases.
*/
namespace MapSumPairs {
	class TrieNode {
	private:
		unordered_map<char, std::shared_ptr<TrieNode> > map;
		int val;
	public:
		TrieNode(int value) : val(value) {}
		std::shared_ptr<TrieNode> insert(const char c, int value) {
			if (1 == this->map.count(c))
				this->map[c]->val += value;
			else
				this->map.emplace(c, std::shared_ptr<TrieNode>(new TrieNode(value)));
			return this->map[c];
		}
		std::shared_ptr<TrieNode> getChild(const char c) {
			return (1 == this->map.count(c)) ? this->map[c] : nullptr;
		}
		int getValue() { return this->val; }
		void setValue(int value) { this->val = value; }
	};
	class MapSum {
	private:
		std::shared_ptr<TrieNode> root;
		unordered_map<string, int> memo;
	public:
		MapSum() : root(new TrieNode(0)), memo() {
		}
		void insert(string key, int val) {
			int diff = val - ((1 == this->memo.count(key)) ? this->memo[key] : 0);
			this->memo.emplace(key, val);
			std::shared_ptr<TrieNode> node = this->root;
			this->root->setValue(this->root->getValue() + diff);
			for (char c : key)
				node = node->insert(c, diff);
		}
		int sum(string prefix) {
			int len = (int)prefix.length();
			std::shared_ptr<TrieNode> node = this->root;
			for (int i = 0; i < len && nullptr != node; ++i)
				node = node->getChild(prefix[i]);
			return nullptr != node ? node->getValue() : 0;
		}
	};
	/**
	* Your MapSum object will be instantiated and called as such:
	* MapSum obj = new MapSum();
	* obj.insert(key,val);
	* int param_2 = obj.sum(prefix);
	*/
}
/*
Test cases:

["MapSum", "insert", "sum", "insert", "sum","sum","sum","sum","sum","sum"]
[[], ["apple",3], ["ap"], ["app",2], ["ap"],[""],["a"],["app"],["appl"],["apple"]]
["MapSum","insert","sum","insert","sum","insert","sum","sum","sum"]
[[],["pencil",2],["pen"],["leetcode",5],["le"],["let",1],["le"],["p"],["l"]]
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["aa",3], ["a"], ["aa",2], ["a"]]

Outputs:

[null,null,3,null,5,5,5,5,3,3]
[null,null,2,null,5,null,6,2,6]
[null,null,3,null,2]
*/