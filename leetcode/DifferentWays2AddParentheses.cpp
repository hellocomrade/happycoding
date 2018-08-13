#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/different-ways-to-add-parentheses/
/*
241. Different Ways to Add Parentheses

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1:

Input: "2-1-1"

Output: [0, 2]

Explanation:

((2-1)-1) = 0

(2-(1-1)) = 2

Example 2:

Input: "2*3-4*5"

Output: [-34, -14, -10, -10, 10]

Explanation:

(2*(3-(4*5))) = -34

((2*3)-(4*5)) = -14

((2*(3-4))*5) = -10

(2*((3-4)*5)) = -10

(((2*3)-4)*5) = 10

Observations:

Even the problem is called "Add Parentheses", it actually only asks to output the final results including duplicates in ascending order.

Therefore, placing the parentheses in all possible locations and then calculate the result one by one might be too naive. As long as one
can make sure all precedences are considered, the results can be calculated accordingly without parentheses. This is done by spliting the string
at any location that has '+', '-', or '*'. Then two halves are handled using the same approach. The results coming from two halves are then doing
cross product using the operator at the split point.

This is a typical Divide-and-Conquer. Again, this procedure may produce duplicates, for example:

((2*(3-4))*5) = -10

and

(2*((3-4)*5)) = -10

Someone points out there are lots of duplicated substring calculations that can be avoided by memorization. However,
it appears the test cases are not strong enough to justify that.
*/
class SolutionDifferentWays2AddParentheses {
public:
	vector<int> diffWaysToCompute(const string input) {
		auto bt = [&](int start, int end, auto& fun) {
			vector<int> ret;
			if (start > end || start > (int)input.length() - 1) return ret;
			for (int i = start; i <= end; ++i) {
				switch (input[i]) {
				case '+':
				case '-':
				case '*': {
					vector<int> lvs = fun(start, i - 1, fun);
					vector<int> rvs = fun(i + 1, end, fun);
					for (int j = 0; j < lvs.size(); ++j)
						for (int k = 0; k < rvs.size(); ++k) {
							if ('+' == input[i]) ret.push_back(lvs[j] + rvs[k]);
							else if ('-' == input[i]) ret.push_back(lvs[j] - rvs[k]);
							else ret.push_back(lvs[j] * rvs[k]);
						}
					break;
				}
				default:
					break;
				}
			}
			if (0 == ret.size()) ret.push_back(stoi(input.substr(start, end - start + 1), nullptr, 10));
			return ret;
		};
		vector<int> ans = bt(0, input.length() - 1, bt);
		std::sort(ans.begin(), ans.end());
		return ans;
	}
};
void TestDifferentWays2AddParentheses() {
	SolutionDifferentWays2AddParentheses so;
	vector<int> vec1 = so.diffWaysToCompute("2-1-1");
}
/*
Test cases:

""
"2-1-1"
"2*3-4*5"
"2+3"
"1+2*3"
"2+3*0"
"325+235*12-24592+11512+23*12"

Outputs:

[]
[0,2]
[-34,-14,-10,-10,10]
[5]
[7,9]
[0,2]
[-242766720,-242766720,-242692800,-242692800,-242692800,-242692800,-242537964,-242383680,-242383680,-165039180,-165039180,-101874995,-101874995,-101843975,-101843975,-101843975,-101843975,-101840400,-101840400,-101778839,-101775264,-101775264,-101714255,-101714255,-101710680,-91280000,-87816684,-87662400,-87662400,-87662400,-87662400,-69176855,-69176855,-69173280,-69173280,-69173280,-69173280,-69173280,-38304675,-36851159,-36847584,-36847584,-36786575,-36786575,-36786575,-36786575,-36783000,-36783000,-20366080,-20366080,-20211244,-20056960,-13753012,-13753012,-13626380,-8546155,-8546155,-8481019,-8481019,-8416435,-7317804,-7163520,-7163520,-5764187,-5764187,-5764187,-5764187,-5764187,-5637555,-5637555,-3070379,-3070379,-3005795,-3005795,-430379,-430379,-430379,-430379,-426804,-426804,-399359,-399359,-398807,-395784,-395784,-395784,-395784,-395232,-395232,-395232,-352884,-352884,-352332,-159867,-159867,-156292,-122519,-122519,-118944,-118944,-118944,-118944,-118944,-118944,-118944,-76044,-76044,-33235,-33235,-33235,-33235,-32683,-32683,-32683,-29660,-29660,-29108,-9659,-9659,-9659,-9659,-9659,-9659,-9659,-6084,-6084,116973,116973,116973,120548,26752725,63750400]
*/