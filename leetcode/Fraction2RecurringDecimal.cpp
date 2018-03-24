#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;

//
/*
166. Fraction to Recurring Decimal

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".

Observations:

Math again, fortunately we can apply what we learnt in primary school noto this one directly:

Fraction to repeating decimal for rational numbers! If you feel strange about these terms, go over your math class notes
in basement...

Idea is:

- First figure out integer part by (numerator / denominator), then reminder of (numerator / denominator) and denominator
form the fraction, which can also be denoted as (numerator % denominator) / denominator

- Now it's ready for conversion! Since the reminder is less than denominator now, we will have to borrow/multiply 10 on the reminder of each division operation.
Say, 7 / 11, then we multiply 7 by 10 and then do 70 / 11, 6 will be the first decimal, the reminder 70 % 11 = 4 will be the numerator of next division against
denominator 11, 4 /11, of course, 4 tims 10 first then divided by 11. This is exactly the same approach if we do by hand.

- When should we stop division? Two ending conditions:

1. Reminder is 0 after the division, there is terminating decimal to represent this fraction!

2. Reminder is as same as the previous reminder, there is repeating decimal to represent the fraction.

Since we deal with rational number only, the above two conditions are sufficient to cover all.

- Question is how to find the previous repeated reminder? I first thought the repeated reminder will always be the
original (numerator % denominator). It's true for the case like 23 / 11, which is 2.(09). But there is also 7 / 12,
which has repeating decimal starts at the third digit 0.58(3).

So, there is really no way to tell which reminder should be kept, so we have to use hashtable here to track all previous
reminder on every division plus the index they are applied so we can reconstruct the string.

It's also interesting to discover that for a given fraction, the number of repeating decimal shall be no more than
1 + 2 + ... + denominator - 1. It's a huge number if we have to pick a data type other than string...

- Overflow issue: since the domain is all integers and we will have to do abs, then overflow on abs against INT_MIN shall
be considered. Using type long should be OK to cover all scenarios.

- 0 / -5 shall print 0, even though 0 and 5 have differnt signs! Therefore, rule out any numerator == 0 up front.
*/
class SolutionFraction2RecurringDecimal {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (0 == denominator)return "";
		else if (0 == numerator)return "0";
		stringstream ans, ssDecimal;
		ans << std::abs(1L * numerator / denominator);
		long dividend = std::abs(1L * numerator % denominator), divisor = std::abs(denominator * 1L), idx = 0;
		if (0 != dividend) {
			unordered_map<int, long> lastPos;
			do {
				lastPos.insert({ dividend, idx++ });
				ssDecimal << dividend * 10L / divisor;
				dividend = dividend * 10L % divisor;
			} while (0 != dividend && 0 == lastPos.count(dividend));
			string str = ssDecimal.str();
			if (0 == dividend) ans << '.' << str;
			else ans << '.' << str.substr(0, lastPos[dividend]) << '(' << str.substr(lastPos[dividend], string::npos) << ')';
		}
		return ((numerator > 0) ^ (denominator > 0)) ? '-' + ans.str() : ans.str();
	}
};
void TestFraction2RecurringDecimal() {
	SolutionFraction2RecurringDecimal so;
	assert("6.(5294117647058823)" == so.fractionToDecimal(111, 17));
	assert("2.(09)" == so.fractionToDecimal(23, 11));
	assert("0.58(3)" == so.fractionToDecimal(7, 12));
}
/*
Test cases:

0
1
0
-5
1
5
1
-5
-1
5
-1
-5
-2
1
23
11
111
12
111
17
1567
23
7
12
3227
555
6543210
123456
-2147483648
1
-2147483648
347
2147483647
1
2147483647
890123

Outputs:

"0"
"0"
"0.2"
"-0.2"
"-0.2"
"0.2"
"-2"
"2.(09)"
"9.25"
"6.(5294117647058823)"
"68.(1304347826086956521739)"
"0.58(3)"
"5.8(144)"
"53.00034(02021772939346811819595645412130637636080870917573872472783825816485225505443234836702954898911353032659409)"
"-2147483648"
"-6188713.(68299711815561959654178674351585014409221902017291066282420749279538904899135446685878962536023054755043227665706051873198847262247838616714697406340057636887608069164265129)"
"2147483647"

The last result was intentionally ignored...too long...
*/