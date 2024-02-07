#include <iostream>
#include <deque>

class bfnum
{
private:
    int len;
    int man_len;
    std::deque<int> number;
    std::deque<int> mantissa;
    bool sign;

    // void push_left(int); // вынести реализацию в .cpp
    void push_left(int num)
    {
        bool is_null = 1;
        for (int i = 0; i < len; i++)
        {
            if (number[i] != 0)
            {
                is_null = 0;
                break;
            }
        }
        if (is_null)
            return;

        bool is_num = 0;
        int prev_len = len;
        for (int i = 0; i < prev_len; i++)
        {
            number.push_front(0);
            mantissa.push_front(0);
            len++;
        }
        for (int i = 0; i < len; i++)
        {
            if (i + num < len)
            {
                number[i] = number[i + num];
                if (number[i] == 0 && is_num == 0 && i < prev_len)
                {
                    number.pop_front();
                    mantissa.pop_front();
                    len--;
                    i--;
                }
                else
                {
                    is_num = 1;
                }
            }
            else
            {
                number[i] = 0;
            }
        }
    }

    void push_right(int num)
    {
        bool is_null = 1;
        for (int i = 0; i < len; i++)
        {
            if (number[i] != 0)
            {
                is_null = 0;
                break;
            }
        }
        if (is_null)
            return;

        bool is_num = 0;
        int prev_len = len;
        for (int i = 0; i < prev_len; i++)
        {
            number.push_back(0);
            mantissa.push_back(1);
            len++;
        }
        for (int i = len - 1; i >= 0; i--)
        {
            if (i - num >= 0)
            {
                number[i] = number[i - num];
                if (number[i] == 0 && is_num == 0 && i >= prev_len)
                {
                    number.pop_back();
                    mantissa.pop_back();
                    len--;
                }
                else
                {
                    is_num = 1;
                }
            }
            else
            {
                number[i] = 0;
            }
        }
    }

    void levelout(bfnum &other)
    {
        for (int i = 0; i < len; i++) // Удаление незначащих нулей в конце
        {
            if (number[(len - 1) - i] == 0 && mantissa[(len - 1) - i] == 1)
            {
                man_len--;
                len--;
                number.pop_back();
                mantissa.pop_back();
                i--;
            }
            else
                break;
        }
        for (int i = 0; i < len; i++) // Удаление незначащих нулей в начале
        {
            if (number[i] == 0 && i != len - man_len - 1)
            {
                len--;
                number.pop_front();
                mantissa.pop_front();
                i--;
            }
            else
                break;
        }

        for (int i = 0; i < other.len; i++) // Удаление незначащих нулей в конце
        {
            if (other.number[(other.len - 1) - i] == 0 && other.mantissa[(other.len - 1) - i] == 1)
            {
                other.man_len--;
                other.len--;
                other.number.pop_back();
                other.mantissa.pop_back();
                i--;
            }
            else
                break;
        }
        for (int i = 0; i < other.len; i++) // Удаление незначащих нулей в начале
        {
            if (other.number[i] == 0 && i != other.len - other.man_len - 1)
            {
                other.len--;
                other.number.pop_front();
                other.mantissa.pop_front();
                i--;
            }
            else
                break;
        }

        int old_len_t = len;
        int old_man_len_t = man_len;
        int old_len_o = other.len;
        int old_man_len_o = other.man_len;

        int new_man_len = man_len > other.man_len ? man_len : other.man_len;
        int new_len = (len - man_len) > (other.len - other.man_len) ? (len - man_len) : (other.len - other.man_len);
        new_len += new_man_len;

        while (man_len != new_man_len) // Выравнивание числа
        {
            number.push_back(0);
            mantissa.push_back(1);
            man_len++;
            len++;
        }
        while (len != new_len)
        {
            number.push_front(0);
            mantissa.push_front(0);
            len++;
        }

        while (other.man_len != new_man_len) // Выравнивание числа
        {
            other.number.push_back(0);
            other.mantissa.push_back(1);
            other.man_len++;
            other.len++;
        }
        while (other.len != new_len)
        {
            other.number.push_front(0);
            other.mantissa.push_front(0);
            other.len++;
        }
    }

public:
    bfnum()
    {
        len = 1;
        man_len = 0;
        number.push_back(0);
        mantissa.push_back(0);
        sign = 1;
    }

    bfnum(int num)
    {
        *this = bfnum((long long)num);
    }

    bfnum(long num)
    {
        *this = bfnum((long long)num);
    }

    bfnum(long long num)
    {
        len = 0;
        man_len = 0;
        if (num < 0)
        {
            sign = 0;
            num = -num;
        }
        else
            sign = 1;
        while (num > 0)
        {
            number.push_front(num % 10);
            mantissa.push_front(0);
            len++;
            num /= 10;
        }
        if (len == 0)
        {
            number.push_front(0);
            mantissa.push_front(0);
            len++;
        }
    }

    bfnum(double num, int man_len = 10)
    {
        len = 0;
        this->man_len = 0;
        if (num < 0)
        {
            sign = 0;
            num = -num;
        }
        else
            sign = 1;
        long long dec = num;
        while (dec > 0)
        {
            number.push_front(dec % 10);
            mantissa.push_front(0);
            dec /= 10;
            len++;
        }
        num *= 10;
        while (this->man_len < man_len)
        {
            dec = (long long)num % 10;
            number.push_back(dec);
            mantissa.push_back(1);
            num *= 10;
            len++;
            this->man_len++;
        }
        if (len == 0)
        {
            number.push_front(0);
            mantissa.push_front(0);
            len++;
        }
    }

    std::string get_string()
    {
        std::string str;

        bool is_num = 0;
        bool is_frac = 0;
        if (this->sign == 0)
            str.push_back('-');
        for (int i = 0; i < this->len; i++)
        {
            if (is_num == 0 && this->mantissa[i] == 1)
            {
                str.push_back('0');
                is_num = 1;
            }
            if (is_frac == 0 && this->mantissa[i] == 1)
            {
                str.push_back('.');
                is_frac = 1;
            }
            if (this->number[i] != 0)
                is_num = 1;
            if (is_num == 1 || this->number[i] != 0)
            {
                str.push_back(this->number[i] + '0');
            }
        }
        if (is_num == 0)
            str.push_back(0);

        return (str);
    }

    bfnum &operator=(const bfnum &other)
    {
        this->len = other.len;
        this->man_len = other.man_len;
        this->sign = other.sign;

        this->number.clear();
        this->mantissa.clear();

        for (int i = 0; i < this->len; i++)
        {
            this->number.push_back(other.number[i]);
            this->mantissa.push_back(other.mantissa[i]);
        }

        return *this;
    }

    bfnum &operator=(long long other)
    {
        bfnum nthis(other);
        *this = nthis;

        return *this;
    }

    bfnum &operator=(double other)
    {
        bfnum nthis(other);
        *this = nthis;

        return *this;
    }

    bool operator==(const bfnum &other)
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nthis.sign != nother.sign)
            return 0;

        for (int i = 0; i < len; i++)
        {
            if (nthis.number[i] != nother.number[i])
                return 0;
        }
        return 1;
    }

    // попробовать реализовать через <=>
    bool operator!=(const bfnum &other)
    {
        return !(*this == other);
    }

    bool operator<(const bfnum &other)
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nthis.sign == 1 && nother.sign == 0)
            return 0;
        else if (nthis.sign == 0 && nother.sign == 1)
            return 1;
        for (int i = 0; i < nthis.len; i++)
        {
            if (nthis.number[i] < nother.number[i])
                return 1;
            if (nthis.number[i] > nother.number[i])
                return 0;
        }
        return 0;
    }

    bool operator>(const bfnum &other)
    {
        return (*this != other) && !(*this < other);
    }

    bfnum operator+(const bfnum &other)
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nthis.sign == nother.sign)
        {
            bfnum new_num = nthis;

            for (int i = nthis.len - 1; i > 0; i--)
            {
                new_num.number[i] += nother.number[i];
                new_num.number[i - 1] += new_num.number[i] / 10;
                new_num.number[i] = new_num.number[i] % 10;
            }
            new_num.number[0] += nother.number[0];
            if (new_num.number[0] > 9)
            {
                new_num.number.push_front(new_num.number[0] / 10);
                new_num.number[1] = new_num.number[1] % 10;
                new_num.len++;
            }

            return new_num;
        }
        else
        {
            if (nthis.sign == 1)
            {
                nother.sign = 1;

                return nthis - nother;
            }
            else
            {
                nthis.sign = 1;

                return nother - nthis;
            }
        }
    }

    bfnum operator-(const bfnum &other)
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nthis.sign == nother.sign)
        {
            bfnum null;
            null.sign = 0;
            if (nthis > nother)
            {
                bfnum new_num = nthis;

                for (int i = nthis.len - 1; i >= 0; i--)
                {
                    new_num.number[i] -= nother.number[i];
                    if (new_num.number[i] < 0 && i != 0)
                    {
                        new_num.number[i - 1] -= 1;
                        new_num.number[i] += 10;
                    }
                    else if (new_num.number[i] < 0 && i == 0)
                    {
                        new_num.number[0] = -new_num.number[0];
                        new_num.sign = !new_num.sign;
                    }
                }

                if (new_num == null)
                {
                    new_num.sign = 1;
                }

                return new_num;
            }
            else
            {
                bfnum new_num = nother;

                for (int i = nother.len - 1; i >= 0; i--)
                {
                    new_num.number[i] -= nthis.number[i];
                    if (new_num.number[i] < 0 && i != 0)
                    {
                        new_num.number[i - 1] -= 1;
                        new_num.number[i] += 10;
                    }
                    else if (new_num.number[i] < 0 && i == 0)
                    {
                        new_num.number[0] = -new_num.number[0];
                        new_num.sign = !new_num.sign;
                    }
                }

                if (new_num == null)
                {
                    new_num.sign = 1;
                }
                else
                    new_num.sign = 0;

                return new_num;
            }
        }
        else
        {
            if (nthis.sign == 1)
            {
                nother.sign = 1;

                return nthis + nother;
            }
            else
            {
                nthis.sign = 1;

                return nthis + nother;
            }
        }
    }

    bfnum operator*(const bfnum &other)
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        bfnum null;
        if (nthis == null || nother == null)
            return null;
        else
        {
            bfnum new_num;
            new_num.sign = nthis.sign;
            bfnum plus;
            plus.sign = nthis.sign;
            for (int i = nother.len - 1; i >= 0; i--)
            {
                if (nother.number[i] != 0)
                {
                    for (int j = 0; j < nother.number[i]; j++)
                    {
                        plus = plus + nthis;
                    }
                    if (nthis.len - nthis.man_len - 1 - i < 0)
                    {
                        plus.push_right(i - (nthis.len - nthis.man_len - 1));
                    }
                    else
                    {
                        plus.push_left(nthis.len - nthis.man_len - 1 - i);
                    }
                    new_num = new_num + plus;
                    plus = 0.0;
                }
            }
            if (nthis.sign == nother.sign || new_num == null)
            {
                new_num.sign = 1;
            }
            else
                new_num.sign = 0;

            return new_num;
        }
    }

    bfnum operator/(const bfnum &other)
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nother == 0)
        {
            std::cout << "ERROR: dividing by zero" << std::endl;
            exit(EXIT_FAILURE);
        }
        else if (nthis == 0)
        {
            return 0;
        }
        else
        {
            bfnum new_num(0.0);
            nthis.sign = 1;
            nother.sign = 1;
            int digit = 0;
            int edge = nthis.len - nthis.man_len - 1;

            for (int i = 0; i < new_num.len; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    nthis = nthis - nother;
                    if (nthis < 0)
                    {
                        nthis = nthis + nother;
                        nthis.sign = 1;
                        new_num.number[i] = j;
                        if (digit < edge)
                        {
                            new_num.push_left(1);
                            i--;
                        }
                        nthis.push_left(1);
                        digit++;
                        break;
                    }
                    else if (nthis == 0)
                    {
                        j++;
                        new_num.number[i] = j;
                        if (digit < edge)
                        {
                            new_num.push_left(1);
                            i--;
                        }
                        goto stop;
                    }
                    else if (j == 9)
                    {
                        nthis.push_right(1);
                        i--;
                    }
                }
            }
        stop:
            if (this->sign == other.sign || new_num == 0)
            {
                new_num.sign = 1;
            }
            else
                new_num.sign = 0;

            return new_num;
        }
    }

    bfnum fact()
    {
        bfnum nthis = *this;
        bfnum res = 1;
        while (nthis != 0.0)
        {
            res = res * nthis;
            nthis = nthis - 1;
        }

        return res;
    }

    bfnum pow(long long pow)
    {
        bfnum new_num = *this;

        if (pow == 0)
            return 1;

        for (long long i = 1; i < pow; i++)
        {
            new_num = new_num * new_num;
        }

        return new_num;
    }

    bfnum abs()
    {
        bfnum nthis = *this;

        nthis.sign = 1;

        return nthis;
    }

    bfnum sqrt(long long precision)
    {
        bfnum x = *this;

        if (x < 0)
            exit(1);
        if (x == 0)
            return 0;

        bfnum xhi = x;
        bfnum xlo = 0;
        bfnum guess = x / 2;

        bfnum eps = 0.1;
        eps = eps.pow(precision);

        while ((guess * guess - x).abs() > eps)
        {
            if (guess * guess > x)
            {
                xhi = guess;
            }
            else
            {
                xlo = guess;
            }

            guess = (xhi + xlo) / 2;
        }

        return guess;
    }
};