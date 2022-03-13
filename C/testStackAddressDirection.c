
/*
 To detect the stack address extend dirction: low->high or high -> low
    the call_first() will be call first, then call_second(), that means a will be added to stack first, then a.
    the result:
        First : a's address = 00000090d81ffaec.
        Second: b'a address = 00000090d81ffaac.
 Conclusion:
    a'address > b'address, that means the stack address extend from high to low.
*/

#include <stdio.h>

void call_second();

void call_first()
{
    int  a = 1;
    printf("First : a's address = %p.\n", &a);

    call_second();
}

void call_second()
{
    int b = 2;
    printf("Second: b'a address = %p.\n", &b);
}


int main()
{
    call_first();

    return 0;
}

