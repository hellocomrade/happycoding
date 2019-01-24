#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/candy/
/*
135. Candy

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

Example 1:

Input: [1,0,2]

Output: 5

Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:

Input: [1,2,2]

Output: 4

Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.

Observations:

My first passed solution is close but different than the "official" solution. Don't have time right now, will
come back to write note later.
*/
class SolutionCandy {
public:
	int candy(const vector<int>& ratings) {
		int len = (int)ratings.size(), ans = len;
		if (2 > len) return 0 == len ? 0 : 1;
		for (int i = 1, status = -1, cnt = 0, prev_cnt = len + 1; i < len; ++i) {
			if (ratings[i] == ratings[i - 1]) status = 1, prev_cnt = len + 1, cnt = 0;
			else if (ratings[i] > ratings[i - 1]) {
				if (2 == status) cnt = 0;
				ans += ++cnt;
				prev_cnt = len + 1, status = 0;
			}
			else {//ratings[i] < ratings[i - 1]
				if (0 == status) prev_cnt = cnt > 0 ? 1 - cnt : len + 1, cnt = 0;
				else ans += ++cnt + (len + 1 != prev_cnt && 1 == ++prev_cnt ? prev_cnt = 0, 1 : 0);
				status = 2;
			}
		}
		return ans;
	}
	//This is the official solution. It's not very intutive to me though. The way it counts overlap at peak
	//is not intutive...
	int candy1(const vector<int>& ratings) {
            int len = (int)ratings.size(), ans = 0, up = 0, down = 0;
            auto sum = [](int n) -> int { return static_cast<int>(n * (n + 1L) / 2L); };
            for(int i = 1, slope = -1, prev_slope = -1; i < len; prev_slope = slope, ++i) {
                slope = ratings[i] < ratings[i - 1] ? 0 : (ratings[i] > ratings[i - 1] ? 2 : 1);
                if((0 == prev_slope && 0 < slope) || (2 == prev_slope && 1 == slope)) {
                    ans += sum(up) + sum(down) + std::max(up, down);
                    up = down = 0;
                }
                if(0 == slope) ++down;
                else if(2 == slope) ++up;
                else ++ans;
            }
            return 1 > len ? 0 : ans + sum(up) + sum(down) + std::max(up, down) + 1;
        }
	// Tried to minic official solution after a peek, but still not the same :)
	int candy0(const vector<int>& ratings) {
            int len = (int)ratings.size(), ans = len;
            if(2 > len) return 0 == len ? 0 : ans;
            auto sum = [](int n) -> int { return n >= 0 ? static_cast<int>(n * (n + 1L) / 2L) : 0; };
            for(int i = 1, status = -1, prev_status = -1, cntUp = 0, prevUp = 0, cntDown = 0; i <= len; prev_status = status, ++i) {
                if(i < len) status = ratings[i] < ratings[i - 1] ? 0 : (ratings[i] == ratings[i - 1] ? 1 : 2);
                if(1 == i) prev_status = status;
                if(prev_status != status || i == len) {
                    ans += sum(cntDown) + sum(cntUp) + (0 < prevUp ? std::max(0, cntDown - prevUp + 1) : 0);
                    prevUp = (0 == status) ? cntUp : 0;
                    cntUp = 0, cntDown = 1 == prev_status ? 0 : -1;
                }
                if(0 == status) ++cntDown;
                else if(2 == status) ++cntUp;
            }
            return ans;
        }
};
void TestCandy() {
	SolutionCandy so;
	assert(5 == so.candy(vector<int>{1, 0, 2}));
	assert(7 == so.candy(vector<int>{1, 3, 2, 1}));
	assert(7 == so.candy(vector<int>{1, 5, 4, 3}));
	assert(11 == so.candy(vector<int>{1, 5, 4, 3, 2}));
}
/*
Test cases:

[1,3,2,1]
[1,5,4,3,2]
[1,2,3,1,0]
[3,2,1,0,1,2]
[3,2,1,0,1,2,3]
[3,2,1,0,1,2,3,4]
[1,1,1,0,0]
[1,2,3,3,3,4,5]
[1,2,3,3,3,2,1]
[29,51,87,87,72,12]
[]
[1]
[1,2]
[1,1]
[1,0,2]
[1,2,2]
[2,2,1]
[1,0,1,1,2,3]
[3,2,1]
[1,2,3]
[1,1,1,1]
[3,3,2,0]
[3,3,3,3,1]
[3,3,3,2,1,0]
[3,3,3,2,2,2,1,1,0]
[1,4,3,3,2,2,1,5,4,3,2,2,0,7,6,9,10,0,1,2]
[8,7,8,7,8,7]
[1,2,2,2,3,3,1,3]
[2,2,2,0,2,1,1,1,0,0,1,1,3,2,1]
[2,2,2,1,1,1,0,3,2,3,3,2,0,1,1,0]
[2,2,2,1,1,1,0,3,2,3,3,2,0]

Outputs:

7
11
9
15
19
24
6
13
13
12
0
1
3
2
5
4
4
11
6
6
4
7
6
12
12
37
9
12
22
25
20
*/
