#include <vector>
#include <set>
#include <iostream>

using namespace std;

/*
 * https://codility.com/demo/results/trainingVFQ3M2-ZU7/
 *
 * expected worst-case time complexity is O(N*log(N));
 * expected worst-case space complexity is O(N)
 *
 * Since C++ STL offers container set, which is a red-black tree implementation that doesn't allow
 * duplicates, we simply take advantage of it.
*/
int solutionDistinct(vector<int> &A)
{
    set<int> tree;
    for (int i : A)
	tree.insert(i);
    return tree.size();
}
void testDistinct()
{
    cout << "Expect 3: " << solutionDistinct(vector<int>({2, 1, 1, 2, 3, 1})) << endl;
    cout << "Expect 0: " << solutionDistinct(vector<int>({})) << endl;
    cout << "Expect 1: " << solutionDistinct(vector<int>({1})) << endl;
    cout << "Expect 2: " << solutionDistinct(vector<int>({1, 2})) << endl;
    cout << "Expect 1: " << solutionDistinct(vector<int>({ 2, 2 })) << endl;
    cout << "Expect 5: " << solutionDistinct(vector<int>({ -10000, 10000, 10, 50, 20, 10 })) << endl;
    cout << "Expect 6: " << solutionDistinct(vector<int>({ -10000, 10000, 10, 50, 20, 11 })) << endl;
}
