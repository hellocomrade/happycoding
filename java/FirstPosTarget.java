//http://www.lintcode.com/en/problem/first-position-of-target/
class SolutionFirstPosTarget {
    /**
     * @param nums: The integer array.
     * @param target: Target to find.
     * @return: The first position of target. Position starts from 0.
     */
    public int binarySearch(int[] nums, int target) {
        //write your code here
        int len = nums.length;
        int l = 0, h = len - 1;
        int ans = len, mid;
        while(l <= h) {
            mid = (int)((l + (h - l) / 2));
            if(nums[mid] >= target) {
                ans = mid;
                h = mid - 1;
            }
            else
                l = mid + 1;
        }
        return ans == len ? -1 : nums[ans] == target ? ans : -1;
    }
}
