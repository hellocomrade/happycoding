//https://codility.com/demo/results/trainingDZUZXX-SPQ/
#include <cassert>
#include <vector>

using namespace std:

int solutionPassingCars(vector<int> &A)
{
    int len = A.size();
    assert(len > 0);
    int eastbound = 0;
    int passing = 0;
    for (int dir : A)
    {
	assert(dir == 0 || dir == 1);
	if (0 == dir)
	    ++eastbound;
	else
	    passing += eastbound;
	if (passing > 1e9)
	    return -1;
    }
    return passing;
}
void testPassingCars()
{
    cout << "Expect 5: " << solutionPassingCars(vector<int>({0,1,0,1,1})) << endl;
    cout << "Expect 0: " << solutionPassingCars(vector<int>({ 0 })) << endl;
    cout << "Expect 0: " << solutionPassingCars(vector<int>({ 1, 1, 1, 1 })) << endl;
    cout << "Expect 0: " << solutionPassingCars(vector<int>({ 0, 0, 0, 0 })) << endl;
    cout << "Expect 0: " << solutionPassingCars(vector<int>({ 1, 1, 1, 0 })) << endl;
    cout << "Expect 3: " << solutionPassingCars(vector<int>({ 0, 1, 1, 1 })) << endl;
    cout << "Expect 0: " << solutionPassingCars(vector<int>({ 1 })) << endl;
    cout << "Expect 1: " << solutionPassingCars(vector<int>({ 0, 1 })) << endl;
    cout << "Expect 0: " << solutionPassingCars(vector<int>({ 1, 0 })) << endl;
    cout << "Expect 4: " << solutionPassingCars(vector<int>({ 1, 0, 1, 1, 0, 1, 0 })) << endl;
}
