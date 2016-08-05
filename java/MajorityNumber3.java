//http://www.lintcode.com/en/problem/majority-number-iii/
import java.util.Iterator;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Map;

public class SolutionMajorityNumber3 {
    /**
     * @param nums: A list of integers
     * @param k: As described
     * @return: The majority number
     */
    public int majorityNumber(ArrayList<Integer> nums, int k) {
        // write your code
        int len = nums.size();
        if(len < 1 || k < 1)return -1;
        HashMap<Integer, Integer> kth = new HashMap<>();
        for(int i : nums) {
            if(kth.size() < k - 1) { // has at most k - 1 majority numbers that satisfy more than 1 / k
                if(kth.get(i) == null)kth.put(i, 1);
                else kth.put(i, kth.get(i) + 1);
            }
            else {
                if(kth.get(i) != null)kth.put(i, kth.get(i) + 1); 
                else {
                    Iterator<Map.Entry<Integer, Integer> > itor = kth.entrySet().iterator();
                    while(itor.hasNext()) {
                        Map.Entry<Integer, Integer> pair = itor.next();
                        if(pair.getValue() > 1)
                            pair.setValue(pair.getValue() - 1);
                        else
                            itor.remove();//remove pair during loop using Iterator
                    }
                }
            }
        }
        if(kth.size() > 0) {
            Iterator<Map.Entry<Integer, Integer> > itor = kth.entrySet().iterator();
            int s = len / k, cnt = 0;
            while(itor.hasNext()) {
                Map.Entry<Integer, Integer> pair = itor.next();
                cnt = 0;
                for(int i : nums)
                    if(i == pair.getKey())++cnt;
                if(cnt > s)return pair.getKey();
            }
        }
        return -1;
    }
}
