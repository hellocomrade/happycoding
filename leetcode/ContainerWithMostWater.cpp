#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/container-with-most-water/
/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.

Observation:
I thought this might be related to manhattan skyline problem, but it's not. It can be solved in O(N) time with O(1) space.

It's Caterpillar method, aka two pointers. Here is the deal:
You put two pointers at the begin and the end of the sequence. You always move forward/backward the pointer having the smaller value.
Each time you move one of the pointers, you mark the area. Then you find the answer in max(area at each move).

The idea is by shrinking the distance between two pointers, the only possible way to get a larger area is by finding a greater height[k]. 
Otherwise, the area would be less than the current value.

The code below skips the extra complexity by calcuating the area at each move, which is not necessary but making the coding easier...
*/
class SolutionContainerWithMostWater {
public:
    int maxArea(vector<int>& height) {
        int len = height.size();
        if(len < 2)return 0;
        int start = 0;
        int end = len - 1;
        long long area = std::min(height[start], height[end]) * (long long)(end - start);
        while(start != end)
        {
            if(height[start] < height[end])
                ++start;
            else
                --end;
            area = std::max(area, std::min(height[start], height[end]) * (long long)(end - start));
        }
        return area;
    }
};
