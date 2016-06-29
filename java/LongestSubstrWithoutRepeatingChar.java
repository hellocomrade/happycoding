import java.util.HashMap;
public class SolutionLongestSubstrWithoutRepeatingChar {
    public int lengthOfLongestSubstring(String s) {
        if(s == null || s.isEmpty())return 0;
        int len = s.length();
        int ans = 1, start = 0, i = 0;
        HashMap<Character, Integer> memo = new HashMap<>();
        for(i = 0; i < len; ++i) {
            if(memo.containsKey(s.charAt(i)) == false)
                memo.put(s.charAt(i), i);
            else {
                if(memo.get(s.charAt(i)) >= start) { 
                    ans = Math.max(ans, i - start);
                    start = memo.get(s.charAt(i)) + 1;
                }
                memo.put(s.charAt(i), i);
            }
        }
        return Math.max(ans, i - start);
    }
}
