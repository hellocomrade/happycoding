#include <cassert>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//http://www.lintcode.com/en/problem/majority-number-iii/
/*
Majority Number III

Given an array of integers and a number k, the majority number is the number that occurs more than 1/k of the size of the array.

Find it.

Notice

There is only one majority number in the array. <-- this is a simplification and should not be there at the first place

Example
Given [3,1,2,3,2,3,3,4,4,4] and k=3, return 3.

Challenge
O(n) time and O(k) extra space

Observations:
Generic Boyer Moore Majority Voting algorithm. For any given K, there are at most K - 1 majority numbers.
We allocate O(K) space for counting the count of elements we have scaned so far up to K - 1 of them. Once the
cap is met, we decrease the count on each element in the counter and remove those who's count is zero. After
an element is removed, we now have space to put on a new element if exists.

After this process, we have some candidates and we have to check them one by one to eliminate false ones.

For the case like ([1,1,1,9,9,9,9], 3), both 1 and 9 should be returned.

Actually, in the worst case, K is close to len, this algoirthm could degrade to O(N^2). Using a Set instead of
unordered_map could improve that a bit, but will degrade the performance for general cases.
*/
class SolutionMajorityNumber3 {
public:
	/**
	* @param nums: A list of integers
	* @param k: As described
	* @return: The majority number
	*/
	int majorityNumber(vector<int> nums, int k) {
		int len = nums.size(), ans = -1;
		unordered_map<int, int> counter;
		auto end = counter.end();
		for (int i = 0; i < len; ++i)
		{
			auto val = counter.find(nums[i]);
			if (end == val)
			{
				if (counter.size() < k - 1)
					counter.emplace(nums[i], 1);
				else
				{
					/*
					In order to remove the elements in container during loop, you have
					to use iterator in C++, erase will return the next available iterator after erase.
					You should take that after erase instead of ++
					*/
					auto p = counter.begin();
					while (p != end)
					{
						p->second--;
						if (0 == p->second)
							p = counter.erase(p);
						else
							++p;
					}
				}
			}
			else
				counter[nums[i]]++;
		}
		for (const auto& candidate : counter)
			if (std::count(nums.begin(), nums.end(), candidate.first) >  len / k)
				return candidate.first;
		return ans;
	}
};
void TestMajorityNumber3(){
	SolutionMajorityNumber3 so;
	assert(3 == so.majorityNumber(vector<int>{3, 1, 2, 3, 2, 3, 3, 4, 4, 4}, 3));
	assert(61 == so.majorityNumber(vector<int>{7, 1, 7, 7, 61, 61, 61, 10, 10, 10, 61}, 3));
	//This should return both 1 and 9
	so.majorityNumber(vector<int>{1, 1, 1, 9, 9, 9, 9}, 3));
}