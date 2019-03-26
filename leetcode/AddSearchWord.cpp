#include <string>
#include <memory>
#include <functional>

using namespace std;

//https://leetcode.com/problems/add-and-search-word-data-structure-design/
/*
211. Add and Search Word - Data structure design

Design a data structure that supports the following two operations:

void addWord(word)

bool search(word)

search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

Example:

addWord("bad")

addWord("dad")

addWord("mad")

search("pad") -> false

search("bad") -> true

search(".ad") -> true

search("b..") -> true

Note:
- You may assume that all words are consist of lowercase letters a-z.

Hint1:
- You should be familiar with how a Trie works. If not, please work on this problem: Implement Trie (Prefix Tree) first.

Observations:

Prefix Tree appears to be a good fit for this. One may struggle on the fact that wildcard '.' could have an impact on the performance. But
seems like there is no other way?

When handling wildcard, simple loop through all child nodes(at most ) that are available in current node and exit the loop if
any subtree returns true. In this context, this is qualified as Back Tracing.
*/
class WordDictionary {
private:
	class PrefixTree {
	private:
		class TrieNode {
		private:
			bool hasEndHere;
			std::shared_ptr<TrieNode> buckets[26];
		public:
			TrieNode(bool endHere) : hasEndHere(endHere), buckets{ std::shared_ptr<TrieNode>(nullptr) } {}
			TrieNode* getChildNode(const char key) { return this->buckets[key - 'a'].get(); }
			std::shared_ptr<TrieNode>* getAllChidren() { return this->buckets; }
			TrieNode* addIfAbsent(const char key, bool endHere) {
				if (false == (bool)this->buckets[key - 'a']) this->buckets[key - 'a'] = std::make_shared<TrieNode>(false);
				if (true == endHere) this->buckets[key - 'a']->hasEndHere = true;
				return this->buckets[key - 'a'].get();
			}
			bool hasEndingHere() { return this->hasEndHere; }
		};
		std::shared_ptr<TrieNode> root;
	public:
		/** Initialize your data structure here. */
		PrefixTree() : root(std::make_shared<TrieNode>(false)) {}

		/** Inserts a word into the trie. */
		void insert(string word) {
			size_t len = word.length();
			TrieNode *ptr = root.get();
			for (size_t i = 0; i < len; ++i)
				ptr = ptr->addIfAbsent(word[i], len - 1 == i);
		}

		/** Returns if the word is in the trie. */
		bool searchPattern(string word) {
			size_t len = word.length();
			std::function<bool(size_t i, TrieNode*)> bt = [&](size_t i, TrieNode *ptr) {
				if (nullptr == ptr) return false;
				if (len == i) return nullptr != ptr && true == ptr->hasEndingHere();
				if ('.' != word[i]) return bt(i + 1, ptr->getChildNode(word[i]));
				std::shared_ptr<TrieNode>* sptrs = ptr->getAllChidren();
				bool ans = false;
				for (int j = 0; j < 26; ++j) {
					if (true == (bool)sptrs[j]) ans = bt(i + 1, sptrs[j].get());
					if (true == ans) break;
				}
				return ans;
			};
			return bt(0, this->root.get());
		}
	};
	PrefixTree trie;
public:
	/** Initialize your data structure here. */
	WordDictionary() : trie() {

	}

	/** Adds a word into the data structure. */
	void addWord(string word) {
		this->trie.insert(word);
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string word) {
		return trie.searchPattern(word);
	}
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
 /*
 Test cases:

 ["WordDictionary","addWord","addWord","addWord","search","search","search","search","search","search","search","search","search"]
 [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."],["b.d"],["b..d"],["..."],[".."],["."]]
 ["WordDictionary","addWord","addWord","search","addWord","search"]
 [[],["aaaa"],["bbb"],["aabb"],["aabb"],["a.b."]]

 Outputs:

 [null,null,null,null,false,true,true,true,true,false,true,false,false]
 [null,null,null,false,null,true]
 */