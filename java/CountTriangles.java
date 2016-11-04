//https://codility.com/demo/results/trainingKF6KMM-4N8/
import java.util.Arrays;
class SolutionCountTriangles {
    /*
    Caterpillar approach
    O(N^2), This is not the best solution in terms of coding logic though.
    Check the tutorial for the best solution: https://codility.com/media/train/13-CaterpillarMethod.pdf
    */
    public int solution(int[] A) {
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
}
