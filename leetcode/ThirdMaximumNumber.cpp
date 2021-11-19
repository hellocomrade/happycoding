#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/third-maximum-number/
/*
414. Third Maximum Number

Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.



Example 1:

Input: nums = [3,2,1]

Output: 1

Explanation:

The first distinct maximum is 3.

The second distinct maximum is 2.

The third distinct maximum is 1.

Example 2:

Input: nums = [1,2]

Output: 2

Explanation:

The first distinct maximum is 2.

The second distinct maximum is 1.

The third distinct maximum does not exist, so the maximum (2) is returned instead.

Example 3:

Input: nums = [2,2,3,1]

Output: 1

Explanation:

The first distinct maximum is 3.

The second distinct maximum is 2 (both 2's are counted together since they have the same value).

The third distinct maximum is 1.


Constraints:

- 1 <= nums.length <= 104
- -2^31 <= nums[i] <= 2^31 - 1


Follow up: Can you find an O(n) solution?

Observations:

Haven't done anything for a while. This is an easy level question.

Since it asks for only top 3 distinct elements, we can use a container with 4 elements only, then any operation like sort on such a container,
is considered constant time.

Once can prefill a 4 elemetns vector, bucket with the min value in the input array, then push any element in the input array into the bucket[3]
as long as such an element doesn't exist yet in bucket. Then sort the bucket during each iteration, again this is a const operation.

At the end, if nums.size() > 3, bucket[2] can be return safely. Otherwise two edge cases returning bucket[0]:

1. If nums.size() < 3, bucket[0] shall be returned;

2. If nums.size() = 3 and bucket[2] == bucket[1], bucket[0] should be returned, i.e [2,1,1]
*/
class SolutionThirdMaximumNumber {
public:
	int thirdMax(vector<int>& nums) {
		size_t len = nums.size();
		vector<int> bucket(4, *std::min_element(nums.begin(), nums.end()));
		for (int i = 0; i < len; ++i) {
			if (bucket.end() == std::find(bucket.begin(), bucket.end(), nums[i])) {
				bucket[3] = nums[i];
				std::sort(bucket.begin(), bucket.end(), greater<int>());
			}
		}
		return len < 3 || bucket[2] == bucket[1] ? bucket[0] : bucket[2];
	}
};
/*
Test cases:

[3,2,1]
[1,2]
[2,2,3,1]
[1]
[1,1,2]

Outputs:

1
2
1
1
2
*/