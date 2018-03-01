#include <vector>
#include <string>
#include <sstream>

using namespace std;

//https://leetcode.com/problems/summary-ranges/
/*
228. Summary Ranges

Given a sorted integer array without duplicates, return the summary of its ranges.

Example 1:

Input: [0,1,2,4,5,7]

Output: ["0->2","4->5","7"]

Example 2:

Input: [0,2,3,4,6,8,9]

Output: ["0","2->4","6","8->9"]

Observations:
Very straightforward question. The only details to pay attention are:

- Single element range;

- End of the array;

And for C++, string concatenation...stringstream here but I also saw others using to_string() in <string> and + operator.
*/
class SolutionSummaryRanges {
private:
	void assembly(vector<string> &ans, int s, int e) {
		stringstream ss;
		ss << s;
		if (e > s) ss << "->" << e;
		ans.emplace_back(ss.str());
	}
public:
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> ans;
		int len = (int)nums.size(), l = 0;
		for (int i = 0; i < len - 1; ++i) {
			if (nums[i] + 1 <  nums[i + 1]) {
				this->assembly(ans, nums[l], nums[i]);
				l = i + 1;
			}
		}
		if (len > 0) this->assembly(ans, nums[l], nums[len - 1]);
		return ans;
	}
};
/*
Test cases:
[0,1,2,4,5,7]
[0,2,3,4,6,8,9]
[0]
[]
[-10,-9,0,1,3,5,6,7,8]

Outputs:
["0->2","4->5","7"]
["0","2->4","6","8->9"]
["0"]
[]
["-10->-9","0->1","3","5->8"]
*/