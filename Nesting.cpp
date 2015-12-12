#include <cassert>
#include <string>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingCZ28VN-Y5E/

I didn't pass it, coz I didn't even think of ')(' :(
Trick:
If '(' count++, or count--
Counting back to 0 by the end means a valid nesting? No! For example:
")(", you will have to examine the count inside the loop. So anytime there is a negative count, return
immediately with 0
*/
*/
int solutionNesting(const string &S)
{
	if (true == S.empty())return 1;
	int count = 0;
	for (char c : S)
	{
		assert('(' == c || ')' == c);
		if ('(' == c)
			++count;
		else
			--count;
		if (count < 0)
			return 0;
	}
	return 0 == count;
}
void testNesting()
{
	cout << "Expect 1: " << solutionNesting("(()(())())") << endl;
	cout << "Expect 1: " << solutionNesting("") << endl;
	cout << "Expect 0: " << solutionNesting("())") << endl;
	cout << "Expect 0: " << solutionNesting("((((((((") << endl;
	cout << "Expect 0: " << solutionNesting("))))))))") << endl;
	cout << "Expect 1: " << solutionNesting("(()())") << endl;
	cout << "Expect 1: " << solutionNesting("()()") << endl;
	cout << "Expect 1: " << solutionNesting("((()))()()") << endl;
	cout << "Expect 0: " << solutionNesting(")(") << endl;
	cout << "Expect 0: " << solutionNesting("))())(()((") << endl;
	cout << "Expect 0: " << solutionNesting(")((") << endl;
	cout << "Expect 0: " << solutionNesting("(()))") << endl;
}