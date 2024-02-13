#include "bfnumlib.hpp"

namespace BFNumLib
{
    void bfnum::push_left(int num)
    {
        bool is_null = true;
        for (int i = 0; i < len; i++)
        {
            if (number[i] != 0)
            {
                is_null = false;
                break;
            }
        }
        if (is_null)
            return;

        bool is_num = false;
        int prev_len = len;
        for (int i = 0; i < num; i++)
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
                    is_num = true;
                }
            }
            else
            {
                number[i] = 0;
            }
        }
    }

    void bfnum::push_right(int num)
    {
        bool is_null = true;
        for (int i = 0; i < len; i++)
        {
            if (number[i] != 0)
            {
                is_null = false;
                break;
            }
        }
        if (is_null)
            return;

        bool is_num = false;
        int prev_len = len;
        for (int i = 0; i < num; i++)
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
                    is_num = true;
                }
            }
            else
            {
                number[i] = 0;
            }
        }
    }

    void bfnum::levelout(bfnum &other)
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

    bfnum::bfnum()
    {
        len = 1;
        man_len = 0;
        number.push_back(0);
        mantissa.push_back(0);
        sign = 1;
    }

    bfnum::bfnum(int num)
    {
        *this = bfnum((long long)num);
    }

    bfnum::bfnum(long num)
    {
        *this = bfnum((long long)num);
    }

    bfnum::bfnum(long long num)
    {
        len = 0;
        man_len = 0;
        if (num < 0)
        {
            sign = false;
            num = -num;
        }
        else
            sign = true;
        while (num > 0)
        {
            number.push_front((int)(num % 10));
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

    bfnum::bfnum(double num, int man_len)
    {
        len = 0;
        this->man_len = 0;
        if (num < 0)
        {
            sign = false;
            num = -num;
        }
        else
            sign = true;
        long long dec = (int)num;
        while (dec > 0)
        {
            number.push_front((int)(dec % 10));
            mantissa.push_front(0);
            dec /= 10;
            len++;
        }
        num *= 10;
        while (this->man_len < man_len)
        {
            dec = (long long)num % 10;
            number.push_back((int)dec);
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

    bfnum::bfnum(double num)
    {
        *this = bfnum(num, 10);
    }

    std::string bfnum::get_string()
    {
        std::string str;

        bool is_num = false;
        bool is_frac = false;
        if (this->sign == 0)
            str.push_back('-');
        for (int i = 0; i < this->len; i++)
        {
            if (is_num == 0 && this->mantissa[i] == 1)
            {
                str.push_back('0');
                is_num = true;
            }
            if (is_frac == 0 && this->mantissa[i] == 1)
            {
                str.push_back('.');
                is_frac = true;
            }
            if (this->number[i] != 0)
                is_num = true;
            if (is_num == 1 || this->number[i] != 0)
            {
                str.push_back((char)(this->number[i] + '0'));
            }
        }
        if (is_num == 0)
            str.push_back('0');

        return (str);
    }

    bfnum &bfnum::operator=(const bfnum &other)
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

    bfnum &bfnum::operator=(long long other)
    {
        bfnum nthis(other);
        *this = nthis;

        return *this;
    }

    bfnum &bfnum::operator=(double other)
    {
        bfnum nthis(other);
        *this = nthis;

        return *this;
    }

    bool bfnum::operator==(const bfnum &other) const
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nthis.sign != nother.sign)
            return false;

        for (int i = 0; i < nthis.len; i++)
        {
            if (nthis.number[i] != nother.number[i])
                return false;
        }
        return true;
    }

    bool bfnum::operator!=(const bfnum &other) const
    {
        return !(*this == other);
    }

    bool bfnum::operator<(const bfnum &other) const
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nthis.sign == 1 && nother.sign == 0)
            return false;
        if (nthis.sign == 0 && nother.sign == 1)
            return true;
        if (nthis.sign == 0 && nother.sign == 0)
        {
            nthis.sign = true;
            nother.sign = true;
            return nthis > nother;
        }
        for (int i = 0; i < nthis.len; i++)
        {
            if (nthis.number[i] < nother.number[i])
                return true;
            if (nthis.number[i] > nother.number[i])
                return false;
        }
        return false;
    }

    bool bfnum::operator>(const bfnum &other) const
    {
        return (*this != other) && !(*this < other);
    }

    bfnum bfnum::operator+(const bfnum &other) const
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
                nother.sign = true;

                return nthis - nother;
            }
            else
            {
                nthis.sign = true;

                return nother - nthis;
            }
        }
    }

    bfnum bfnum::operator-(const bfnum &other) const
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (nthis.sign == nother.sign)
        {
            bfnum null;
            null.sign = false;
            if (nthis < nother)
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
                    new_num.sign = true;
                }

                return new_num;
            }
            else
            {
                bfnum new_num = nother - nthis;
                if (new_num != 0)
                    new_num.sign_change();

                return new_num;
            }
        }
        else
        {
            if (nthis.sign == 1)
            {
                nother.sign = true;

                return nthis + nother;
            }
            else
            {
                nthis.sign = true;

                return nthis + nother;
            }
        }
    }

    bfnum bfnum::operator*(const bfnum &other) const
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
            new_num.push_right(nother.man_len);
            new_num.man_len += nother.man_len;

            if (nthis.sign == nother.sign || new_num == null)
            {
                new_num.sign = true;
            }
            else
                new_num.sign = false;

            return new_num;
        }
    }

    bfnum bfnum::operator/(const bfnum &other) const
    {
        return div(other, 10);
    }

    bfnum bfnum::div(const bfnum &other, int man) const
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        nthis.sign = true;
        nother.sign = true;

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
            bfnum new_num(0.0, man);
            bfnum mnull(0.0);
            mnull.sign = false;
            int digit = 0;
            int edge = 1;
            int tcount = 0;
            int ocount = 0;
            for (int i = 0; i < nthis.len; i++)
            {
                if (nthis.number[i] == 0)
                {
                    tcount++;
                }
                else
                    break;
            }
            for (int i = 0; i < nother.len; i++)
            {
                if (nother.number[i] == 0)
                {
                    ocount++;
                }
                else
                    break;
            }
            if (ocount - tcount > 0)
            {
                nother.push_left(ocount - tcount);
                edge += (ocount - tcount);
                while (nother > nthis)
                {
                    nother.man_len++;
                    edge--;
                    nother.mantissa[nother.len - nother.man_len] = 1;
                }
            }

            for (int i = 0; i < new_num.len; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    nthis = nthis - nother;
                    if (nthis < mnull)
                    {
                        nthis = nthis + nother;
                        nthis.sign = true;
                        new_num.number[i] = j;
                        if (digit < edge)
                        {
                            new_num.push_left(1);
                        }
                        nother.man_len++;
                        digit++;
                        break;
                    }
                    else if (nthis == mnull)
                    {
                        j++;
                        new_num.number[i] = j;
                        if (digit < edge)
                        {
                            new_num.push_left(1);
                        }
                        goto stop;
                    }
                }
            }
        stop:
            if (this->sign == other.sign || new_num == 0)
            {
                new_num.sign = true;
            }
            else
                new_num.sign = false;

            return new_num;
        }
    }

    void bfnum::sign_change()
    {
        sign = !sign;
    }

    void bfnum::evalf(int digits)
    {
        while (man_len > digits)
        {
            man_len--;
            len--;
            number.pop_back();
            mantissa.pop_back();
        }
    }

    bfnum bfnum::fact() const
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

    bfnum bfnum::pow(long long pow) const
    {
        bfnum nthis = *this;
        bfnum new_num = 1;

        while (pow != 0)
        {
            if (pow % 2 != 0)
            {
                new_num = new_num * nthis;
            }
            nthis = nthis * nthis;
            pow /= 2;
        }

        return new_num;
    }

    bfnum bfnum::abs() const
    {
        bfnum nthis = *this;

        nthis.sign = true;

        return nthis;
    }
}