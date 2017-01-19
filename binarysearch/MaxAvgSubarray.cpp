#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>
#include <cstdint>
#include <cassert>

using namespace std;

//http://www.lintcode.com/en/problem/maximum-average-subarray/
/*
 Maximum Average Subarray
 
 Given an array with positive and negative numbers, find the maximum average subarray which length should be greater or equal to given length k.
 
 Notice
 
 It's guaranteed that the size of the array is greater or equal to k.
 
 Example
 Given nums = [1, 12, -5, -6, 50, 3], k = 3
 
 Return 15.667 // (-6 + 50 + 3) / 3 = 15.667
 
 Observation:
 I knew this is the classic binary search greedy since it's the k as the deal b reak. However I can't build the cases
 inside BS.
 
 Then did a Google Search (Well, Lintcode claims this is a Google interview question...): http://stackoverflow.com/questions/13093602/finding-subarray-with-maximum-sum-number-of-elements
 
 Following the logic to implment, again I was stuck. Given an array, find the longest subarray having its sum greater
 than 0...
 
 Took a while to recall that I did read the MonotonicPair problem on Codility. If we transform this array into its
 prefixSum status, then the question becomes:
 
 "A monotonic pair is a pair of integers (P, Q), such that 0 ≤ P ≤ Q < N and A[P] ≤ A[Q].
 
 The goal is to find the monotonic pair whose indices are the furthest apart. More precisely, we should maximize the value Q − P. It is sufficient to find only the distance."
 
 The only difference comparing with monotonic pair implementation is that we also need to examine if each prefixSum[i]
 is greater than zero coz it represents the sum between memo[0] to memo[i]. This is a prefixSum "feature"...
 
 In fact, we don't have to fully implement monotonic pair since we only want to know if memo in its prefixSum form has
 a subarray that is no less than zero and its length is no less than k. Therefore, we could introduce a simpler version:
 
 Given any indx i >= k, we compare prefixSum[i] with the minimum prefixSum value from 0 to i - k - 1. If the substraction
 is no less than zero, we prove such a subarray exists.
 */
class SolutionMaxAvgSubarray {
public:
    /**
     * @param nums an array with positive and negative numbers
     * @param k an integer
     * @return the maximum average
     */
    double maxAverage(const vector<int>& nums, int k) {
        int len = (int)nums.size(), m;
        if (0 == len || k < 1)return 0;
        vector<double> prefixSum(len, 0);
        double left = (double)*std::min_element(nums.begin(), nums.end()), right = (double)*std::max_element(nums.begin(), nums.end());
        double ERROR = 1e-6, mid;
        //double ans = (double)std::accumulate(nums.begin(), nums.end(), 0) / len;
        /*
         The above syntax suger can't be used since it will accumulate nums[i] using int type, which is an integer overflow hazard!
         */
        double ans = 0;
        for (int i = 0; i < len; ++i)
            ans += nums[i];
        ans /= len;
        stack<std::pair<double, int> > stk;
        while (std::abs(right - left) >= ERROR) {
            mid = left + (right - left) / 2;
            stk.empty();
            //std::copy(nums.begin(), nums.end(), memo.begin());
            //std::for_each(memo.begin(), memo.end(), [mid](double &n) { n -= mid; });
            prefixSum[0] = nums[0] - mid;
            m = prefixSum[0] >= ERROR ? 1 : 0;
            for (int i = 1; i < len; ++i) {
                prefixSum[i] = prefixSum[i - 1] + nums[i] - mid;
                if (prefixSum[i] >= ERROR) m = std::max(m, i + 1);
            }
            /*
             If we could find a m among prefixSum[i] - 0, which represents sum from memo[0] to memo[i], there is no
             need to do the following since our purpose is to prove the existence of such a m that is no less than k.
             */
            if (m < k){
                stk.push(std::make_pair(prefixSum[0], 0));
                for (int i = 0; i < len; ++i)
                    if (prefixSum[i] < stk.top().first)stk.push(std::make_pair(prefixSum[i], i));
                for (int i = len - 1; i > -1; --i)
                    while (false == stk.empty() && prefixSum[i] >= stk.top().first) {
                        m = std::max(m, i - stk.top().second);
                        stk.pop();
                    }
            }
            if (m >= k) {
                left = mid;
                ans = std::max(ans, mid);
            }
            else right = mid;
            
        }
        return ans;
    }
};
void TestMaxAvgSubarray() {
    double ERROR = 10e-4;
    SolutionMaxAvgSubarray so;
    //15.667
    assert(std::abs(15.667 - so.maxAverage(vector<int>{1, 12, -5, -6, 50, 3}, 3)) <= ERROR);
    assert(-1 == so.maxAverage(vector<int>{-1, -1, -1, -1}, 2));
    assert(INT32_MIN == so.maxAverage(vector<int>{INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN}, 2));
    //-21.4
    assert(std::abs(-21.4 - so.maxAverage(vector<int>{-1, -2, -3, -100, -1, -50}, 4)) <= ERROR);
    //5.707
    assert(std::abs(5.707 - so.maxAverage(vector<int>{-28, -75, 100, -26, -80, -26, -47, 63, 59, -84, -54, 48, 64, -34, -48, 80, 38, -76, 25, 17, -59, -10, -67, 80, 80, -63, -66, 5, 97, -34, -28, 60, 59, -64, -9, -45, -15, 27, -2, 78, -61, -54, -44, -15, 66, 79, 53, -70, 11, 36, -3, -54, 27, -16, 81, 88, 77, -5, -67, 82, 19, -96, -50, -17, -33, 0, 58, 78, -34, 95, 75, 53, 66, 45, 51, 22, -74, -32, -40, -60, 92, 21, 4, -82, -38, -75, 19, -90, 67, 10, 52, 100, -66, -39, 91, -5, 39, -59, 74, 9, -37, -88, 60, 40, -2, 43, -63, -33, 35, 49, -53, 32, 20, -100, 42, 69, 49, 36, 42, -26, -25, 70, 27, -71, -28, 94, -30, -61, 12, 21, -77, -35, 69, 2, -90, 59, -13, -37, 56, 7, 90, -41, -27, -49, -59, 40, 39, -80, 17, -55, -54, 33, 87, 55, -51, -32, 8, 52, 2, 59, 67, -1, 31, 42, 87, 94, -65, 53, -10, 31, 58, 81, 34, -30, 2, 51, -37, 73, 48, 71, -78, -28, -62, 41, 68, 25, -3, 57, -58, 11, -92, 33, 85, 47, -49, 79, -7, -53, 8, -41, -66, 65, 47, 11, 0, -92, 18, 41, -91, -26, -82, -78, 13, -1, -67, -56, 34, -20, 2, -54, -58, -77, 90, 90, -67, 29, 16, 24, -20, 49, -97, 67, -9, 18, 10, 62, 88, -31, -24, 36, 6, 53, -54, -99, -94, -95, 26, 79, 47, 34, 88, 94, -95, 68, -88, -80, 41, 1, -34, 60, -95, 78, -81, 83, -64, -5, -25, -87, -81, -30, 75, 36, -14, -19, -98, 46, -94, -36, -38, 51, -48, -91, -39, -50, -33, 98, 49, 81, 63, -59, -37, 32, 4, -54, -23, -38, 88, 89, -16, -30, 90, 63, -52, -20, 74, 82, -34, 87, -86, 21, -41, 93, 82, -96, 20, -75, 96, 52, -72, 87, 45, 83, 63, -24, -86, -88, 85, 12, -8, 77, -56, -51, -73, 43, -34, 35, -10, 65, 54, 1, -60, 100, 36, 8, -81, 53, 81, 42, 75, -44, 83, 55, -24, 96, -31, -43, 42, -37, -51, -33, 40, 15, -83, -92, -77, -35, -68, 21, -64, -12, 22, -71, -19, -13, -15, 15, 56, -8, 79, -44, -9, -78, -11, -28, -13, 42, 38, -7, -48, -90, 70, 69, 2, -47, 56, -93, -16, 51, 44, -1, -93, 64, -13, 67, -72, 95, 80, 1, 68, -47, 37, 72, -29, -74, 79, -60, 97, 12, -38, 7, -75, 26, 90, 99, 46, -3, -5, 74, 9, -26, 60, -55, 85, -52, -15, -24, 3, 23, 44, 5, -55, 72, 54, 97, 53, 49, -30, 18, 36, 99, 23, 79, 94, -15, -84, -35, 86, 8, 16, 1, -23, 83, -47, -67, 6, 13, 8, 84, 57, -80, 67, 38, -95, 65, -46, -87, 34, 97, -29, -70, 55, 17, -92, 87, -39, -82, 74, 5, 38, -81, -9, 41, 66, 49, -38, -42, 88, -65, -83, 45, -52, -34, 54, -39, -50, -45, -62, 35, -26, -74, 20, -22, 92, -67, 51, 77, 42, 58, 40, -86, 44, 13, 100, -62, 52, -49, -72, -68, -13, 47, 57, 21, 63, -54, 52, -8, 31, -87, -34, -29, -7, 45, -32, 95, 47, -31, -10, -15, 9, -76, -69, -15, 21, -26, 79, -64, 43, 72, 29, -90, 6, -29, -15, -53, -40, -3, -7, -91, -80, 0, -91, 5, -72, 55, -88, -31, -43, 33, -17, -4, 23, -89, 26, -29, 5, -26, -4, -28, 22, -36, 45, 31, 36, -1, -35, -45, 22, -67, -85, 22, 80, -10, -38, -14, -93, -13, 27, 64, 75, 89, 75, 10, -23, -78, 41, 3, 54, 73, -73, -28, -61, -48, 7, -8, -16, 62, -74, 50, 38, -74, -23, 22, 3, 66, 22, -36, -59, 17, -54, -45, 80, -66, 86, 3, 5, 66, 28, 73, 63, 17, 5, -58, -87, -15, -36, 55, -34, -39, 93, 55, -74, -40, 13, -70, 89, -10, 75, -24, 86, 76, 15, 28, -66, -55, 8, 25, 24, 98, -47, 25, -29, -44, -54, -48, -80, 89, 98, 27, -73, -44, 35, -64, 84, 7, -39, -57, 30, 100, 12, 41, -17, -27, -25, 7, 78, -10, 50, -41, -55, -34, 21, 88, 27, 21, 32, 58, -93, 18, -55, 61, -79, 17, -27, 82, -29, 36, -22, -12, 31, 49, -1, 24, -63, 67, 41, 24, 98, 66, 8, -2, 100, -3, -44, 55, 75, -46, 16, -34, -38, -87, -21, -27, 39, 18, 23, -64, -99, 43, 74, 11, -67, 4, -96, -56, 88, 4, -45, 27, -79, -39, -97, -14, 44, 12, -12, 57, -81, -37, 38, 89, -75, -79, -42, -43, -18, -91, 39, -23, -90, -20, -32, 92, 96, 99, -11, -7, -17, -39, -23, 45, 58, -73, 73, -14, 60, 61, -6, -67, -16, 72, -91, -51, 57, -99, -9, 82, 32, -39, -40, 23, -78, -45, 27, -65, 100, 91, -96, -1, -72, -9, -47, 9, 87, 55, 39, 79, -42, -26, -3, 48, 22, -52, -71, -77, -30, 12, 38, 84, -6, 39, 67, 97, 77, -82, 75, -45, 11, -81, -89, 60, 51, -48, -99, -31, -75, 51, 82, -31, -39, -77, 98, 88, 66, -37, -3, -96, -83, -86, -27, 80, -93, -55, 44, -14, 98, -86, -4, 90, -51, -64, 71, -91, -4, -4, -99, -57, -93, 27, -15, -89, 21, -77, 9, 39, -80, 3, 10, 65, 4, 26, 27, 11, -63, 2, -36, -81, 4, -57, -93, -53, -92, -44, 94, -63, 90, 56, 40, -32, -28, -1, -36, -70, 51, 1, 80, -9, 100, -46, -69, -93, 59, -82, -34, -58, -90, 78, -61, 34, 33, -37, 6, 66, -49, 92, 98, -57, -79, -60, -4, 91, 95, -85, -83, -69, -82, 4, -100, 44, -67, 92, -79, 16, 83, -70, 84, 57, 90, -30, -98, -24, -48, 100, 17, -1, -52, -4, -28, 39, -43, 28, 12, -14, -52, -64, -84, 6, 66, -98, -73, -72
    }, 312)) <= ERROR);
    //-0.333
    assert(std::abs(-0.333 - so.maxAverage(vector<int>{5, -10, 4}, 2)) <= ERROR);
}
