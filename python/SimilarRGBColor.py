# https://www.lintcode.com/problem/similar-rgb-color/description
class SolutionSimilarRGBColor:
    """
    @param color: the given color
    @return: a 7 character color that is most similar to the given color
    """
    def similarRGB(self, color):
        lst = ['#', '', '', '', '', '', '']
        for i in range(1, 6, 2):
            j = int(color[i : i + 2], 16)
            j = j // 0x11 + (1 if j % 0x11 > 8 else 0)
            lst[i] = lst[i + 1] = chr(ord('0') + j) if j < 10 else chr(j - 10 + ord('a'))
        return ''.join(lst)
