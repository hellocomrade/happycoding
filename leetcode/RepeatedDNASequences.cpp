#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

//https://leetcode.com/problems/repeated-dna-sequences/
/*
187. Repeated DNA Sequences

All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

Example:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"

Output: ["AAAAACCCCC", "CCCCCAAAAA"]

Observations:

I don't know why this one is on leetcode. Since only 10-letter-long sequence matters, there are only (LEN(s) - 10) substrings.
Using a hash table to track the visted substring, then one can tell which one is repeated. This will take O(N) time even considering
the linear algorithm to hash a substring.

By checking the "Related Topics" section, "Bit Manipulation" was then on my rader. How to utilize bitwise operations to
boost the performace? Well, the naive solution is linear already. We shouldn't expect much. That has been said, getting all
substring 10-letter-long does take a lot of extra memory. In fact, the next 10-letter-long substring can be built on previous
one by removing the first letter at the beginning of the previous substring and then appending the new letter to the previous substring.

The description up there sounds like what? A left or right shift depending on how one may look at it. Again if using string only, it will
takes const time to do the shife since 10-letter-long strings. But, it would be faster if bitwise shift is used. So the next question would
be: how to encode DNA sequence in binary format?

Since only 4 letters are invovled, 2 bits are enough to represent one letter in the sequence.

A - 00
C - 01
G - 10
T - 11

Of course, since C++ is used, class bitset should be used. However, the extra implementation is longer
than naive version and looks ugly... Does run faster though...
*/
class SolutionRepeatedDNASequences {
public:
	//52ms
	vector<string> findRepeatedDnaSequences(string s) {
		vector<string> ans;
		bitset<20> bits;
		unordered_map<unsigned long, size_t> maps;
		unsigned long ul;
		size_t len = s.length();
		auto setbit = [&](int i, char c) {
			switch (c) {
			case 'A':
				bits.set(i * 2, 0);
				break;
			case 'C':
				bits.set(i * 2);
				break;
			case 'G':
				bits.set(i * 2 + 1, 1);
				break;
			case 'T':
				bits.set(i * 2);
				bits.set(i * 2 + 1);
				break;
			}
		};
		if (len > 10) {
			for (size_t i = 0; i < 10; ++i) setbit(i, s[i]);
			maps[bits.to_ulong()] = 1;
			for (size_t i = 10; i < len; ++i) {
				bits >>= 2; setbit(9, s[i]); ul = bits.to_ulong();
				if (0 == maps.count(ul)) maps[bits.to_ulong()] = 1;
				else if (1 == maps[ul]) ans.push_back(s.substr(i - 9, 10)), ++maps[ul];
			}
		}
		return ans;
	}
	//68ms
	vector<string> findRepeatedDnaSequences1(string s) {
		vector<string> ans;
		int len = (int)s.length();
		unordered_map<string, int> cnts;
		string str;
		for (int i = 0; i <= len - 10; ++i) {
			str = s.substr(i, 10);
			if (0 == cnts.count(str)) cnts[str] = 1;
			else if (1 == cnts[str]) ans.push_back(str), ++cnts[str];
		}
		return ans;
	}
};
/*
Test cases:

"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
"ACT"
""
"AAAAAAAAAA"
"TTTTTTTTTTTTTTTTTT"
"AAAAAAAAAACCCCCCCCCCAAAAAAAAAACCCCCCCCCTTTTTTTTTGGGGGGGGGGAAAAAAA"
"GAGAGAGAGAG"

Outputs:

["AAAAACCCCC","CCCCCAAAAA"]
[]
[]
[]
["TTTTTTTTTT"]
["AAAAAAAAAA","AAAAAAAAAC","AAAAAAAACC","AAAAAAACCC","AAAAAACCCC","AAAAACCCCC","AAAACCCCCC","AAACCCCCCC","AACCCCCCCC","ACCCCCCCCC"]
[]
*/