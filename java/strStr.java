//https://leetcode.com/problems/implement-strstr/
public class SolutionStrStr {
    private int[] lpps(String needle) {
        if(0 == needle.length())return null;
        int len = needle.length();
        int[] ans = new int[len];
        ans[0] = -1;
        if(len > 1) {
            ans[1] = 0;
            int left = 0, right = 2;
            while(right < len) {
                if(needle.charAt(left) == needle.charAt(right - 1))
                    ans[right++] = ++left;
                else if(left > 0)
                    left = ans[left];
                else {
                    ans[right++] = 0;
                    left = 0;
                }
            }
        }
        return ans;
    }
    //KMP version
    public int strStr(String haystack, String needle) {
        if(null == haystack || null == needle || needle.length() > haystack.length())return -1;
        int hlen = haystack.length(), nlen = needle.length(), ans = 0, i = 0;
        int[] memo = this.lpps(needle);
        while(ans + nlen <= hlen) {
            while(i < nlen && haystack.charAt(ans + i) == needle.charAt(i))++i;
            if(nlen == i)return ans;
            ans += i - memo[i];
            i = memo[i] <= 0 ? 0 : memo[i];
        }
        return hlen == nlen && 0 == hlen ? 0 : -1; 
    }
}
