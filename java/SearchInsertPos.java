//http://www.lintcode.com/en/problem/search-insert-position/
public class SolutionSearchInsertPos {
    /** 
     * param A : an integer sorted array
     * param target :  an integer to be inserted
     * return : an integer
     */
    public int searchInsert(int[] A, int target) {
        // write your code here
        int len = A.length;
        int l = 0, h = len - 1, mid = 0, ans = len;
        while(l <= h) {
            mid = l + (h - l) / 2;
            if(A[mid] >= target) {
                ans = mid;
                h = mid - 1;
            }
            else
                l = mid + 1;
        }
        return ans;
    }
}
