import java.util.Arrays;

//https://leetcode.com/problems/longest-increasing-subsequence
class SolutionLongestIncreasingSubsequence {
    //NLogN BS
    public int lengthOfLIS(int[] nums) {
        int len = nums.length, ans = 0, r = 0, l = 0, sz = 0, m, t;
        int[] seq = new int[len];
        for(int i : nums) {
            if(0 == sz) seq[sz++] = i;
            else {
                l = 0;
                r = sz - 1;
                t = sz;
                while(l <= r) {
                    m = l + (r - l) / 2;
                    if(seq[m] >= i) {
                        t = m;
                        r = m - 1;
                    }
                    else
                        l = m + 1;
                }
                seq[t] = i;
                if(sz == t) ++sz;
            }
        }
        return 1 > len ? 0 : sz;
    }
    //O(N^2) DP
    public int lengthOfLIS1(int[] nums) {
        int len = nums.length, ans = 0;
        int[] memo = new int[len];
        Arrays.fill(memo, 1);
        for(int i = 1; i < len; ++i) {
            for(int j = i - 1; j > -1; --j)
                if(nums[j] < nums[i]) memo[i] = Math.max(memo[i], memo[j] + 1);
            ans = Math.max(ans, memo[i]);
        }
        return 1 == len ? 1 : ans;
    }
}
