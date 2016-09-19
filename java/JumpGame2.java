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
    //This version has extra complication comparing with above
    public int jump1(int[] A) {
        int len = A.length, ans = 0;
        if(len > 1) {
            int maxstep = A[0], cnt = A[0];
            for(int i = 1; i < len; ++i) {
                /*
                 * This exit condition might be confusing: why len not len - 1?
                 * Well, the cnt is checked afterward: after it's supposed to be checked when it is assigned at line 34.
                 * so, variable i here when we check, it's already 1 position off the "i" we are supposed to check.
                 * The condition is actually: cnt + i - 1 >= len - 1 ==> cnt + i >= len
                 */
                if(cnt + i >= len)return ++ans;
                --cnt;--maxstep;
                maxstep = Math.max(A[i], maxstep);
                if(0 == cnt) {
                    if(maxstep == cnt)return -1;
                    cnt = maxstep;
                    //maxstep should be reset?
                    maxstep = 0;
                    ++ans;
                }
            }
        }
        return ans;
    }
}
