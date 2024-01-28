#include <iostream>

#include "bfnumlib.h"

int main(void)
{
    bfn a(10, 7);
    bfn b(20, 5);
    bfn c;

    b = 1.5;

    a = 150.85;

    c = a + b;
    
    c.print_num();

    return 0;
}