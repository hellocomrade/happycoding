import java.util.Arrays;
//import java.util.Collections;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
//http://www.lintcode.com/en/problem/anagrams/
import java.util.Arrays;
//import java.util.Collections;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
class SolutionAnagramsArray {
    /**
     * @param strs: A list of strings
     * @return: A list of strings
     */
    public List<String> anagrams(String[] strs) {
        List<String> ans = new ArrayList<>();
        final String dummy = "A";
        HashMap<String, String> map = new HashMap<>();
        for(String s : strs) {
            char[] chars = s.toCharArray();
            Arrays.sort(chars);
            String str = new String(chars);
            if(map.get(str) != null) {
                if(map.get(str) != dummy) {
                    ans.add(map.get(str));
                    map.put(str, dummy);
                }
                ans.add(s);
            }
            else
                map.put(str, s);
        }
        //Collections.sort(ans);
        return ans;
    }
}
