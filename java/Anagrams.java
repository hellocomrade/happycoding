public class SolutionAnagrams {
    /**
     * @param s: The first string
     * @param b: The second string
     * @return true or false
     */
    public boolean anagram(String s, String t) {
        // write your code here
        if(s == null || t == null)return false;
        int lens = s.length();
        int lent = t.length();
        if(lens != lent)return false;
        char[] map = new char[256];
        for(int i = 0; i < lens; ++i)
            map[(int)s.charAt(i)]++;
        for(int i = 0; i < lens; ++i) {
            if(map[(int)t.charAt(i)] == 0)return false;
            map[(int)t.charAt(i)]--;
        }
        return true;
    }
};
