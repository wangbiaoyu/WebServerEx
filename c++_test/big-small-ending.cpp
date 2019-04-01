#include <stdio.h>
 

union
{
    short value;
    char array[sizeof(short)];
}test;

int main()
{
    test.value = 0X0102;
    printf("low bit is %d,high bit is %d\n-",test.array[0],test.array[1]);
    return 0;
}
