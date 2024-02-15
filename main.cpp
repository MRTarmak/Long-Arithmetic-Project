#include <iostream>
#include <bfnumlib.hpp>

using namespace BFNumLib;

auto msqrt(const bfnum &num, long long precision)
{
    bfnum lh(0);
    bfnum rh = num + bfnum(1);
    bfnum eps(0.1, 1);
    eps = eps.pow(70);
    while (rh - lh > eps)
    {
        auto mid = lh + ((rh - lh) / 2);

        if (mid * mid < num)
            lh = mid;
        else
            rh = mid;
    }

    return lh + (rh - lh) / 2;
}

auto root(const bfnum &n, const bfnum &one, long long prec)
{
    bfnum precision = 10000000000000000;
    auto n_float = (n * precision).div(one, 0);
    n_float = n_float / precision;
    auto tmp = precision * msqrt(n_float, prec);
    tmp.evalf(0);
    tmp = tmp * one;
    auto x = tmp.div(precision, 0);
    auto n_one = n * one;
    while (true)
    {
        auto x_old = x;
        x = x + n_one.div(x, 0);
        x = x.div(2, 0);
        if (x == x_old)
            break;
    }

    return x;
}

bfnum pi_calculation(int prec)
{
    bfnum mnull(0);
    mnull.sign_change();
    bfnum one(10);
    one = one.pow(prec);
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
        if (a_k != 0 && a_k != mnull)
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
    bfnum pi = (bfnum(426880) * root(rt_param, one, prec) * one).div(total, 0);

    pi.set_man_len(prec);

    return pi;
}

int main()
{
    bfnum pi;
    int prec;
    std::cout << "Set precision:";
    std::cin >> prec;
    pi = pi_calculation(prec);
    std::cout << "Pi with " << prec << " signs after the decimal point: " << pi.get_string() << std::endl;

    return 0;
}