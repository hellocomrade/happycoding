#include <string>
#include <sstream>
#include <queue>

using namespace std;

//https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
/*
297. Serialize and Deserialize Binary Tree

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

1
/ \
2   3
/ \
4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

Observations:
First of all, we should understand that the result from a single traversal can NOT determine the structure
of binary tree, unless, in this case, we put placeholders to specifiy empty left, right children. Therefore,
any traversal in this mode can identify an unique tree structure.

We use level order traversal here simply because it's in the example. Actually, preorder seems to be more
promising.

As for our level order approach, we first conduct level order traversal. Instead of tracking not null node,
we will insert '#' to the result to represent null node so we can keep the structure intact. However, we actually
don't need any '#' after the last valid node. So we have to truncate the result. A tailing ',' is added just
for easy parse during deseralization. Deseralization is the opposite of the seralization. We still use the
same approach for level order traversal. A queue is used to track all nodes on the same level, then we move
through the tokens and try to match their children; at the meantime, we put these children on the queue for the
next round matches.

This solution is not optimized and preorder approach can get this done in 45 lines if recursion is used.
*/
namespace SerializeDeserializeBT {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class Codec {
	private:
		static const char punct = '#';
		static const char separator = ',';
	public:

		// Encodes a tree to a single string.
		string serialize(TreeNode* root) {
			ostringstream os;
			if (root != nullptr) {
				queue<TreeNode*> q;
				q.push(root);
				TreeNode *current = nullptr;
				while (q.empty() == false) {
					current = q.front(); q.pop();
					if (current != nullptr) {
						os << current->val << separator;
						q.push(current->left);
						q.push(current->right);
					}
					else // in order to keep the structure of the tree, we have to insert null for non-exist node
						os << punct << separator;
				}
			}
			string tmp = os.str();
			int i = tmp.length() - 1;
			//Any '#' and ',' after the last valid node should be discarded
			for (; i > -1; --i)
				if (tmp[i] != separator && tmp[i] != punct)break;
			//we put an extra tailing ',' to make it easier for deserialization to parse out the tokens
			return tmp.substr(0, i + 1) + separator;
		}

		// Decodes your encoded data to tree.
		TreeNode* deserialize(string data) {
			TreeNode *root = nullptr;
			int len = data.length();
			if (len > 1) { //the length of data is no less than 1 even the tree is empty due to the extra tailing ','
				vector<string> tokens;
				int lastStart = 0;
				//since the last character is guaranteed to be ',', we don't need to worry the edge condition at the end
				for (int i = 0; i < len; ++i) {
					if (data[i] == separator) {
						tokens.push_back(data.substr(lastStart, i - lastStart));
						lastStart = i + 1;
					}
				}
				if (tokens.empty() == false) {
					int i = 0, size = 0;
					len = tokens.size();
					root = new TreeNode(stoi(tokens[i++]));
					queue<TreeNode*> q;
					TreeNode *current = nullptr, *node = nullptr;
					q.push(root);
					while (q.empty() == false && i < len) {
						size = q.size();
						for (int j = 0; j < size; ++j) {
							current = q.front(); q.pop();
							//the following probably has a better solution
							if (i < len) {
								if (tokens[i].c_str()[0] == punct)node = nullptr;
								else {
									node = new TreeNode(stoi(tokens[i]));
									q.push(node);
								}
								current->left = node;
							}
							++i;
							if (i < len) {
								if (tokens[i].c_str()[0] == punct)node = nullptr;
								else {
									node = new TreeNode(stoi(tokens[i]));
									q.push(node);
								}
								current->right = node;
							}
							++i;
						}
					}
				}
			}
			return root;
		}
	};

	// Your Codec object will be instantiated and called as such:
	// Codec codec;
	// codec.deserialize(codec.serialize(root));
}