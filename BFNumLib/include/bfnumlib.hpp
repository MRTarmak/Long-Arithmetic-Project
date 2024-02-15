#pragma once

#include <iostream>
#include <deque>

namespace BFNumLib
{
    class bfnum
    {
    private:
        int len;
        int man_len;
        std::deque<int> number;
        std::deque<int> mantissa;
        bool sign;

        void push_left(int);
        void push_right(int);
        void levelout(bfnum &);

    public:
        bfnum();
        bfnum(int);
        bfnum(long);
        bfnum(long long);
        bfnum(double, int);
        bfnum(double);

        std::string get_string(int);
        std::string get_string();

        bfnum &operator=(const bfnum &);
        bfnum &operator=(long long);
        bfnum &operator=(double);

        bool operator==(const bfnum &) const;
        bool operator!=(const bfnum &) const;
        bool operator<(const bfnum &) const;
        bool operator>(const bfnum &) const;

        bfnum operator+(const bfnum &) const;
        bfnum operator-(const bfnum &) const;
        bfnum operator*(const bfnum &) const;
        bfnum operator/(const bfnum &) const;

        bfnum div(const bfnum &, int) const;
        bfnum pow(long long) const;

        void sign_change();
        void evalf(int);
        void set_man_len(int);
    };
}