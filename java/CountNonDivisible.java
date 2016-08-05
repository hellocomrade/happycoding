//https://codility.com/demo/results/trainingZ8N88F-PTR/
import java.util.HashMap;
class SolutionCountNonDivisible {
    public int[] solution(int[] A) {
        // write your code in Java SE 8
        int len = A.length;
        int[] ans = new int[len];
        HashMap<Integer, Integer> counter = new HashMap<>();
        HashMap<Integer, Integer> memo = new HashMap<>();
        Integer ig = null;
        for(int i : A){
            ig = counter.get(i);
            if(ig == null)counter.put(i, 1);
            else counter.put(i, ig + 1);
        }
        int cnt = 0, k = 0, j = 0;
        for(int i = 0; i < len; ++i) {
            k = A[i]; cnt = len; j = 1;
            if(memo.get(k) != null) {
                ans[i] = memo.get(k);
                continue;
            }
            while(j * j <= k) {
                if(k % j == 0) {
                    if(counter.get(j) != null) cnt -= counter.get(j);
                    if(j * j != k && counter.get(k / j) != null) cnt -= counter.get(k / j);
                }
                ++j;
            }
            memo.put(k, cnt);
            ans[i] = cnt;
        }
        return ans;
    }
}
