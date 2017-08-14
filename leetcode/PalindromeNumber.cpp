#include <cmath>

//https://leetcode.com/problems/palindrome-number/
/*
9. Palindrome Number

Determine whether an integer is a palindrome. Do this without extra space.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.

Observations:
First, all negative numbers are not considered as palindromes because of the minus sign.

If you did "Reverse Integer" already, you could use the same trick and again, have to deal with integer overflow.
A popular solution is to reversing only half of the number which makes sense in terms of palindrome but more importantly,
integer overflow is avoided. In order to do that, make sure the loop terminates if reversed number is no less than x.
After exit from the loop, x is a palindrome:
- if x == reversed, this is the case when x has even number of digits
or
- if x == reversed / 10, this is the case when x has odd number of digits

There is an exception for this algorithm: if x is a number ends with 0, the above approach will fail. Fortunately,
if x ends with 0, x is not a palindrome for sure. Therefore, we could exclude such numbers at the beginning of the function
along with negative numbers.

I have a more generic approach that can actually conclude the palindrome inside the loop: by literally comparing
digits. In order to do that, we have to know the number of digits in x. This can be done in O(1), looks silly though.
It does require more instructions...
*/
class SolutionPalindromeNumber {
private:
	int digits(int x) {
		size_t y = std::abs(x);
		if (x < 10)return 1;
		if (x < 100)return 2;
		if (x < 1000)return 3;
		if (x < 10000)return 4;
		if (x < 100000)return 5;
		if (x < 1000000)return 6;
		if (x < 10000000)return 7;
		if (x < 100000000)return 8;
		if (x < 1000000000)return 9;
		return 10;
	}
public:
	bool isPalindrome(int x) {
		if (x < 0 || (x > 0 && 0 == x % 10))return false;
		int reversed = 0;
		while (reversed < x) {
			reversed = reversed * 10 + x % 10;
			x /= 10;
		}
		return reversed == x || reversed / 10 == x;
	}
	bool isPalindrome1(int x) {
		if (x < 0)return false;
		int dz = this->digits(x);
		int divisor = (int)std::pow(10, dz - 1);
		while (x > 0) {
			if (x / divisor != x % 10)return false;
			x = (x % divisor) / 10;
			divisor /= 100;
		}
		return true;
	}
};