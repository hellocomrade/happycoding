#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/word-search-ii/
/*
212. Word Search II

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example:

Input:
words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

Output: ["eat","oath"]

Note:
- You may assume that all inputs are consist of lowercase letters a-z.

Hints:

1. You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
2. If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.

Observations:

This is pretty similar to Add and Search Word - Data structure design  (leetcode 211). They both are built upon Prefix Tree implementation.
As for this one, since it asks to return all words in the board. Backtracing appears to the best approach.

Then question is: how could we search the words more efficiently on a letter to letter basis? Well, Prefix tree! It works perfectly with BT!

I had 2 failed attempts:

1. Duplicate results. This is due to the fact that mutliple paths on board could generate same word. The fix is simple: once a word is discovered,
   flapping hasEndHere flag on trie node. For example:

   [["a","a"]]
   ["a"]

   Output should be ["a"]

2. Missing words in board. This is caused by the fact that hasEndHere is true doesn't mean such a trie node is a leaf node. For example:
   ["a","b","c"]
   ["ab", "abc"]

   When "ab" is discovered, the tracing should not stop

   The fix for this is simple as well: usually in BT, if a desirable result is found, BT shall be terminated. On this case though, it should continue.
   Therefore, simply removing return statement will do.

BT reset occurs on marking visited cell. This can be done using an extra O(MN) space. In fact, it can be saved by marking cells in place in board.
Someone puts a letter other than a - z, such as '*' as indicator. I did board[i][j] - 97.

Some solution doesn't use the extra vec. Instead, it makes every word as the leaf node on trie. I don't think it actually saves any memory though.
*/
class SolutionWordSearch2 {
private:
	class TrieNode {
	private:
		bool hasEndHere;
		std::shared_ptr<TrieNode> buckets[26];
	public:
		TrieNode(bool endHere) : hasEndHere(endHere), buckets{ std::shared_ptr<TrieNode>(nullptr) } {}
		TrieNode* getChildNode(const char key) { return this->buckets[key - 'a'].get(); }
		TrieNode* addIfAbsent(const char key, bool endHere) {
			if (false == (bool)this->buckets[key - 'a']) this->buckets[key - 'a'] = std::make_shared<TrieNode>(false);
			if (true == endHere) this->buckets[key - 'a']->hasEndHere = true;
			return this->buckets[key - 'a'].get();
		}
		bool hasEndingHere() { return this->hasEndHere; }
		void removeEndingHereFlag() { this->hasEndHere = false; }
	};
	class PrefixTree {
	private:
		std::shared_ptr<TrieNode> root;
	public:
		PrefixTree() : root(std::make_shared<TrieNode>(false)) {}
		void insert(const string& word) {
			size_t len = word.length();
			TrieNode *ptr = root.get();
			for (size_t i = 0; i < len; ++i)
				ptr = ptr->addIfAbsent(word[i], len - 1 == i);
		}
		TrieNode* getRootNodePtr() { return root.get(); }
	};
public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> ans;
		size_t rlen = board.size();
		if (1 > rlen) return ans;
		size_t clen = board[0].size(), mlen = 0;
		PrefixTree trie;
		for (const string& word : words) mlen = std::max(mlen, word.length()), trie.insert(word);
		vector<char> vec(mlen);
		function<void(int, int, int, TrieNode*)> bt = [&](int i, int j, int idx, TrieNode* pnode) {
			if (nullptr == pnode || i < 0 || j < 0 || rlen == i || clen == j || board[i][j] < 'a') return;
			pnode = pnode->getChildNode(board[i][j]);
			if (nullptr == pnode) return;
			vec[idx] = board[i][j];
			if (true == pnode->hasEndingHere()) {
				pnode->removeEndingHereFlag();
				ans.push_back(string(vec.begin(), vec.begin() + idx + 1));
			}
			board[i][j] -= 'a';
			bt(i + 1, j, idx + 1, pnode), bt(i - 1, j, idx + 1, pnode), bt(i, j + 1, idx + 1, pnode), bt(i, j - 1, idx + 1, pnode);
			board[i][j] += 'a';
		};
		for (size_t i = 0; i < rlen; ++i) for (size_t j = 0; j < clen; ++j) bt(i, j, 0, trie.getRootNodePtr());
		return ans;
	}
};
/*
Test cases:

[["a","a"]]
["a"]
[["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]
["oath","pea","eat","rain"]

Outputs:

["a"]
["oath","eat"]
*/