#include <stdio.h>
#include "bitwise.h"

void testBitwiseMacro()
{
    int arr[]={1,10,20,100,1011,10111,10000001};
    int len=sizeof(arr)/sizeof(arr[0]);
    int i;
    for(i = 0; i < len; ++i)
	set(arr[i]);
    for(i = 0; i < len; ++i)
    {
	printf("Expect 1:%d\n",test(arr[i]));
	printf("Expect 0:%d\n",test(arr[i]+i+1));
	clr(arr[i]);
    }
    for(i = 0; i < len; ++i)
	printf("Expect 0:%d\n",test(arr[i]));
}
