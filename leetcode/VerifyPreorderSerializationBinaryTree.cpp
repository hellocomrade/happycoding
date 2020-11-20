#include <cassert>
#include <string>
#include <stack>

using namespace std;

//https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
/*
331. Verify Preorder Serialization of a Binary Tree

One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

	 _9_
	/   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #

For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:

Input: "9,3,4,#,#,1,#,#,2,#,6,#,#"

Output: true

Example 2:

Input: "1,#"

Output: false

Example 3:

Input: "9,#,#,1"

Output: false

Observations:

When dealing with a BT, first option is usually using recursion. However, for this one, stack is the first choice.

isValidSerialization0 is the implementation using a stack. The idea is like an elminator game on '#':

The basic element in such a setting is:

  N
 / \
#   #

which N is a non-leaf node and # is a leaf node. During interation, if such an element is discovered on the stack, remove it and replace with a single #, replacing N## with #, which
effectively creating a new leaf node.
Otherwise, pushing current node onto the stack.

For example: "9,3,4,#,#,#,#", when reaching the second # after 4

On the stack: [9,3,4,#]

Pop # and 4 out of the stack and push a new #,

On the stack: [9,3,#]

One may notice the code using while instead of if, this is because of the chain reaction:

For example: "9,3,4,#,#,1,#,#,2,#,6,#,#"

After "4,#,#" is merged, on the stack [9,3,#]. When "1,#,#" is discovered and handled, on the stack [9,3,#,#]. The stack should be further cleand up to [9] since "3,#,#" forms
a new element for earse and replacement.

The actually implementation is kind of messy. I didn't find a good way to include the "chain reaction" impl without extra, ugly branches...


isValidSerialization, on the other hand, is what I learnt from the discussion section. It borrows the indegree, outdegree idea from graph. For a BT, including null node '#' or not,
the sum of indegree and outdegree should be 0.

For example:

  1
 / \
2   3

- Node 1 has 2 outdegree and 0 in degree;
- Node 2 and 3 have 0 outdegree but 1 indegree each;

Total sum is 0

Using this idea, an implementation can be given without using the stack. However, the actual impl is tricky as well: whenever degree_sum is negative, the function must return
immediately and this has been checked up front during each iteration. This is due to the fact that non-leaf node will add 2 outdegrees and made a negative sum again back to positive...
Since this impl doesn't actually check the integrity of the BT structure, the check has to be done this way, which, by my opinion, clouds the beauty of this idea...
*/
class SolutioVerifyPreorderSerializationBinaryTree {
public:
	bool isValidSerialization(string preorder) {
		size_t sz = preorder.length();
		int degree_sum = 1;
		for (size_t i = 0; i <= sz; ++i) {
			if (i == sz || ',' == preorder[i]) {
				if (0 > --degree_sum) //indegree
					return false;
				if ('#' != preorder[i - 1]) //outdegree
					degree_sum += 2;
			}
		}
		return 0 == degree_sum;
	}
	bool isValidSerialization0(string preorder) {
		size_t sz = preorder.length();
		stack<char> stk;
		for (size_t i = 0; i <= sz; ++i) {
			if (i == sz || ',' == preorder[i]) {
				while ('#' == preorder[i - 1] && false == stk.empty() && '#' == stk.top()) {
					stk.pop();
					if (true == stk.empty())
						return false;
					stk.pop();
				}
				stk.push('#' == preorder[i - 1] ? '#' : 'N');
			}
		}
		return 1 == stk.size() && '#' == stk.top();
	}
};
void TestVerifyPreorderSerializationBinaryTree() {
	SolutioVerifyPreorderSerializationBinaryTree so;
	assert(false == so.isValidSerialization("9,3,4,#,#,#"));
	assert(true == so.isValidSerialization("9,3,4,#,#,#,#"));
}
/*
Test cases:

"#,7,6,9,#,#,#"
""
"#"
"9"
"9,#"
"1,#"
"9,#,#"
"9,#,#,1"
"9,3,4,#,#,1,#,#,2,#,6"
"9,3,4,#,#,#"
"9,3,4,#,#,#,#"
"9,3,4,#,#,1,#,#,2,#,6,#,#"

Outputs:

false
false
true
false
false
false
true
false
false
false
true
true
*/