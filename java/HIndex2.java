//https://leetcode.com/problems/h-index-ii/
public class SolutionHIndex2 {
    public int hIndex(int[] citations) {
        int len = citations.length;
        //l is the lowest possible h-index and h is the highest possible h-index, we do a BS greedy here.
        int l = 0, h = len, m = 0;
        while(l <= h) {
            m = l + (h - l) / 2;
            /*
            we can't do len == 0, it can't cover [1]. In this case, 1 should be the answer, but the break
            will make 0 returned.
            */
            if(len == m)break;
            if(citations[len - m - 1] <= m) {
                // if c[len - m - 1] <= m <= citations[len - m], we have the h-index, m
                if(m == 0 || citations[len - m] >= m)
                    break;
                else
                    h = m - 1; // c[len - m - 1] < c[len - m] < m, m should be smaller
            }
            else
                l = m + 1;//h-index could be higher since c[len - m - 1] is no less than m
        }
        return m;
    }
}
