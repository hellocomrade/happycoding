#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;
using IntPair = std::pair<int, int>;
static int arrayInversionCountAux1(const vector<int> &A, const vector<IntPair> &Sorted, int idx, int start, int end)
{
	if (start > end || idx == A.size())return 0;
	//cout << "Find " << A[idx] << "[" << idx << "] in " << start << "," << end << endl;
	IntPair *ptr = (IntPair*)std::bsearch(&A[idx], Sorted.data() + start, end - start + 1, sizeof(IntPair), [](const void *v1, const void *v2) -> int {return (*(IntPair*)v1).first < (*(IntPair*)v2).first ? -1 : (*(IntPair*)v1).first >(*(IntPair*)v2).first ? 1 : 0; });
	int cnt = 0;
	if (nullptr == ptr)
	{
		cnt = A[idx] > Sorted[end].first ? end - start + 1 : 0;
		return cnt + arrayInversionCountAux1(A, Sorted, idx + 1, start, end);
	}
	else
	{
		IntPair *ptr1 = ptr;
		while (ptr1->first == A[idx] && ptr1->second != idx && ptr1 > Sorted.data())
			--ptr1;
		if (ptr1->first != A[idx] || ptr1->second != idx)
		{
			ptr1 = ptr;
			while (ptr1->first == A[idx] && ptr1->second != idx && ptr1 - Sorted.data() <= end)
				++ptr1;
		}
		ptr = ptr1;
	}
	cnt = ptr - Sorted.data() - start;
	int cntl = arrayInversionCountAux1(A, Sorted, idx + 1, start, start + cnt - 1);
	int	cntr = arrayInversionCountAux1(A, Sorted, idx + 1, start + cnt + 1, end);
	//cout << "For up to " << A[idx] << "[" << idx << "]" << " found: " << cnt + cntl + cntr << endl;
	if (cntl == -1 || cntr == -1)return -1;
	else if (cnt + cntl + cntr > 1e9)return -1;
	else return cnt + cntl + cntr;
}
//https://codility.com/demo/results/trainingHQRF22-AXP/
/*
try to make the case of O(NLogN), but failed...:(
*/
int solutionArrayInversionCount1(const vector<int> &A)
{
	int len = A.size();
	int count = 0;
	vector<std::pair<int, int> > vec;
	for (int i = 0; i < len; ++i)
		vec.emplace_back(A[i], i);
	std::sort(vec.begin(), vec.end(), std::less<IntPair>());
	count = arrayInversionCountAux1(A, vec, 0, 0, len - 1);
	return count >(int)1e9 ? -1 : count;
}

//http://www.geeksforgeeks.org/counting-inversions/
//https://codility.com/demo/results/training7682SD-JNQ/
/*
Observation:
The counting is done during the merge procedure of merge sort using the trick:

for two sorted sub sequence split from A[low, high]: [low, mid] and [mid + 1, high], at each merge step, the relative order in the original array is reserved between
any element with index i in [low, mid] and j in [mid + 1, high]. Therefore, if A[i] > A[j], then we could say that
all elements in the first half from i to mid have the inverse order with A[j], there are mid - i + 1 of them
*/
static int merge(vector<int> &A, vector<int> &B, int left, int mid, int right)
{
	int count = 0;
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right)
	{
		if (A[i] <= A[j])
			B[k++] = A[i++];
		else
		{
			B[k++] = A[j++];
			count += mid - i + 1;
		}
	}
	while (i <= mid)
		B[k++] = A[i++];
	while (j <= right)
		B[k++] = A[j++];
	return count > 1e9 ? -1 : count;
}
static int mergeSort(vector<int> &A, vector<int> &B, int start, int end)
{
	int cnt = 0, tmp = 0;
	int mid;
	if (start < end)
	{
		mid = start + (end - start) / 2;
		cnt = mergeSort(A, B, start, mid);
		if (cnt == -1) return -1;
		tmp = mergeSort(A, B, mid + 1, end);
		if (tmp == -1) return -1;
		cnt += tmp;
		tmp = merge(A, B, start, mid, end);
		if (tmp == -1) return -1;
		cnt += tmp;
		if (cnt > 1e9) return -1;
		std::copy(B.begin() + start, B.begin() + end + 1, A.begin() + start);
	}
	return cnt;
}

int solutionArrayInversionCount0(vector<int> &A)
{
	vector<int> B(A.size(), 0);
	return mergeSort(A, B, 0, A.size() - 1);
}
//https://app.codility.com/demo/results/training4T7V5N-BBV/
//Redo after 3 years
int solutionArrayInversionCount(vector<int> &A) {
    int len = (int)A.size();
    vector<int> aux(len, 0);
    long long ans = 0LL;
    auto merge = [&A, &aux](int l, int mid, int r) -> long long {
        int lr = mid, i = l;
        long long cnt = 0;
        while(l < mid && lr < r) aux[i++] = (A[l] <= A[lr]) ? A[l++] : (cnt += (mid - l), A[lr++]);
        while(l < mid) aux[i++] = A[l++];
        while(lr < r) aux[i++] = A[lr++];
        return cnt;
    };
    for(int i = 1; i < len; std::copy(aux.begin(), aux.end(), A.begin()), i <<= 1)
        for(int j = 0; j + i < len; j += 2 * i) {
            ans += merge(j, j + i, std::min(len, j + 2 * i));
            if(ans > 1000000000) return -1;
        }
    return static_cast<int>(ans);
}
void testArrayInversionCount()
{
	vector<int> foo{ 1, 2, 3, 4 };
	int i = 3;
	int *p = (int*)std::bsearch(&i, foo.data(), 4, sizeof(int), [](const void *v1, const void *v2) -> int {return (*(int*)v1 < *(int*)v2) ? -1 : (*(int*)v1 > *(int*)v2) ? 1 : 0; });
	if (p != nullptr)
		i = p - foo.data();
	vector<int> bar{ 2, 1, 4, 2 };
	solutionArrayInversionCount(bar);
	vector<int> vec1{ 3, 2, 1, 0 };
	cout << "Expect 6: " << solutionArrayInversionCount(vec1) << endl;
	vector<int> vec2{ -1, 6, 3, 4, 7, 4 };
	cout << "Expect 4: " << solutionArrayInversionCount(vec2) << endl;
	vector<int> vec3{ -1, 6, 3, 4, 7 };
	cout << "Expect 2: " << solutionArrayInversionCount(vec3) << endl;
	vector<int> vec4{ 1, 2, 3, 4 };
	cout << "Expect 0: " << solutionArrayInversionCount(vec4) << endl;
	vector<int> vec5{ 10, 2, 3, 4, 1, 0, -1 };
	cout << "Expect 18: " << solutionArrayInversionCount(vec5) << endl;
	vector<int> vec6{ 10, 2, 2, 2 };
	cout << "Expect 3: " << solutionArrayInversionCount(vec6) << endl;
	vector<int> vec7{ 10, 2, 2, 2, 1 };
	cout << "Expect 7: " << solutionArrayInversionCount(vec7) << endl;
	vector<int> vec8{};
	cout << "Expect 0: " << solutionArrayInversionCount(vec8) << endl;
	vector<int> vec9{1};
	cout << "Expect 0: " << solutionArrayInversionCount(vec9) << endl;
}
