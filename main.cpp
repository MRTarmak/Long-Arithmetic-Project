#include <iostream>

#include "bfnumlib.h"

bfnum pi_calculation(long long n)
{
    bfnum pi(0.0, 100);

    bfnum num;
    bfnum denum;
    bfnum one = 1;

    for (long long k = 0; k <= n; k++)
    {
        num = 545140134 * k;
        num = num + 13591409;
        num = num * bfnum(6 * k).fact();
        denum = bfnum(3 * k).fact();
        denum = denum * bfnum(k).fact().pow(3);
        denum = denum * bfnum(640320).pow(3 * k);

        if (k % 2 == 0)
        {
            pi = pi + num / denum;
        }
        else
            pi = pi - num / denum;
    }
    pi = pi / (bfnum(426880) * bfnum(10005).sqrt(100));
    pi = one / pi;

    return pi;
}

int main(void)
{
    bfnum a = (long long)10;
    a = pi_calculation(1);
    std::cout << a.get_string() << std::endl;

    return 0;
}