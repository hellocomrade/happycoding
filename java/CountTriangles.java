//https://codility.com/demo/results/trainingKF6KMM-4N8/
import java.util.Arrays;
class SolutionCountTriangles {
    /*
    Caterpillar approach
    O(N^2), This is not the best solution in terms of coding logic though.
    Check the tutorial for the best solution: https://codility.com/media/train/13-CaterpillarMethod.pdf
    */
    public int solution1(int[] A) {
        int len = A.length, ans = 0, j = 0, k = 0, cnt = 0;
        Arrays.sort(A);
        for(int i = 0; i < len - 2; ++i) {
            j = i + 1;
            k = j + 1;
            cnt = 0;
            while(j <= k) {
                /*
                When j catches up with k and k has not reached len yet,
                we should start examining i, j, k + 1
                */
                if(j == k) {
                    if(len == j)break;
                    else ++k;
                }
                if(k < len && A[i] + A[j] > A[k]) {
                    ++cnt;
                    ++k;
                }
                else {
                    ans += cnt;
                    cnt = Math.max(cnt - 1, 0);
                    ++j;
                }
            }
        }
        return ans;
    }
    /*
    https://codility.com/demo/results/trainingE6HHVA-CUW/
    Here is the better solution according to the tutorial. It's not that obvious to tell O(N^2) since
    it has 3 loops. However, the most inner while loop grow as fast as the for loop of j.
    */
    public int solution(int[] A) {
        int len = A.length, ans = 0, k = 0;
        Arrays.sort(A);
        for(int i = 0; i < len - 2; ++i) {
            k = i + 2;
            for(int j = i + 1; j < len - 1; ++j) {
                while(k < len && A[i] + A[j] > A[k])++k;
                ans += k - j - 1;
            }
        }
        return ans;
    }
}
