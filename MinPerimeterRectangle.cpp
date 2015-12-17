#include <cassert>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingZUFYF2-E94/
*/
int solutionMinPerimeterRectangle1(int N)
{
	assert(N > 0);
	int len = 1, minPerimeter = numeric_limits<int>::max();
	while (len*len <= N)
	{
		if (0 == N % len)
			minPerimeter = std::min(minPerimeter, 2 * (N / len + len));
		++len;
	}
	return minPerimeter;
}
/*
Observation:
If a rectangle has the min perimeter, the two lengthes, len1, and len2 meets:

min(abs(len1-len2))

For example:
If area is 36, then the min permieter comes from len1=6 and len2=6, since 6-6 =0
if area is 30, then the min permieter comes from 5 and 6

With this, we could have a slightly faster alogirhtm by starting the scan from sqrt(N) to 1, since it the pivot
point. the first divisor will be the answer.
*/
int solutionMinPerimeterRectangle(int N)
{
	assert(N > 0);
	int len = (int)sqrt(N), minPerimeter = numeric_limits<int>::max();
	while (len > 0)
	{
		if (0 == N % len)
			return 2 * (N / len + len);
		--len;
	}
	return 0;
}
void testMinPerimeterRectangle()
{
	cout << "Expect 36: " << solutionMinPerimeterRectangle(17) << endl;
	cout << "Expect 22: " << solutionMinPerimeterRectangle(30) << endl;
	cout << "Expect 24: " << solutionMinPerimeterRectangle(36) << endl;
	cout << "Expect 4: " << solutionMinPerimeterRectangle(1) << endl;
	cout << "Expect 40: " << solutionMinPerimeterRectangle(100) << endl;
	cout << "Expect 126500: " << solutionMinPerimeterRectangle(1000000000) << endl;
}