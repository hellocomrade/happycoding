#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingGBMQ6H-9TZ/

Observation:
I didn't get this simple task done right at the first try, what's a shame! But what even more is that
it took me 15 minutes to figure out why I failed the permutation test! I did recognize that the sum will
overflow int, so I used long long. But I forgot to convert int X to long long during the calcuation. So,
actually (X+1)*X was still calculated with type int and then overflow and then the result was converted
to long long. What's a stupid mistake!

Actually, there is no need to do sum. Count is enough. So, I failed because I was stupid at the first place.
A stupid decision led to a more stupid result...

*/
//Wrong one: https://codility.com/demo/results/trainingBQG9ME-XZE/
int solutionFrogRiverOne1(int X, const vector<int> &A) {
    vector<bool> bv(X + 1, false);
    long long sum = ((long long)X + 1) * (long long)X / 2;
    int len = A.size();
    for (int i = 0; i < len; ++i)
    {
	if (false == bv[A[i]])
	{
 	    bv[A[i]] = true;
	    sum -= A[i];
	    if (0 == sum)
		return i;
	}	
    }
    return -1;
}
int solutionFrogRiverOne(int X, const vector<int> &A) {
    vector<bool> bv(X + 1, false);
    int len = A.size();
    for (int i = 0; i < len; ++i)
    {
	if (false == bv[A[i]])
	{
	    bv[A[i]] = true;
	    if (0 == --X)
		return i;
	}
    }
    return -1;
}
void testFrogRiverOne()
{
    cout << "Expect 6: " << solutionFrogRiverOne(5, vector<int>{ 1, 3, 1, 4, 2, 3, 5, 4 }) << endl;
}
