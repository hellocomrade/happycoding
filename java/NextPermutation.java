public class SolutionNextPermutation {
    /**
     * @param nums: an array of integers
     * @return: return nothing (void), do not return anything, modify nums in-place instead
     */
    public int[] nextPermutation(int[] nums) {
        // write your code here
        if(nums != null) {
            int len = nums.length;
            int i = len - 1, t = 0;
            for(; i > 0; --i)
                if(nums[i] > nums[i - 1])break;
            if(i > 0) {
                t = nums[i - 1];
                int j = len - 1;
                for(; j >= i; --j)
                    if(t < nums[j])break;
                nums[i - 1] = nums[j];
                nums[j] = t;
            }
            int j = len - 1;
            while(i < j) {
                t = nums[j];
                nums[j--] = nums[i];
                nums[i++] = t;
            }
        }
        return nums;
    }
}
