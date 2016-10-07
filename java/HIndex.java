public class SolutionHIndex {
    //O(N) space + O(N) time    
    public int hIndex(int[] citations) {
        int len = citations.length, noLessThanCnt = 0;
        if(len > 0) {
            int[] counters = new int[len + 1];
            for(int i = 0; i < len; ++i)
                ++counters[Math.min(len, citations[i])];
            //i here represents possible h-index value from len to 0    
            for(int i = len; i > -1; --i) {
                //noLessThanCnt holds the count of elements that are no less than i
                noLessThanCnt += counters[i];
                /*
                '>' is necessary, for example [1,1], when possible h-index value is 1 (i = 1), noLessThanCnt = 2
                since the last noLessThanCnt at i + 1 is smaller than i + 1, we can conclude that the extra contributation
                for noLessThanCnt, which results in a no less than i situation, comes from the number of elements that are
                equal to i
                */
                if(noLessThanCnt >= i)
                    return i;
            }
        }
        return 0;
    }
    //O(1) space + O(NlogN) time
    public int hIndex1(int[] citations) {
        int len = citations.length, i = 0;
        int ans = len;
        if(ans > 0) {
            Arrays.sort(citations);
            while(i < len && citations[i] < ans){
                --ans;
                ++i;
            }
        }
        return ans;
    }
    public int hIndex2(int[] citations) {
        int len = citations.length;
        if(len > 0) {
            Arrays.sort(citations);
            int i = len;
            //Since I didn't find an elegant way to sort an int (primitive type) array in no increasing order, the following
            //conditions look ugly!
            while(i > 0 && citations[i - 1] >= len - i + 1)
                --i;
            return len - i;
        }
        return 0;
    }
}
