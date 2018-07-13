#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

//https://leetcode.com/problems/implement-trie-prefix-tree/
/*
208. Implement Trie (Prefix Tree)

Implement a trie with insert, search, and startsWith methods.

Example:

Trie trie = new Trie();

trie.insert("apple");

trie.search("apple");   // returns true

trie.search("app");     // returns false

trie.startsWith("app"); // returns true

trie.insert("app");

trie.search("app");     // returns true

Note:

You may assume that all inputs are consist of lowercase letters a-z.

All inputs are guaranteed to be non-empty strings.

Observations:

Implementing a Prefix Trie. The only trick is to update the member variable for indicating the end of the whole word. For example:

["Trie","insert","insert", "search","search"]
[[],["apps"],["app"],["app"],["apps"]]

Result: [null,null,null,true,true]

When "apps" was inserted, path ends at "app" was marked with isLeaf = false; However, that should be updated when "app" is inserted.
After "app"'s insertion, path ends at "app" should be isLeaf = true;

Same implementations with tweaks in order to get slightly better performance

namespace ImplementTrie1: using unodered_map for child nodes and shared_ptr instead of raw pointer;

namespace ImplementTrie0: using array with 26 elements for child nodes and shared_ptr;

namespace ImplementTrie: TrieNode returns raw pointer for getChild and insert instead of copy of shared_ptr;

MS has guildlines on how to pass a shared_ptr:

https://msdn.microsoft.com/en-us/library/hh279669.aspx


You can pass a shared_ptr to another function in the following ways:

- Pass the shared_ptr by value. This invokes the copy constructor, increments the reference count, and makes the callee an owner. There is a small amount of overhead in this operation, which may be significant depending on how many shared_ptr objects you are passing. Use this option when the code contract (implied or explicit) between the caller and callee requires that the callee be an owner.

- Pass the shared_ptr by reference or const reference. In this case, the reference count is not incremented, and the callee can access the pointer as long as the caller does not go out of scope. Or, the callee can decide to create a shared_ptr based on the reference, and thereby become a shared owner. Use this option when the caller has no knowledge of the callee, or when you must pass a shared_ptr and want to avoid the copy operation for performance reasons.

- Pass the underlying pointer or a reference to the underlying object. This enables the callee to use the object, but does not enable it to share ownership or extend the lifetime. If the callee creates a shared_ptr from the raw pointer, the new shared_ptr is independent from the original, and does not control the underlying resource. Use this option when the contract between the caller and callee clearly specifies that the caller retains ownership of the shared_ptr lifetime.

- When you are deciding how to pass a shared_ptr, determine whether the callee has to share ownership of the underlying resource. An "owner" is an object or function that can keep the underlying resource alive for as long as it needs it. If the caller has to guarantee that the callee can extend the life of the pointer beyond its (the function's) lifetime, use the first option. If you don't care whether the callee extends the lifetime, then pass by reference and let the callee copy it or not.

- If you have to give a helper function access to the underlying pointer, and you know that the helper function will just use the pointer and return before the calling function returns, then that function does not have to share ownership of the underlying pointer. It just has to access the pointer within the lifetime of the caller's shared_ptr. In this case, it is safe to pass the shared_ptr by reference, or pass the raw pointer or a reference to the underlying object. Passing this way provides a small performance benefit, and may also help you express your programming intent.

- Sometimes, for example in a std:vector<shared_ptr<T>>, you may have to pass each shared_ptr to a lambda expression body or named function object. If the lambda or function is not storing the pointer, then pass the shared_ptr by reference to avoid invoking the copy constructor for each element.
*/
namespace ImplementTrie {
	class Trie {
	private:
		class TrieNode {
		private:
			bool isLeaf;
			std::shared_ptr<TrieNode> children[26];
		public:
			TrieNode(bool isEnd) : isLeaf(isEnd), children{ std::shared_ptr<TrieNode>(nullptr) } {}
			TrieNode* getChild(const char key) {
				return true == (bool)this->children[key - 'a'] ? this->children[key - 'a'].get() : nullptr;
			}
			TrieNode* insert(const char key, bool isEnd) {
				if (false == (bool)this->children[key - 'a']) this->children[key - 'a'] = std::make_shared<TrieNode>(isEnd);
				if (true == isEnd) this->children[key - 'a']->isLeaf = isEnd;
				return this->children[key - 'a'].get();
			}
			bool isLeafNode() { return this->isLeaf; }
		};
		std::shared_ptr<TrieNode> root;
	public:
		/** Initialize your data structure here. */
		Trie() : root(new TrieNode(false)) {}

		/** Inserts a word into the trie. */
		void insert(string word) {
			int len = (int)word.length();
			TrieNode* pnode = root.get();
			for (int i = 0; i < len; ++i)
				pnode = pnode->insert(word[i], len - 1 == i);
		}

		/** Returns if the word is in the trie. */
		bool search(string word) {
			int len = (int)word.length();
			TrieNode* pnode = root.get();
			for (int i = 0; i < len && nullptr != pnode; ++i)
				pnode = pnode->getChild(word[i]);
			return nullptr != pnode && true == pnode->isLeafNode();
		}

		/** Returns if there is any word in the trie that starts with the given prefix. */
		bool startsWith(string prefix) {
			int len = (int)prefix.length();
			TrieNode* pnode = root.get();
			for (int i = 0; i < len && nullptr != pnode; ++i)
				pnode = pnode->getChild(prefix[i]);
			return nullptr != pnode;
		}
	};

	/**
	* Your Trie object will be instantiated and called as such:
	* Trie obj = new Trie();
	* obj.insert(word);
	* bool param_2 = obj.search(word);
	* bool param_3 = obj.startsWith(prefix);
	*/
}
namespace ImplementTrie0 {
	class Trie {
	private:
		class TrieNode {
		private:
			bool isLeaf;
			std::shared_ptr<TrieNode> children[26];
		public:
			TrieNode(bool isEnd) : isLeaf(isEnd), children{ std::shared_ptr<TrieNode>(nullptr) } {}
			std::shared_ptr<TrieNode> getChild(const char key) {
				return true == (bool)this->children[key - 'a'] ? this->children[key - 'a'] : nullptr;
			}
			std::shared_ptr<TrieNode> insert(const char key, bool isEnd) {
				if (false == (bool)this->children[key - 'a']) this->children[key - 'a'] = std::make_shared<TrieNode>(isEnd);
				if (true == isEnd) this->children[key - 'a']->isLeaf = isEnd;
				return this->children[key - 'a'];
			}
			bool isLeafNode() { return this->isLeaf; }
		};
		std::shared_ptr<TrieNode> root;
	public:
		/** Initialize your data structure here. */
		Trie() : root(new TrieNode(false)) {}

		/** Inserts a word into the trie. */
		void insert(string word) {
			int len = (int)word.length();
			std::shared_ptr<TrieNode> pnode = root;
			for (int i = 0; i < len; ++i)
				pnode = pnode->insert(word[i], len - 1 == i);
		}

		/** Returns if the word is in the trie. */
		bool search(string word) {
			int len = (int)word.length();
			std::shared_ptr<TrieNode> pnode = root;
			for (int i = 0; i < len && nullptr != pnode; ++i)
				pnode = pnode->getChild(word[i]);
			return nullptr != pnode && true == pnode->isLeafNode();
		}

		/** Returns if there is any word in the trie that starts with the given prefix. */
		bool startsWith(string prefix) {
			int len = (int)prefix.length();
			std::shared_ptr<TrieNode> pnode = root;
			for (int i = 0; i < len && nullptr != pnode; ++i)
				pnode = pnode->getChild(prefix[i]);
			return nullptr != pnode;
		}
	};

	/**
	* Your Trie object will be instantiated and called as such:
	* Trie obj = new Trie();
	* obj.insert(word);
	* bool param_2 = obj.search(word);
	* bool param_3 = obj.startsWith(prefix);
	*/
}
namespace ImplementTrie1 {
	class Trie {
	private:
		class TrieNode {
		private:
			unordered_map<char, std::shared_ptr<TrieNode>> children;
			bool isLeaf;
		public:
			TrieNode(bool isEnd) : isLeaf(isEnd) {}
			std::shared_ptr<TrieNode> getChild(const char key) {
				return 1 == this->children.count(key) ? this->children[key] : nullptr;
			}
			std::shared_ptr<TrieNode> insert(const char key, bool isEnd) {
				if (0 == this->children.count(key)) this->children.emplace(key, std::make_shared<TrieNode>(isEnd));
				if (true == isEnd) this->children[key]->isLeaf = isEnd;
				return this->children[key];
			}
			bool isLeafNode() { return this->isLeaf; }
		};
		std::shared_ptr<TrieNode> root;
	public:
		/** Initialize your data structure here. */
		Trie() : root(std::make_shared<TrieNode>(false)) {}

		/** Inserts a word into the trie. */
		void insert(string word) {
			int len = (int)word.length();
			std::shared_ptr<TrieNode> pnode = root;
			for (int i = 0; i < len; ++i)
				pnode = pnode->insert(word[i], len - 1 == i);
		}

		/** Returns if the word is in the trie. */
		bool search(string word) {
			int len = (int)word.length();
			std::shared_ptr<TrieNode> pnode = root;
			for (int i = 0; i < len && nullptr != pnode; ++i)
				pnode = pnode->getChild(word[i]);
			return nullptr != pnode && true == pnode->isLeafNode();
		}

		/** Returns if there is any word in the trie that starts with the given prefix. */
		bool startsWith(string prefix) {
			int len = (int)prefix.length();
			std::shared_ptr<TrieNode> pnode = root;
			for (int i = 0; i < len && nullptr != pnode; ++i)
				pnode = pnode->getChild(prefix[i]);
			return nullptr != pnode;
		}
	};

	/**
	* Your Trie object will be instantiated and called as such:
	* Trie obj = new Trie();
	* obj.insert(word);
	* bool param_2 = obj.search(word);
	* bool param_3 = obj.startsWith(prefix);
	*/
}
/*
Test cases:

["Trie","insert","search","search","startsWith","insert","insert","search","search","search","search"]
[[],["apple"],["apple"],["app"],["app"],["apps"],["app"],["app"],["apps"],["apple"],[""]]
["Trie","insert","search","search","startsWith","insert","search","search","search","insert","startsWith"]
[[],["pencil"],["pencil"],["pen"],["penc"],["let"],["let"],["le"],[""],["leetcode"],["le"]]

Outputs:

[null,null,true,false,true,null,null,true,true,true,false]
[null,null,true,false,true,null,true,false,false,null,true]
*/