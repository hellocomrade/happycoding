import java.util.Deque;
import java.util.ArrayDeque;
public class SolutionLongestValidParentheses {
    //This version will guarantee a Time Limit Exceed since the tester doesn't want to you to do a non DP, this constraint can't stop C++
    //though. It appears Deque is faster than Stack, the same reason of HashTable vs HashMap
    public int longestValidParentheses(String s) {
        int len = s.length();
        if(null == s || len < 2)return 0;
        Deque<Integer> stk = new ArrayDeque<>();
        int offBy1 = -1, ans = 0;
        for(int i = 0; i < len; ++i) {
            if('(' == s.charAt(i))stk.push(i);
            else {
                if(0 == stk.size())offBy1 = i;
                else {
                    stk.pop();
                    ans = Math.max(ans, i - (0 == stk.size() ? offBy1 : stk.peek()));
                }
            }
        }
        return ans;
    }
}
