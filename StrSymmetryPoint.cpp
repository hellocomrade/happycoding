#include <string>
#include <iostream>
using namespace std;

//https://codility.com/demo/results/trainingZKG7R5-NHG/
int solutionStrSymmetryPoint(const string &S) {
    int len = S.length();
    int l = 0, h = len - 1;
    while(l < h)
    {
        if(S[l] == S[h])
        {
            ++l;
            --h;
        }
        else
            break;
    }
    return l == h ? l : -1;
}

void testStrSymmetryPoint()
{
    cout << "Expect 3: " << solutionStrSymmetryPoint("racecar") << endl;
    cout << "Expect 0: " << solutionStrSymmetryPoint("x") << endl;
    cout << "Expect -1: " << solutionStrSymmetryPoint("abc") << endl;
    cout << "Expect -1: " << solutionStrSymmetryPoint("") << endl;
}
