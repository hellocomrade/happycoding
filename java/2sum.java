public class Solution2Sum {
    public int[] twoSum(int[] nums, int target) {
        int[] ans= new int[]{0,0};
        HashMap<Integer, Integer> map = new HashMap<>();
        int j = 0;
        for(int i = 0; i < nums.length; ++i) {
            j = target - nums[i];
            if(map.containsKey(j)) {
                ans[0] = map.get(j);
                ans[1] = i;
                break;
            }
            map.put(nums[i], i);
        }
        return ans;
    }
}
