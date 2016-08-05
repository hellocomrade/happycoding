//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
public class SolutionFindMinRotatedSortedArray {
    public int findMin(int[] nums) {
        int len = nums.length;
        int l = 0, h = len - 1, mid = 0, ans = 0;
        while(l <= h) {
            mid = l + (h - l) / 2;
            if(nums[mid] < nums[0]) {
                h = mid - 1;
                ans = mid;
            }
            else
                l = mid + 1;
        }
        return nums[ans];
    }
}
