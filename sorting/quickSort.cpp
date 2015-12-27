#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

/*
Insert sort takes O(N^2) time and works efficiently in small amount of datasets.
The loop start from 1, and the inner loop always check the index from 0 to i-1 and comparing their value 
with A[i]. If, say, value at j=i - k is greater than A[i], move its value to i-k+1. The inner loop ends
if A[j-1] is no greater than A[i]. Then we put A[i]'s value at index j, whose original value, since it's
bigger than A[i], was moved to j+1. So we can safely put A[i]'s value at index j.

At this moment, all values from index 0 to j-1 is no greater than A[j]

We keep this process, until the outter loop is done. The entire sequeuce should be sorted by now.
*/
template<typename T>
void insertSort(vector<T> &A)
{
	int len = A.size();
	int j, k = 0, tmp = 0;
	for (int i = 1; i < len; ++i)
	{
		k = A[i];
		for (j = i; j > 0 && A[j - 1] > k; --j)
			A[j] = A[j - 1];
		A[j] = k;
	}
}
/*
Quick sort has overall NlogN time complexity, without proper implementation, its time complexity could drop
to N^2. For example:
1. A sorted sequence, [1,2,3,4,5], if we take pviot at index 0 (1), after the first partition, we will have
[1], [2,3,4,5]. then [1][2], [3,4,5]..., it will be n+(n-1)+(n-2)+..+1, N^2
2. A sequence with all identical values, if we don't swap them in the implementation of quick sort
[1,1,1,1,1], after the first parition, it will be like [1], [1,1,1,1]. So, it's exactly like case 1.
3. It has been proved, if the sequence is smaller enough, insert sort could have better performance.

Why we use do while, instead of while? After a swap is done in the infinite loop, i and j remain their last
value, although the swap has been done. The first look seems OK, A[l] will be less than pivot, and A[h] should
be greater than pivot. However, since we intentinally require to swap the values that is identical to pivot,
if both A[l] and A[h] are equal to pivot, the two while loops will break immediately and swap them again. So we
fall into a infinite loop forever. Of course, we could do ++l, --h after swap, but what if these make l>h, we should
break from the whole loop by now, so we also have to move this check to the top of the loop, before two while loops.

Using do while can free us from this complication, at least to me, I think it's simpler.

Why we have l <= high in the first while condition but no such check for h in the second while condition?
There is no way for h to be less than low because 'A[h] > p' implies that h will stop at low (p=A[low])
*/
#define COMBINED
const int SORT_BOUNDARY = 6;
template<typename T>
void quickSort(vector<T> &A, int low, int high)
{
#ifdef COMBINED
	if (high - low <= SORT_BOUNDARY)return;
#else
	if (low >= high)return;
#endif
	srand(time(NULL));
	int r = rand() % (high - low + 1);
	std::swap(A[low], A[low + r]);
	int p = A[low], l = low, h = high + 1;
	while (true)
	{
		do
		{
			++l;
		} while (l <= high && A[l] < p);
		do
		{
			--h;
		} while (A[h] > p);
		if (l > h)
			break;
		std::swap(A[l], A[h]);
	}
	std::swap(A[low], A[h]);
	quickSort(A, low, h - 1);
	quickSort(A, h + 1, high);
}
template<typename T>
void QuickSort(vector<T> &A, int low, int high)
{
	quickSort(A, low, high);
	insertSort(A);
}
void printSortingResult(const vector<int> &A)
{
	for (int i : A)
		cout << i << ',';
	cout << endl;
}
void testCombinedQuickSort()
{
	vector<int> vec1({ 8, 7, 5, 10, 2, 3, 6, 10, 15, 1, 3, 3, 17, 24, 6 });
	QuickSort(vec1, 0, vec1.size() - 1);
	printSortingResult(vec1);
}
void testQuickSort()
{
	vector<int> vec1({ 8, 7, 5, 10, 2, 3, 6 });
	quickSort(vec1, 0, vec1.size() - 1);
	printSortingResult(vec1);

	vector<int> vec2({ 1, 2, 3, 4 });
	quickSort(vec2, 0, vec2.size() - 1);
	printSortingResult(vec2);

	vector<int> vec3({ 4, 3, 2, 1 });
	quickSort(vec3, 0, vec3.size() - 1);
	printSortingResult(vec3);

	vector<int> vec4({ 2, 1 });
	quickSort(vec4, 0, vec4.size() - 1);
	printSortingResult(vec4);

	vector<int> vec5({ 1 });
	quickSort(vec5, 0, vec5.size() - 1);
	printSortingResult(vec5);

	vector<int> vec6({});
	quickSort(vec6, 0, vec6.size() - 1);
	printSortingResult(vec6);
}
void testInsertSort()
{
	vector<int> vec1({ 8, 7, 5, 10, 2, 3, 6 });
	insertSort(vec1);
	printSortingResult(vec1);

	vector<int> vec2({ 1, 2, 3, 4 });
	insertSort(vec2);
	printSortingResult(vec2);

	vector<int> vec3({ 4, 3, 2, 1 });
	insertSort(vec3);
	printSortingResult(vec3);

	vector<int> vec4({ 2, 1 });
	insertSort(vec4);
	printSortingResult(vec4);

	vector<int> vec5({ 1 });
	insertSort(vec5);
	printSortingResult(vec5);

	vector<int> vec6({});
	insertSort(vec6);
	printSortingResult(vec6);
}