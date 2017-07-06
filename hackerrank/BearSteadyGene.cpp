#include <cassert>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

//https://www.hackerrank.com/challenges/bear-and-steady-gene
/*
Bear and Steady Gene

A gene is represented as a string of length  (where n is divisible by 4), composed of the letters A, C, T, and G.
It is considered to be steady if each of the four letters occurs exactly n/4 times. For example, GACT and AAGTGCCT are
both steady genes.

Bear Limak is a famous biotechnology scientist who specializes in modifying bear DNA to make it steady. Right now,
he is examining a gene represented as a string s. It is not necessarily steady. Fortunately,
Limak can choose one (maybe empty) substring of s and replace it with any string of the same length.

Modifying a large substring of bear genes can be dangerous. Given a string s, can you help Limak find the length of the smallest possible substring
that he can replace to make s a steady gene?

Note: A substring of a string S is a subsequence made up of zero or more consecutive characters of S.

Input Format

- The first line contains an interger n divisible by 4, denoting the length of a string s.
- The second line contains a string  of length . Each character is one of the four: A, C, T, G.

Constraints

- 4 <= n <= 500,000
- n is divisible by

Subtask

- 4 <= n <= 2000 in tests worth 30% points.

Output Format

On a new line, print the minimum length of the substring replaced to make s stable.

Sample Input

8
GAAATAAA
Sample Output

5
Explanation

One optimal solution is to replace a substring AAATA with TTCCG, resulting in GTTCCGAA. The replaced substring has length 5, so we print 5 on a new line.

Observations:
Greedy seems OK and among ACGT, how many of them can be over average? In other words, given a sequence with 4 letter A, C, G, T, how many of them can be more than
1/4? The answer is 3, it's the theory behind leader problem: https://codility.com/media/train/6-Leader.pdf

Why we need this? coz we now can hardwire the vector for counting. In this case, we only need a vector with size of 3. Since there will be at most 3 leaders.
If there are less than 3 leaders, setting unused paris as pair(0, 0) is allright.

- We are looking for a substring that for every leader, the number of leading letter is equal to the difference between its total count in the string and average (1/4).
That's the candidate for replacement. We just need to find the minimium size of such substrings.
- So, we first find out leaders by looping through the string. There will be at most 3 leaders.
- Then, we use two pointers. The fast one will stop if a substring is found that meet the requirements that the number of every leader is no less than the difference we defined in step 1.
Next, move slow point rightward and decrease leader count if it's met on the way. In such a manner, we keep tracking on a window that covers a condidate substring. We simply need to
track the shortest one.
*/
class SolutionBearSteadyGene {
public:
	int steadyGene(const string& gene) {
		size_t len = gene.length();
		size_t avg = len / 4, s = 0, f = 0, si = 0, ans = len;
		vector<std::pair<char, size_t> > offenders(3, std::make_pair(0, 0));
		unordered_map<char, size_t> acgt;
		acgt.emplace('A', 0);
		acgt.emplace('C', 0);
		acgt.emplace('G', 0);
		acgt.emplace('T', 0);
		for (char c : gene)++acgt[c];
		for (auto itor = acgt.begin(); acgt.end() != itor; ++itor)
			if (itor->second > avg)offenders[si++] = std::make_pair(itor->first, itor->second - avg);
		if (0 == si)return 0;
		vector<size_t> counter(3, 0);
		while (f < len) {
			while (f < len && (counter[0] < offenders[0].second || counter[1] < offenders[1].second || counter[2] < offenders[2].second)) {
				if (gene[f] == offenders[0].first)++counter[0];
				else if (gene[f] == offenders[1].first)++counter[1];
				else if (gene[f] == offenders[2].first)++counter[2];
				++f;
			}
			ans = std::min(ans, f - s);
			if (gene[s] == offenders[0].first)--counter[0];
			else if (gene[s] == offenders[1].first)--counter[1];
			else if (gene[s] == offenders[2].first)--counter[2];
			++s;
		}
		return ans;
	}
};
void TestBearSteadyGene() {
	SolutionBearSteadyGene so;
	assert(5 == so.steadyGene("GAAATAAA"));
	assert(2 == so.steadyGene("AAATTTCG"));
	assert(2 == so.steadyGene("AATCGATT"));
	assert(0 == so.steadyGene("ACGTACGT"));
	assert(4 == so.steadyGene("AAAATTTT"));
	assert(4 == so.steadyGene("AAAACTTT"));
	assert(3 == so.steadyGene("AAAATTTC"));
	assert(6 == so.steadyGene("AAAATTTTCCCC"));
}