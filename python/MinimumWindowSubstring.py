class SolutionMinimumWindowSubstring:
    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        map, sizeS, sizeT, l, r, zeroCnt = {}, len(s), len(t), 0, 0, 0
        ans, ans1 = 0, sizeS
        # Leetcode test cases don't handle the case like ["ABC", ""] or ["", ""] correctly
        if 0 == sizeS or 0 == sizeT:
            return ""
        for c in t:
            map[c] = 1 if c not in map else map[c] + 1
        while r < sizeS:
            if s[r] in map:
                if map[s[r]] > 0:
                    zeroCnt += 1
                map[s[r]] -= 1
            while sizeT == zeroCnt:
                if r - l < ans1 - ans:
                    ans, ans1 = l, r
                if s[l] in map:
                    map[s[l]] += 1
                    if map[s[l]] > 0:
                        zeroCnt -= 1
                l += 1
            r += 1
        return s[ans : ans1 + 1] if ans1 < sizeS else ""
