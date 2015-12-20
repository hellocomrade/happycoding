#include <string>
#include <bitset>
#include <iostream>

using namespace std;

/*
Implement an algorithm to determine if a string has all unique characters. What
if you cannot use additional data structures?
Assuming all characters are ascii (0 - 255), so a and A are not identical.
time complexity O(N)
space complexity O(1)

If you have good understanding on the meaning of O(1), this is really a trivial interview question.
O(1) means constant time or space.
For this case, since we know the range of characters is from 0 to 255 (ascii), reserving a space with
255 slots is still considered as O(1), since it's sufficient to handle all scenarios, no matter the length
of the string.
Therefore, we define a bitmap with 256 slots (0 - 255), that's exactly 8 bits or 1 bytes.

We can scan the sequence at most one time and keep the intermidate results using 1 bytes extra space.
*/
bool isAllUnqiueCharacter(const string &S)
{
	bitset<256> bmap;
	for (char c : S)
	{
		if (false == bmap.test((int)c))
			bmap.set((int)c, 1);
		else
			return false;
	}
	return true;
}
void testAllUnqiueCharacter()
{
	cout << "Expect 1: " << isAllUnqiueCharacter("abCd") << endl;
	cout << "Expect 1: " << isAllUnqiueCharacter("") << endl;
	cout << "Expect 1: " << isAllUnqiueCharacter("AaBb") << endl;
	cout << "Expect 0: " << isAllUnqiueCharacter("ABAB") << endl;
	cout << "Expect 0: " << isAllUnqiueCharacter("ABCDEFGHIA") << endl;
}