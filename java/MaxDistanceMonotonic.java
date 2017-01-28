//https://codility.com/demo/results/trainingD9T59Y-V3V/

/*
This is actually a O(NlogN) solution, but Codility say otherwise:) They need better, longer test cases.
The O(N) solution will be added later. So it's here:https://codility.com/demo/results/training8NVKBY-RE8/
*/
import java.util.Stack;
import java.util.Collections;
import java.util.ArrayList;
class SolutionMaxDistanceMonotonic {
    static class Pair {
        public int val;
        public int idx;
        public Pair(int val, int idx) {
            this.val = val;
            this.idx = idx;
        }    
    }
    //O(N)
    public int solution(int[] A) {
        int ans = 0;
        Stack<Pair> stk = new Stack<>();
        stk.push(new Pair(A[A.length - 1], A.length - 1));
        for(int i = A.length - 2; i > -1; --i)
            if(A[i] > stk.peek().val)stk.push(new Pair(A[i], i));
        for(int i = 0; i < A.length && !stk.empty(); ++i) {
            while(false == stk.empty() && A[i] <= stk.peek().val) {
                ans = Math.max(ans, stk.peek().idx - i);
                stk.pop();
            }
        }
        return ans;
    }
    //O(NlogN)
    public int solution1(int[] A) {
        int ans = 0, min = A.length;
        ArrayList<Solution.Pair> lst = new ArrayList<>();
        for(int i = 0; i < A.length; ++i)
            lst.add(new Solution.Pair(A[i], i));
        Collections.sort(lst, (i, j) -> i.val < j.val ? -1 : i.val == j.val ? 0 : 1);
        for(Pair i : lst) {
            if(i.idx < min)min = i.idx;
            ans = Math.max(ans, i.idx - min);
        }
        return ans;
    }
}
