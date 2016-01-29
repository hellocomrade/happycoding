#include <iostream>

using namespace std;

unsigned int swapbitsOddEven(unsigned int A)
{
	unsigned int evenbits = A & 0xaaaaaaaa; //10101010101010101010101010101010
	unsigned int oddbits = A & 0x55555555; // 01010101010101010101010101010101
	return (evenbits >> 1) | (oddbits << 1);
}
void testSwapbitsOddEven()
{
	cout << "Expect 43: " << swapbitsOddEven(23) << endl;
	cout << "Expect 23: " << swapbitsOddEven(43) << endl;
	cout << "Expect 2: " << swapbitsOddEven(1) << endl;
	cout << "Expect 66: " << swapbitsOddEven(129) << endl;
}