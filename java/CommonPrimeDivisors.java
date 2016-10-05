class SolutionCommonPrimeDivisors {
    private int gcd(int a, int b) {
        return 0 == b ? a : gcd(b, a % b);
    }
    public int solution(int[] A, int[] B) {
        int ans = 0, a = 0, b = 0, d = 0, dd = 0;
        for(int i = 0; i < A.length; ++i) {
            d = dd = gcd(A[i], B[i]);
            a = A[i];
            b = B[i];
            while(1 != d) {
                a /= d;
                d = gcd(a, d);
            }
            while(1 != dd) {
                b /= dd;
                dd = gcd(b, dd);
            }
            if(1 == a && 1 == b)++ans;
        }
        return ans;
    }
}
