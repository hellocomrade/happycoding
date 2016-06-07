#include <string>
#include <sstream>
#include <cmath>

using namespace std;

//http://www.lintcode.com/en/problem/binary-representation/
/*
Binary Representation

Given a (decimal - e.g. 3.72) number that is passed in as a string, return the binary representation that is passed in as a string. If the fractional part of the number can not be represented accurately in binary with at most 32 characters, return ERROR.

Example
For n = "3.72", return "ERROR".

For n = "3.5", return "11.1".

Observation:
You can divide the problem to 3 sub problems:
1. String to decimal;
2. Decimal to binary;
3. Fractional to binary;

The third one is kind of rare. Instead of keeping dividing number by 2 for integer to binary, we keep multiplying
2 on fraction. If it's greater than 1, we put 1 on this bit and then substract 1 from the fraction.
If it's less than 1, we put 0 on this position and move to next iteration.
*/
class SolutionBinaryRepresentation {
private:
	long long parseLL(string num, int start, int end)
	{
		long long integer = 0, tens = 1;
		for (int i = end; i >= start; --i)
		{
			integer += (num[i] - 48) * tens;
			tens *= 10;
		}
		return integer;
	}
	void dec2bin(ostringstream &os, int integer)
	{
		unsigned int mask = 1 << (sizeof(int) * 8 - 1);
		bool skipLeading0 = false;
		while (mask)
		{
			if (!skipLeading0)skipLeading0 = (0 != (integer & mask));
			if (skipLeading0)
				os << (0 != (integer & mask));
			mask >>= 1;
		}
		if (!skipLeading0)
			os << '0';
	}
public:
	/**
	*@param n: Given a decimal number that is passed in as a string
	*@return: A string
	*/
	string binaryRepresentation(string n) {
		// wirte your code here
		int len = n.length();
		if (len < 1)return "ERROR";
		ostringstream os;
		int start = (n[0] == '+' || n[0] == '-') ? 1 : 0;
		int pnt = start;
		for (; pnt < len; ++pnt)
			if (n[pnt] == '.')break;
		if (n[0] != '-')
			this->dec2bin(os, (int)this->parseLL(n, start, pnt - 1));
		long long LL = this->parseLL(n, pnt + 1, len - 1);
		//cout << LL << endl;
		if (LL > 0)
		{
			os << '.';
			double fractional = LL * 1.0 / pow(10, len - pnt - 1);
			//cout <<fractional<<endl;
			int cnt = 32;
			double tmp = 0;
			while (cnt-- > 0)
			{
				tmp = fractional * 2;
				if (tmp >= 1)
				{
					os << '1';
					fractional = tmp - 1;
					if (fractional == 0)break;
				}
				else
				{
					os << '0';
					fractional = tmp;
				}
			}
			if (cnt < 0 && fractional != 0)return "ERROR";
		}
		return os.str();
	}
};
