#include <bitset>
#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/check-if-the-sentence-is-pangram/
/*
1832. Check if the Sentence Is Pangram

A pangram is a sentence where every letter of the English alphabet appears at least once.

Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.



Example 1:

Input: sentence = "thequickbrownfoxjumpsoverthelazydog"

Output: true

Explanation: sentence contains at least one of every letter of the English alphabet.

Example 2:

Input: sentence = "leetcode"

Output: false


Constraints:

- 1 <= sentence.length <= 1000
- sentence consists of lowercase English letters.
*/
class SolutionPangram {
public:
	bool checkIfPangram(string sentence) {
		std::bitset<26> memo;
		std::for_each(sentence.begin(), sentence.end(), [&memo](const char& c) { memo.set((int)c - 97); });
		return memo.all();
	}
};
