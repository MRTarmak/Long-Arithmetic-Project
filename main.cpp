#include <iostream>

#include "bfnumlib.h"

int main(void)
{
    bfn a(10, 10);
    bfn b(20, 5);

    b = 1.5;

    a = b;

    a.print_num();

    return 0;
}