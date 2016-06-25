//https://codility.com/demo/results/trainingPC92RP-4FE/
class SolutionCountSemiprimes {
    private int[] factorization(int N) {
        int[] fact = new int[N + 1];
        fact[0] = fact[1] = 1;
        int i = 2, k = 0;
        while(i * i <= N) {
            if(fact[i] == 0){
                k = i * i;
                while(k <= N) {
                    if(fact[k] == 0) {
                        fact[k] = i;
                    }
                    k += i;
                }
            }
            ++i;
        }
        return fact;
    }
    public int[] solution(int N, int[] P, int[] Q) {
        // write your code in Java SE 8
        int[] factors = factorization(N);
        int[] memo = new int[N + 1];
        int len = P.length;
        int[] ans = new int[len];
        memo[0] = memo[1] = 0;
        for(int i = 2; i < N + 1; ++i) {
            memo[i] = memo[i - 1];
            if(factors[i] != 0 && factors[i / factors[i]] == 0)
                ++memo[i];
        }
        for(int i = 0; i< len; ++i)
            ans[i] = memo[Q[i]] - memo[P[i] - 1];
        return ans;
    }
}
