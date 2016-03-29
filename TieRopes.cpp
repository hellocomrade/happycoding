#include <vector>

using namespace std;

/*
https://codility.com/demo/results/trainingWNZ3VG-AR9/
*/
int solutionTieRopes(int K, vector<int> &A) {
	int cnt = 0;
	long long sum = 0;
	for (int i : A)
	{
		sum += i;
		if (sum >= K)
		{
			sum = 0;
			++cnt;
		}
	}
	return cnt;
}