//http://www.lintcode.com/en/problem/combinations/
import java.util.List;
import java.util.ArrayList;
public class SolutionCombinations {
    private void aux(List<List<Integer>> ans, List<Integer> lst, int s, int n, int k) {
        if(k == 0) {
            ans.add(new ArrayList<Integer>(lst));
            return;
        }
        for(int i = s; i <= n; ++i) {
            lst.add(i);
            aux(ans, lst, i + 1, n, k - 1);
            lst.remove(lst.size() - 1);
        }
    }
    /**
     * @param n: Given the range of numbers
     * @param k: Given the numbers of combinations
     * @return: All the combinations of k numbers out of 1..n
     */
    public List<List<Integer>> combine(int n, int k) {
		    List<List<Integer>> ans = new ArrayList<>();
		    if(n >= k && k >= 0) {
		        List<Integer> lst = new ArrayList<>();
		        aux(ans, lst, 1, n, k);
		    }
		    return ans;
    }
}
