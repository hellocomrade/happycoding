//https://www.lintcode.com/problem/minimum-window-substring/description
public class SolutionMinimumWindowSubstring {
    /**
     * @param source : A string
     * @param target: A string
     * @return: A string denote the minimum window, return "" if there is no such a string
     */
    public String minWindow(String source , String target) {
        int[] charCnts = new int[256];
        java.util.Arrays.fill(charCnts, 0);
        int l = 0, r = 0, cnt = 0, ansl = 0, ansr = 0, lens = source.length(), lent = target.length(), len = lens + 1;
        for(int i = 0; i < lent; ++i) ++charCnts[(int)target.charAt(i)];
        while(r < lens) {
            if(0 <= --charCnts[(int)source.charAt(r++)]) ++cnt;
            while(cnt == lent) {
                if(r - l < len) {
                    ansl = l;
                    ansr = r;
                    len = r - l;
                }
                if(0 < ++charCnts[(int)source.charAt(l++)]) --cnt;
            }
        }
        return source.substring(ansl, ansr);
    }
}
