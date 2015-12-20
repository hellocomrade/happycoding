#include <vector>
#include <iostream>

using namespace std;

/*
Given two strings, write a method to decide if one is a permutation of the other.
AKA, Anagram
"bcda" is considered as the permutation of "abcd"

"ab cd" == "da bc"

Again, assuming all characters are in ascii (0-255)

Time complexity: O(N)
space complexity: O(1)
*/
bool anagramStrings(const string &S1, const string &S2)
{
	if (S1.length() != S2.length())
		return false;
	vector<int> counts(256, 0);
	for (char c : S1)
		++counts[(int)c];
	for (char c : S2)
	{
		//since we are sure at this point that s1 and s2 have the same length
		//we can safely tell whenever we see the count is negative, s1 and s2
		//are not anagram
		if (--counts[(int)c] < 0)
			return false;
	}
	return true;
}
void testAnagramStrings()
{
	cout << "Expect 1: " << anagramStrings("abcd", "dcab") << endl;
	cout << "Expect 1: " << anagramStrings("bbcc", "bcbc") << endl;
	cout << "Expect 1: " << anagramStrings("", "") << endl;
	cout << "Expect 1: " << anagramStrings("present", "repents") << endl;
	cout << "Expect 1: " << anagramStrings("rescue dba", "secured ab") << endl;
	cout << "Expect 1: " << anagramStrings("ab cd", "da bc") << endl;
	cout << "Expect 0: " << anagramStrings("abcd", "dzbb") << endl;
}