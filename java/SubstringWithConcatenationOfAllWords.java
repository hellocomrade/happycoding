import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

//https://www.lintcode.com/problem/substring-with-concatenation-of-all-words/
public class SolutionSubstringWithConcatenationOfAllWords {
    /**
     * @param s: a string
     * @param words: a list of words
     * @return: all starting indices of substring(s)
     */
    public List<Integer> findSubstring(String s, String[] words) {
        int lens = s.length(), lenw = words[0].length(), cnt = words.length, n = lens - lenw + 1, l = 0, r = 0;
        List<Integer> ans = new ArrayList<>();
        Map<String, Integer> memo = new HashMap<>();
        String substr = null;
        for(String word : words) {
            if(false == memo.containsKey(word)) memo.put(word, 0);
            memo.put(word, memo.get(word) + 1);
        }
        for(int i = 0; i < lenw; ++i) {
            l = r = i;
            while(r < n) {
                substr = s.substring(r, r + lenw);
                if(true == memo.containsKey(substr)) {
                    memo.put(substr, memo.get(substr) - 1);
                    if(-1 < memo.get(substr)) --cnt;
                }
                r += lenw;
                while(0 == cnt) {
                    if(r - l == lenw * words.length) ans.add(l);
                    substr = s.substring(l, l + lenw);
                    if(true == memo.containsKey(substr)) {
                        memo.put(substr, memo.get(substr) + 1);
                        if(0 < memo.get(substr)) ++cnt;
                    }
                    l += lenw;
                }
            }
            while(l < n) {
                substr = s.substring(l, l + lenw);
                if(true == memo.containsKey(substr)) {
                    memo.put(substr, memo.get(substr) + 1);
                    if(0 < memo.get(substr)) ++cnt;
                }
                l += lenw;
            }
        }
        return ans;
    }
}
