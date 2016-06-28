//http://www.lintcode.com/en/problem/subarray-sum/
import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashMap;

public class SolutionSubarraySum {
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number 
     *          and the index of the last number
     */
    public ArrayList<Integer> subarraySum(int[] nums) {
        // write your code here
        int len = nums.length;
        ArrayList<Integer> ans = new ArrayList<>(Arrays.asList(0, 0));
        HashMap<Integer, Integer> map = new HashMap<>();
        map.put(nums[0], 0);
        for(int i = 1; i < len; ++i) {
            nums[i] += nums[i - 1]; //reuse input array for prefix sum
            if(nums[i] == 0) { //if such subarray starts from index 0
                ans.set(1, i);
                break;
            }
            if(map.get(nums[i]) != null) { // else, check if previous prefix sum value is equal to current one
                ans.set(0, map.get(nums[i]) + 1);
                ans.set(1, i);
                break;
            }
            map.put(nums[i], i);
        }
        return ans;
    }
}
