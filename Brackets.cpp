#include <cassert>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingW9Z6JB-MC8/

I was extra careful this time to make sure that I wouldn't blow it up again :)

Shame on me for Nesting...
*/
int solutionBrackets(const string &S)
{
	stack<char> stk;
	for (char c : S)
	{
		switch (c)
		{
		case '{':
			stk.push('}');
			continue;
		case '[':
			stk.push(']');
			continue;
		case '(':
			stk.push(')');
			continue;
		default:
			break;
		}
		if (false == stk.empty() && stk.top() == c)
			stk.pop();
		else
			return 0;
	}
	return stk.empty();
}
void testBrackets()
{
	cout << "Expect 1: " << solutionBrackets("(()(())())") << endl;
	cout << "Expect 0: " << solutionBrackets("())") << endl;
	cout << "Expect 0: " << solutionBrackets("((((((((") << endl;
	cout << "Expect 0: " << solutionBrackets("))))))))") << endl;
	cout << "Expect 1: " << solutionBrackets("(()())") << endl;
	cout << "Expect 1: " << solutionBrackets("()()") << endl;
	cout << "Expect 1: " << solutionBrackets("((()))()()") << endl;
	cout << "Expect 0: " << solutionBrackets(")(") << endl;
	cout << "Expect 0: " << solutionBrackets("))())(()((") << endl;
	cout << "Expect 0: " << solutionBrackets(")((") << endl;
	cout << "Expect 0: " << solutionBrackets("(()))") << endl;
	cout << "Expect 1: " << solutionBrackets("{[()()]}") << endl;
	cout << "Expect 0: " << solutionBrackets("([)()]") << endl;
	cout << "Expect 1: " << solutionBrackets("") << endl;
	cout << "Expect 0: " << solutionBrackets("}])()([{") << endl;
	cout << "Expect 0: " << solutionBrackets("[(}(())())") << endl;
	cout << "Expect 1: " << solutionBrackets("[({([]{})})()]") << endl;
	cout << "Expect 0: " << solutionBrackets("[({([]{})])()]") << endl;
	cout << "Expect 0: " << solutionBrackets("[({([]{})})()[") << endl;
	cout << "Expect 1: " << solutionBrackets("[]{}()") << endl;
	cout << "Expect 1: " << solutionBrackets("[(){}]{}([])") << endl;
}
