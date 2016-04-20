//https://codility.com/demo/results/trainingM9TEHW-A9W/
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> solutionGenomicRangeQuery(string &S, const vector<int> &P, const vector<int> &Q) 
{
    int lenp = P.size();
    int lenq = Q.size();
    assert(lenp>0);
    assert(lenp == lenq);
    unordered_map<char, const int> map = { { 'A', 1 }, { 'C', 2 }, { 'G', 3 }, { 'T', 4 } };
    int strLen = S.length();
    //memorize the next index(dist) value of A,C,G,T at 1st, 2nd, 3rd and 4th rows
    //so we will know if P.startIndex is at this position, how far can we see a A,C,G,T
    vector<vector<int> > memorization;
    memorization.push_back(vector<int>(0, 0));//dummy array for avoiding minus 1 inside [], less messy looking
    memorization.push_back(vector<int>(strLen, -1));
    memorization.push_back(vector<int>(strLen, -1));
    memorization.push_back(vector<int>(strLen, -1));
    memorization.push_back(vector<int>(strLen, -1));
    memorization[map[S[strLen - 1]]][strLen - 1] = strLen - 1;
    for (int i = strLen - 2; i >= 0; --i)
    {
	memorization[1][i] = memorization[1][i + 1];
	memorization[2][i] = memorization[2][i + 1];
	memorization[3][i] = memorization[3][i + 1];
	memorization[4][i] = memorization[4][i + 1];
	//overwrite the carry over from existing values after the assigment above to avoid a 'for' inner loop
	memorization[map[S[i]]][i] = i;
    }
    vector<int> result;
    int startIdx, endIdx;
    //Since we only have 4 impact value branches (1, 2, 3, 4) and we are looking for the min
    //branching starts from 1 to 4
    for (int i = 0; i < lenp; ++i)
    {
	startIdx = P[i];
	endIdx = Q[i];
	//check all impact values in asc order to see which one is in the reach from startIdx to endIdx
	if (memorization[1][startIdx] != -1 && memorization[1][startIdx] <= endIdx)
	    result.push_back(1);
	else if (memorization[2][startIdx] != -1 && memorization[2][startIdx] <= endIdx)
	    result.push_back(2);
	else if (memorization[3][startIdx] != -1 && memorization[3][startIdx] <= endIdx)
	    result.push_back(3);
	else if (memorization[4][startIdx] != -1 && memorization[4][startIdx] <= endIdx)
	    result.push_back(4);
    }
    return result;
}
void testGenomicRangeQuery()
{
    string s = "CAGCCTA";
    vector<int> result = solutionGenomicRangeQuery(s, vector<int>({ 2,5,0 }), vector<int>({ 4,5,6 }));
}
