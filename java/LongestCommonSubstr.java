public class SolutionLongestCommonSubstr {
    /**
     * @param A, B: Two string.
     * @return: the length of the longest common substring.
     */
    public int longestCommonSubstring(String A, String B) {
        // write your code here
        int lena = A.length();
        int lenb = B.length();
        int[][] memo = new int[lena + 1][lenb + 1];
        int maxLen = 0;
        for(int i = 1; i <= lena; ++i) {
            for(int j = 1; j <= lenb; ++j) {
                if(A.charAt(i - 1) == B.charAt(j - 1)) {
                    memo[i][j] = memo[i - 1][j - 1] + 1;
                    maxLen = Math.max(memo[i][j], maxLen);
                }
            }
        }
        return maxLen;
    }
}
