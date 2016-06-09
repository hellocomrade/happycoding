#include <cassert>
#include <sstream>
#include <string>

using namespace std;

//http://www.lintcode.com/en/problem/delete-digits/
/*
Given string A representative a positive integer which has N digits, remove any k digits of the number, the remaining digits are arranged according to the original order to become a new positive integer.

Find the smallest integer after remove k digits.

N <= 240 and k <= N,

Example
Given an integer A = "178542", k = 4

return a string "12"

Observations:
This is a typical problem can be solved by greedy perfectly. Given K digts need to be removed, we could keep
len - K digits, let's determine the digits from the leftmost one. Remember the order of remaining digits are maintained!
For example, we have 9 digits string and we are asked to remove 4 of them, which means we will keep 5 digits.
We start the search from index 0 and ends at 4, since 4 is the furthest place for we could reach to search for
the first digit (leftmost). Why? After we decide the first digit, we should leave at least 4 digits in the string in
order to form a 5-digits number.

What do we search for? Obviously, the smallest number! With one exception, leadding 0.

10006099, K = 4, the correct answer is: 0

It took me some time to figure it out: if zero is leading, it's still considered as valid candidate, but
they will be removed from the final result. So for the above case, the four digits left are: "0000", therefore
the final result is 0
*/
class SolutionDeleteDigits {
public:
	/**
	*@param A: A positive integer which has N digits, A is a string.
	*@param k: Remove k digits.
	*@return: A string
	*/
	string DeleteDigits(string A, int k) {
		// wirte your code here
		int len = A.length();
		ostringstream os;
		if (len <= k)return os.str();
		int end = 0, min = 10, idx = -1, start = -1, cnt = len - k;
		while (cnt > 0)
		{
			start = idx + 1;
			end = len - cnt-- + 1;
			//cout << start << ',' << end <<endl;
			min = 10;
			for (int i = start; i < end; ++i)
			{
				if (A[i] - 48 < min)
				{
					//if(start == 0 && A[i] == '0')
					//    continue;
					idx = i;
					min = A[i] - 48;
				}
			}
			if (!(os.str().empty() && min == 0))
				os << min;
		}
		if (os.str().empty())os << "0";
		return os.str();
	}
};
void TestDeleteDigits()
{
	SolutionDeleteDigits so;
	assert("0" == so.DeleteDigits("1006099", 4));
	assert("9" == so.DeleteDigits("106099", 3));
}