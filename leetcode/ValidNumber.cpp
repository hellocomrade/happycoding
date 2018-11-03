#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/valid-number/
/*
65. Valid Number

Validate if a given string can be interpreted as a decimal number.

Some examples:

"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. However, here is a list of characters that can be in a valid decimal number:

- Numbers 0-9
- Exponent - "e"
- Positive/negative sign - "+"/"-"
- Decimal point - "."

Of course, the context of these characters also matters in the input.

Observations:

This problem should have a linear solution for sure. isNumber0 is the naive but straightforward solution:

Using two pointers.

1. First skipping all heading and tailing spaces. If the pointer at the left side has not gone out of string length yet,
skipping possible '+' or '-' for once. After all these are done, if left side pointer crosses the right side pointer
already, an invalid string is confirmed. This procedure will rule out the edge case as "", " ", "+", "-".
If there is still letters between left and right pointers, moving to step two after the original left pointer position
is saved in k.

2. In a while loop, examine character one by one:
- If the char is a digit, ++left pointer;
- If the char is '.':
- If '.' or 'e' appears before, the string is illegal;
- If '.' is immediated followed by 'e' and no digit before '.', the string is illegal;
- Otherwise, ++left pointer;
- If the char is 'e':
- If 'e' appears before, the string is illegal;
- If 'e' is at the beginning or the end of the remaining string after step 1, the string is illegal;
- If 'e' is immedately followed by '+' and '-'. But no digit following the '+' or '-', the string is illegal;
- Otherwise, increase left pointer by 2 or 1 depending on if '+'/'-' is after 'e';

3. If the loop exits, the string is guaranteed a valid number.

The above approach works but there are lots of edge cases to cover and error prone.

There is actually a more elgant solution based upon Deterministic Finite Automata (DFA):

https://en.wikipedia.org/wiki/Deterministic_finite_automaton

http://shivankaul.com/blog/cstheory/compilers/2017/03/01/nfa-dfa-and-regexes.html

Personally, this is my first algorithm solved by DFA. Of course, I learnt it from others:

https://leetcode.com/problems/valid-number/discuss/23728/A-simple-solution-in-Python-based-on-DFA

Honestly speaking, if one can't carry out the naive solution during the interview, figuring out DFA is not
possible either! How could one guarantee DFA works for this problem without thinking through?

Once the states are defined, transition is as simple as looking up. The initial state index is 0.
The string is valid if and only if the ending state index is 2 or 4 or 7 or 8, which indicates the ending
of a valid numbe string is always a digit or a space or a dot. There are two states (index 2 and 7) with digit
as the incoming symbol, which decides the state moving into this state.

The lambda function "transit" is not necessary and only for demonstration purpose.

Finite State Automata are abstract models of computation. In other words, they are sytems that take input (in form of symbols) and spit out a result (or, perform a computation). To do this, they read symbols and move internally between states. They can be described by 3 things:

- Starting state
- List of states
- Transitions between states

"Transitions between states" can also be thought of as a function that takes as arguments the current state and current symbol and returns what the next state should be.
*/
class SolutionValidNumber {
public:
	/*
	Symbols:
	blank -> "blank"
	digit -> "digit"
	sign -> "sign"
	decimal point -> "dot"
	exponent -> "e"

	Each state is a hash table, with possible symbols as keys, the index for the next state for the specific symbol
	as the value.
	*/
	bool isNumber(string s) {
		vector<unordered_map<string, int>> states{
			{ { "blank", 0 },{ "sign", 1 },{ "digit", 2 },{ "dot", 3 } },
			{ { "digit", 2 },{ "dot", 3 } },
			{ { "digit", 2 },{ "dot", 4 },{ "e", 5 },{ "blank", 8 } },
			{ { "digit", 4 } },
			{ { "digit", 4 },{ "e", 5 },{ "blank", 8 } },
			{ { "sign", 6 },{ "digit", 7 } },
			{ { "digit", 7 } },
			{ { "digit", 7 },{ "blank", 8 } },
			{ { "blank", 8 } }
		};
		auto transit = [&states](int stateIndex, const string& symbol) -> int {
			if (0 > stateIndex && 8 < stateIndex) return -1;
			return (1 == states[stateIndex].count(symbol)) ? states[stateIndex][symbol] : -1;
		};
		int stateIdx = 0;
		string symbol;
		for (char c : s) {
			symbol = "";
			if (0 != isdigit(c)) symbol = "digit";
			else if ('+' == c || '-' == c) symbol = "sign";
			else if ('.' == c) symbol = "dot";
			else if ('e' == c) symbol = "e";
			else if (' ' == c) symbol = "blank";
			stateIdx = transit(stateIdx, symbol);
			if (-1 == stateIdx) return false;
		}
		return 2 == stateIdx || 4 == stateIdx || 7 == stateIdx || 8 == stateIdx;
	}
	bool isNumber0(string s) {
		long len = (long)s.length(), i = 0L, j = len - 1L, k = 0L;
		bool hasE = false, hasDP = false;
		while (i < len && ' ' == s[i]) ++i;
		while (-1 < j && ' ' == s[j]) --j;
		if (i < len && ('-' == s[i] || '+' == s[i])) ++i;
		if (i > j) return false;
		k = i;
		while (i <= j) {
			if (0 != isdigit(s[i])) ++i;
			else if (false == hasE && false == hasDP && '.' == s[i]) {
				if (i == k && (i + 1 > j || 'e' == s[i + 1])) return false;
				hasDP = true;
				++i;
			}
			else if ('e' == s[i] && i > k && i < j && false == hasE) {
				i = ('-' == s[i + 1] || '+' == s[i + 1]) ? i + 2 : i + 1;
				if (i > j) return false;
				hasE = true;
			}
			else return false;
		}
		return true;
	}
};
/*
Test cases:

"+"
"++"
"+."
"+.0"
"0e"
"4e+"
""
" "
"."
".1"
"..1"
"1."
".e1"
".0e1"
"e"
" 0001.00"
" 0001.-01"
" 000.e10"
" 0001.12e-2"
" 0001.12e-2.0"
" 1.e--200"
" 1.e+200"
" 1.e+200."
" 200."
"0"
" 0.1 "
"abc"
"1 a"
"2e10"
" -90e3  "
" 1e"
"e3"
" 6e-1"
" 99e2.5 "
"53.5e93"
" --6 "
"-+3"
"95a54e53"
" -000e3 "

Outputs:

false
false
false
true
false
false
false
false
false
true
false
true
false
true
false
true
false
true
true
false
false
true
false
true
true
true
false
false
true
true
false
false
true
false
true
false
false
false
true
*/
