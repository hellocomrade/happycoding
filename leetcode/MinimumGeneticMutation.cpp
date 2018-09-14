#include <cassert>
#include <string>
#include <vector>
#include <queue>

using namespace std;

//https://leetcode.com/problems/minimum-genetic-mutation
/*
433. Minimum Genetic Mutation

A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.

Note:

- Starting point is assumed to be valid, so it might not be included in the bank.
- If multiple mutations are needed, all mutations during in the sequence must be valid.
- You may assume start and end string is not the same.


Example 1:

start: "AACCGGTT"

end:   "AACCGGTA"

bank: ["AACCGGTA"]

return: 1


Example 2:

start: "AACCGGTT"

end:   "AAACGGTA"

bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2


Example 3:

start: "AAAAACCC"

end:   "AACCCCCC"

bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

Observations:

One might thought this could be done using DP since the term "minimum" is mentioned. Also, since each
gene only has 8 letters, one might think it's possible to cach them somehow. Well, all of these have been
proven as over-thinking.

This is actually solved using an approach similiar to leetcode 127 (Word Ladder), it's a BFS on a tree. Starting
from the start gene, all its immediate children are mutations that is one letter different from it. The genes in the bank
shall be compared with current gene for detecting mutation. This bank can be implemented as a Queue:

- If it's positive on one gene in the bank, that gene should be removed from the bank;
- Otherwise, remove it from the head and put it to the back of the queue;

A greedy approach is taken here: if a gene is identified as a valid mutation, it shall not be used anymore because if it could
be used in a deeper level, only a longer path can possibly be found.

The mutation on the same level can be represented in a Queue as well.

During this level traversal, if at any moment, the end gene is detected, the minimum is found. This is due to the nature
of BFS.

If  mutation queue is empty, the search ends. This could occur due to:

1. No valid mutation anymore;
2. Bank queue is empty;
*/
class SolutionMinimumGeneticMutation {
public:
	int minMutation(const string start, const string end, const vector<string>& bank) {
		int ans = 0, cnt = 0;
		bool foundEnd = false;
		auto isMutation = [](const string &target, const string &gene) {
			int cnt = 0;
			for (int i = 0; i < 8; ++i)
				if (target[i] != gene[i]) ++cnt;
			return 1 == cnt;
		};
		queue<string> bankq, mutationq;
		mutationq.push(start);
		for (string gene : bank) {
			bankq.push(gene);
			if (gene == end) foundEnd = true;
		}
		if (false == foundEnd) return -1;
		while (false == mutationq.empty()) {
			cnt = mutationq.size();
			for (int i = 0, k = bankq.size(); i < cnt; ++i) {
				if (mutationq.front() == end) return ans;
				for (int j = 0; j < k; ++j) {
					if (true == isMutation(mutationq.front(), bankq.front())) mutationq.push(bankq.front());
					else bankq.push(bankq.front());
					bankq.pop();
				}
				mutationq.pop();
			}
			++ans;
		}
		return -1;
	}
};
void TestMinimumGeneticMutation() {
	SolutionMinimumGeneticMutation so;
	assert(1 == so.minMutation("AACCGGTT", "AACCGGTA", vector<string> {"AACCGGTA"}));
	assert(2 == so.minMutation("AACCGGTT", "AAACGGTA", vector<string> {"AACCGGTA", "AACCGCTA", "AAACGGTA"}));
	assert(3 == so.minMutation("AAAAACCC", "AACCCCCC", vector<string> {"AAAACCCC", "AAACCCCC", "AACCCCCC"}));
	assert(8 == so.minMutation("AAAAAAAA", "CCCCCCCC", vector<string> {"AAAAAAAA", "AAAAAAAC", "AAAAAACC", "AAAAACCC", "AAAACCCC", "AACACCCC", "ACCACCCC", "ACCCCCCC", "CCCCCCCA", "CCCCCCCC"}));
}