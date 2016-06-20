#http://www.lintcode.com/en/problem/two-strings-are-anagrams/
class SolutionValidAnagrams:
    """
    @param s: The first string
    @param b: The second string
    @return true or false
    """
    def anagram(self, s, t):
        # write your code here
        dict = {}
        len1, len2 = len(s), len(t)
        if len1 != len2:
            return False
        for c in s:
            dict[c] = dict[c] + 1 if dict.has_key(c) else 1
        for c in t:
            if dict.has_key(c):
                dict[c] -= 1  
            else:
                return False
        for c in dict.values():
            if c != 0:
                return False
        return True
