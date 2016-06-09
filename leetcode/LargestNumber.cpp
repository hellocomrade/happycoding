#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

//https://leetcode.com/problems/largest-number/
/*
179. Largest Number

Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.

Observations:
If you thought you could figure out the order among numbers for largest number's purpose at digit level,
you run into a trap.
When we do sorting, we compare number A with number B, we can examine them by comparing AB and BA. This can
be done through to_string, which is intutive, but slower; or, through the math, do it on number directly, which
could lead to integer overflow, so we use long long here.
*/
class SolutionLargestNumber {
public:
	//Slow, since we have a lot of string concatenation during sorting
	string largestNumber1(vector<int>& nums) {
		auto comp = [](int a, int b){
			string str_a = to_string(a);
			string str_b = to_string(b);
			return str_a + str_b > str_b + str_a;
		};
		ostringstream os;
		std::sort(nums.begin(), nums.end(), comp);
		if (nums.size() > 1 && nums[0] == 0)
			os << 0;
		else
		{
			for (int i : nums)
				os << i;
		}
		return os.str();
	}
	//Faster coz we concatenate numbers now
	string largestNumber(vector<int>& nums) {
		auto comp = [](int a, int b){
			if (a == 0)return false;
			else if (b == 0)return true;
			long long m10 = 1, n10 = 1, la = a, lb = b;
			while (m10 <= la)
				m10 *= 10;
			while (n10 <= lb)
				n10 *= 10;
			//cout << la <<','<<m10<<':'<<lb<<","<<n10<<endl;
			return la * n10 + lb > lb * m10 + la;
		};
		ostringstream os;
		std::sort(nums.begin(), nums.end(), comp);
		if (nums.size() > 1 && nums[0] == 0)
			os << 0;
		else
		{
			for (int i : nums)
				os << i;
		}
		return os.str();
	}
};