#https://codility.com/demo/results/training3A4DDM-K2V/
def solution(A):
    # write your code in Python 2.7
    size = len(A)
    cnt, cnt1, s, ans = 0, 0, 0, 0
    for i in A:
        if 0 == cnt:
            s = i
        if s == i:
            cnt += 1
        else:
            cnt -= 1
    cnt = A.count(s)
    if cnt > size // 2:
        for i in range(size):
            if A[i] == s:
                cnt1 += 1
            if cnt1 > (i + 1) // 2 and cnt - cnt1 > (size - 1 - i) // 2:
                ans += 1
    return ans
