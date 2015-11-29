//https://codility.com/demo/take-sample-test/stone_wall/
#include <cassert>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

//skyline algorithm
//the intutive solution for minimizing the member of block is to merge shorter
//blocks together as long as they can form a base for taller buildings
//we use a stack to track the starting point of these bases and pop the most recent one
//if the next building is shorter than the base, which means this base ends
//here (reach its rightmost location)
int solutionStoneWall(vector<int>& H)
{
    int len = H.size();
    assert(len > 0);
    stack<int> packedBlock;
    packedBlock.push(H[0]);
    int count = 0, top=-1;
    for (int i = 1; i < len;++i)
    {
	while (!packedBlock.empty())
	{
  	    top = packedBlock.top();
	    if (top > H[i])
	    {
		packedBlock.pop();
		++count;
	    }
	    else
		break;
        }
	if (packedBlock.empty() || (!packedBlock.empty() && packedBlock.top() != H[i]))
	    packedBlock.push(H[i]);
    }
    return count + packedBlock.size();
}
void testStoneWall()
{
	cout << "Expect 7: " << solutionStoneWall(vector<int>({8,8,5,7,9,8,7,4,8})) << endl;
	cout << "Expect 1: " << solutionStoneWall(vector<int>({8})) << endl;
	cout << "Expect 1: " << solutionStoneWall(vector<int>({ 8, 8 })) << endl;
	cout << "Expect 3: " << solutionStoneWall(vector<int>({ 8, 8, 7, 8 })) << endl;
	cout << "Expect 2: " << solutionStoneWall(vector<int>({ 7, 7, 8, 7 })) << endl;
}
