#include <limits.h>

#define N 1e20 //the max int the bitvec can hold
#define INT_CAPACITY 32//sizeof(int)*CHAR_BIT, each int type can hold up to 32 values since it has 32 bits
#define SHIFT 5       //right shift 5 means dividing by 32
#define MASK 0x1f     //mask for getting the reminder of dividing 32, which is the relative index inside a int (0 -- 31)
int bitvec[(int)(N / INT_CAPACITY + 1)]; // if the max value is 65, 65/32=2, plus 1 will actually add another 32 bits, which is sufficient to cover all reminder by N/INT_CAPACITY
#define set(i) (bitvec[(i)>>SHIFT]|=1<<((i)&MASK)) //first dividing the number i by 32 to find the base index, then the offset is defined as the reminder part of i/32, we then move 1 over to the offset based upon the base index, a OR is applied to assign the bit
#define clr(i) (bitvec[(i)>>SHIFT]&=~(1<<((i)&MASK))) // move 1 to the offset, then flip all bits, which will leave the bit we look for to zero. When we do the bitwise and, all other bits will remain unchanged, only the bit with 0 will be cleared
#define test(i) (0!=(bitvec[(i)>>SHIFT]&(1<<((i)&MASK))))//move 1 to the offset and and with the value of the integer. If the specific bit is set, the result will be non-zero

void testSwapbitsOddEven();
