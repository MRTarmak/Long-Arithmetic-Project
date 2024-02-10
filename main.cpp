#include <iostream>

#include "bfnumlib.hpp"

auto sqrt(bfnum &num)
{
    bfnum lh(0);
    bfnum rh = num + bfnum(1);
    bfnum eps(0.1, 1);
    eps = eps.pow(10);
    while (rh - lh > eps)
    {
        lh.evalf(10);
        rh.evalf(10);
        auto mid = lh + ((rh - lh) / 2);

        if (mid * mid < num)
            lh = mid;
        else
            rh = mid;
    }

    return lh + (rh - lh) / 2;
}

auto root(const bfnum &n, const bfnum &one)
{
    bfnum precision = 10000000000000000;
    auto n_float = (n * precision).div(one, 0);
    n_float = n_float / precision;
    auto tmp = (precision * sqrt(n_float) * one);
    tmp.evalf(0);
    auto x = tmp.div(precision, 0);
    auto n_one = n * one;
    while (true)
    {
        auto x_old = x;
        x = n_one.div(x, 0);
        x = x + x_old;
        x = x.div(2, 0);
        if (x == x_old)
            break;
    }

    return x;
}

bfnum pi_calculation(long long n)
{
    bfnum mnull(0.0);
    mnull.sign_change();
    bfnum one(10);
    one = one.pow(n);
    bfnum k(1);
    bfnum a_k = one;
    bfnum a_sum = one;
    bfnum b_sum(0);
    bfnum c(640320);
    bfnum c3_over_24 = c.pow(3).div(24, 0);
    bfnum denum;
    while (true)
    {
        a_k = a_k * (bfnum(6) * k - 5) * (bfnum(2) * k - 1) * (bfnum(6) * k - 1);
        a_k.sign_change();
        denum = k * k * k * c3_over_24;
        a_k = a_k.div(denum, 0);
        a_sum = a_sum + a_k;
        b_sum = b_sum + k * a_k;
        k = k + 1;
        if (a_k == 0 || a_k == mnull)
            break;
    }
    bfnum total = bfnum(13591409) * a_sum + bfnum(545140134) * b_sum;
    bfnum rt_param = bfnum(10005) * one;
    bfnum pi = (bfnum(426880) * root(rt_param, one) * one).div(total, 0);

    return pi;
}

int main(void)
{
    bfnum pi;
    // bfnum a = 2.432;
    // bfnum b = 75435.423;
    // bfnum c = a / b;
    pi = pi_calculation(2);
    std::cout << pi.get_string() << std::endl;

    return 0;
}