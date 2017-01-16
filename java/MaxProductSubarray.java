public class SolutionMaxProductSubarray {
    public int maxProduct(int[] nums) {
        int maxHere = nums[0], minHere = nums[0], maxSofar = nums[0], oldMaxHere;
        for(int i = 1; i < nums.length; ++i) {
            oldMaxHere = maxHere;
            maxHere = Math.max(Math.max(maxHere * nums[i], minHere * nums[i]), nums[i]);
            minHere = Math.min(Math.min(oldMaxHere * nums[i], minHere * nums[i]), nums[i]);
            maxSofar = Math.max(maxHere, maxSofar);
        }
        return maxSofar;
    }
}
