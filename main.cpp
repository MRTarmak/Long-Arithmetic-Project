#include <iostream>
#include <ctime>
#include <bfnumlib.hpp>

using namespace BFNumLib;

auto mysqrt(const bfnum &num, long long prec)
{
    bfnum lh(0);
    bfnum rh = num + bfnum(1);
    bfnum eps(0.1, 1);
    eps = eps.pow(prec);
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

auto root(const bfnum &n, const bfnum &one)
{
    bfnum prec = 10000000000000000;
    auto n_prec = (n * prec).div(one, 0);
    n_prec = n_prec / prec;
    auto tmp = prec * mysqrt(n_prec, 1);
    tmp.evalf(0);
    tmp = tmp * one;
    auto x = tmp.div(prec, 0);
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
    bfnum pi = (bfnum(426880) * root(rt_param, one) * one).div(total, 0);

    pi.set_man_len(prec);

    return pi;
}

int main()
{
    bfnum pi;
    int prec;
    std::cout << "Set precision:";
    std::cin >> prec;
    unsigned int start_time = clock();
    pi = pi_calculation(prec + 10);
    std::cout << "Pi with " << prec << " signs after the decimal point: " << pi.get_string(prec) << std::endl;
    unsigned int end_time = clock();
    std::cout << "Execution time: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}