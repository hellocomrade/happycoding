//http://www.lintcode.com/en/problem/wood-cut/
public class SolutionWoodCut {
    /** 
     *@param L: Given n pieces of wood with length L[i]
     *@param k: An integer
     *return: The maximum length of the small pieces.
     */
    public int woodCut(int[] L, int k) {
        int l = 1, h = L[0], m = 0, ans = 0;
        long cnt = 0;
        if(null == L || 0 == L.length || k < 1)return ans;
        for(int i : L)
            h = Math.max(i, h);
        while(l <= h) {
            m = l + (h - l) / 2;
            for(int i : L)
                cnt += i / m;
            if(cnt < k)
                h = m - 1;
            else {
                ans = Math.max(ans, m);
                l = m + 1;
            }
            cnt = 0;
        }
        return ans;
    }
}
