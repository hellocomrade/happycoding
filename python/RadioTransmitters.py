# https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem
class SolutionRadioTransmitters:
    """
    @param n: the number of houses
    @param k: the range of the transmitter
    @param x: respective locations of each house
    @return: the minimum number of transmitters needed to cover every house in the city
    """
    def HackerlandRadioTransmitters(self, n, k, x):
        hdists, ans, tidx, left, i = sorted(set(x)), 0, 0, True, 1
        while i < len(hdists):
            if k <= hdists[i] - hdists[tidx]:
                if left:
                    ans += 1
                    left = True if 1 == i - tidx and k < hdists[i] - hdists[tidx] else False
                    tidx = i - 1 if i - tidx > 1 and k < hdists[i] - hdists[tidx] else i
                    if i - 1 == tidx:
                        i -= 1
                else:
                    tidx, left = i if k < hdists[i] - hdists[tidx] else i + 1, True
            i += 1
        return ans + 1 if True == left else ans
