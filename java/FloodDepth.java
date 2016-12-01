//https://codility.com/demo/results/trainingEVR9TF-RJE/
class SolutionFloodDepth {
    public int solutionGetMaxDepth(int[] A) {
        int len = A.length, ans = 0;
        if(len > 2) {
            int left = 0, right = len - 1, leftMaxHeightSofar = 0, rightMaxHeightSofar = 0;
            while(left < right) {
                if(A[left] < A[right]) {
                    leftMaxHeightSofar = Math.max(A[left], leftMaxHeightSofar);
                    ans = Math.max(ans, leftMaxHeightSofar - A[left++]);
                }
                else {
                    rightMaxHeightSofar = Math.max(A[right], rightMaxHeightSofar);
                    ans = Math.max(ans, rightMaxHeightSofar - A[right--]);
                }
            }
        }
        return ans;
    }
    public int solutionGetTotalVolume(int[] A) {
        int len = A.length, ans = 0;
        if(len > 2) {
            int left = 0, right = len - 1, leftMaxHeightSofar = 0, rightMaxHeightSofar = 0;
            while(left < right) {
                if(A[left] < A[right]) {
                    leftMaxHeightSofar = Math.max(A[left], leftMaxHeightSofar);
                    ans += Math.max(0, leftMaxHeightSofar - A[left++]);
                }
                else {
                    rightMaxHeightSofar = Math.max(A[right], rightMaxHeightSofar);
                    ans += Math.max(0, rightMaxHeightSofar - A[right--]);
                }
            }
        }
        return ans;
    }
}
