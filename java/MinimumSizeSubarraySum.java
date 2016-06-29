//
public class SolutionMinimumSizeSubarraySum {
    public int minSubArrayLen(int s, int[] nums) {
        int len = nums.length;
        if(len < 1)return 0;
        int left = 0, right = 0, ans = len + 1;
        long sum = 0;
        while(right <= len) {
            if(sum >= s) {
                ans = Math.min(ans, right - left);
                sum -= nums[left++];
            }
            else {
                if(right == len)break;
                sum += nums[right++];
            }
        }
        return ans == len + 1 ? 0 : ans;
    }
}
