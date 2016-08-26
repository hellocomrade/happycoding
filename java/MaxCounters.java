//https://codility.com/demo/results/training4SCUFZ-B5W/
/*
Please use the slider on the page above to see why you were wrong at the first place!
*/
class SolutionMaxCounter {
    public int[] solution(int N, int[] A) {
        int maxhere = 0, maxsofar = 0;
        int[] ans = new int[N];
        for(int i : A) {
            if(i == N + 1)
                maxsofar = maxhere;
            else {
                if(ans[i - 1] < maxsofar) ans[i - 1] = maxsofar + 1;
                else ans[i - 1] += 1;
                maxhere = Math.max(maxhere, ans[i - 1]);
            }
        }
        if(maxsofar > 0)
            for(int i = 0; i < N; ++i)
                if(ans[i] < maxsofar)
                    ans[i] = maxsofar;
        return ans;
    }
}
