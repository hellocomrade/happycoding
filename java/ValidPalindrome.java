//https://leetcode.com/problems/valid-palindrome/
public class SolutionValidPalindrome {
    public boolean isPalindrome(String s) {
        if(s == null)return false;
        int len = s.length();
        int i = 0, j = len - 1;
        while(i < j) {
            while(i < j && Character.isLetterOrDigit(s.charAt(i)) == false)++i;
            while(i < j && Character.isLetterOrDigit(s.charAt(j)) == false)--j;
            if(Character.toLowerCase(s.charAt(i++)) != Character.toLowerCase(s.charAt(j--)))return false;
        }
        return true;
    }
}
