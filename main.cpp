#include <iostream>

#include "bfnumlib.h"

int main(void)
{
    bfn a(10, 7);
    bfn b(20, 5);
    bfn c;

    b = 500;

    a = -151.85;

    c = b / a;
    
    c.print_num();

    return 0;
}