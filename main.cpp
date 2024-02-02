#include <iostream>

#include "bfnumlib.h"

int main(void)
{
    bfnum a(10, 7);
    bfnum b(20, 5);
    bfnum c;

    b = 18.46e1;

    a = -151.85;

    c = b / a;
    
    std::cout << c.get_string() << std::endl;

    return 0;
}