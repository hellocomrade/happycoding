//http://www.lintcode.com/en/problem/jump-game-ii/
public class SolutionJumpGame2 {
    /**
     * @param A: A list of lists of integers
     * @return: An integer
     */
    public int jump(int[] A) {
        int len = A.length, ans = 0, nextPos = 0, maxPos = 0;
        for(int i = 0; i < len; ++i) {
            if(i + A[i] >= len - 1)return ++ans;
            maxPos = Math.max(A[i] + i, maxPos);
            if(i == nextPos) {
                if(maxPos == i)return -1;
                nextPos = maxPos;
                ++ans;
            }
        }
        return ans;
    }
    public int jump1(int[] A) {
        int len = A.length, ans = 0;
        if(len > 1) {
            int maxstep = A[0], cnt = A[0];
            for(int i = 1; i < len; ++i) {
                if(cnt + i >= len)return ++ans;
                --cnt;--maxstep;
                maxstep = Math.max(A[i], maxstep);
                if(0 == cnt) {
                    if(maxstep <= 0)return -1;
                    cnt = maxstep;
                    ++ans;
                }
            }
        }
        return ans;
    }
}
