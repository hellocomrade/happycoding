//https://codility.com/demo/results/trainingPN9JSU-CB8/
import java.util.Arrays;
class SolutionTriangle {
    public int solution(int[] A) {
        int len = A.length;
        Arrays.sort(A);
        for(int i = 0; i < len - 2; ++i)//integer overflow
            if((long)A[i] + (long)A[i + 1] > (long)A[i + 2])return 1;
        return 0;
    }
}
