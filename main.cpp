#include <iostream>

#include "bfnumlib.h"

int main(void)
{
    bfnum a;
    bfnum b;
    bfnum c;

    b = 18483745.4659;

    a = -1534.85;

    c = b * a;
    
    std::cout << c.get_string() << std::endl;

    return 0;
}