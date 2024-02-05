#include <iostream>
#include <vector>

class bfnum
{
private:
    int len = 0;
    int man_len;
    std::vector<int> number;
    std::vector<int> mantissa;
    bool sign;

    // void push_left(int); // вынести реализацию в .cpp
    void push_left(int num)
    {
        for (int i = 0; i < len; i++)
        {
            if (i + num < len)
            {
                number[i] = number[i + num];
            }
            else
            {
                number[i] = 0;
            }
        }
    }

    void push_right(int num)
    {
        for (int i = len - 1; i >= 0; i--)
        {
            if (i - num >= 0)
            {
                number[i] = number[i - num];
            }
            else
            {
                number[i] = 0;
            }
        }
    }

    void levelout(bfnum &other)
    {
        if (len != other.len || man_len != other.man_len)
        {
            int old_len_t = len;
            int old_man_len_t = man_len;
            int old_len_o = other.len;
            int old_man_len_o = other.man_len;

            int new_man_len = man_len > other.man_len ? man_len : other.man_len;
            int new_len = len > other.len ? len : other.len;

            len = new_len;
            man_len = new_man_len;

            while (number.size() != len)
            {
                number.push_back(0);
                mantissa.push_back(0);
            }

            std::cout << get_string() << std::endl; //
            std::cout << other.get_string() << std::endl; //

            for (int i = len - man_len; i < len; i++)
            {
                if (len - (i + 1) < man_len)
                    mantissa[i] = 1;
                else
                    mantissa[i] = 0;
            }

            other.len = new_len;
            other.man_len = new_man_len;

            while (other.number.size() != other.len)
            {
                other.number.push_back(0);
                other.mantissa.push_back(0);
            }

            for (int i = other.len - other.man_len; i < other.len; i++)
            {
                if (other.len - (i + 1) < other.man_len)
                    other.mantissa[i] = 1;
                else
                    other.mantissa[i] = 0;
            }

            if (new_len - old_len_t - (new_man_len - old_man_len_t) > 0)
                push_right(new_len - old_len_t - (new_man_len - old_man_len_t));
            else
                push_left(-(new_len - old_len_t - (new_man_len - old_man_len_t)));

            for (int i = 0; i < this->len; i++)
            {
                this->mantissa[i] = (len - (i + 1) < man_len) ? 1 : 0;
                if (i < new_len - old_len_t)
                    this->number[i] = 0;
            }

            if (new_len - old_len_o - (new_man_len - old_man_len_o) > 0)
                other.push_right(new_len - old_len_o - (new_man_len - old_man_len_o));
            else
                other.push_left(-(new_len - old_len_o - (new_man_len - old_man_len_o)));

            for (int i = 0; i < other.len; i++)
            {
                other.mantissa[i] = (len - (i + 1) < man_len) ? 1 : 0;
                if (i < new_len - old_len_o)
                    other.number[i] = 0;
            }
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

    bfnum(long long num)
    {
        if (num < 0)
        {
            sign = 0;
            num = -num;
        }
        while (num > 0)
        {
            number.push_back(num % 10);
            mantissa.push_back(0);
            num /= 10;
        }
    }

    bfnum(double num, int len)
    {
        int ind = 0;
        if (num < 0)
        {
            sign = 0;
            num = -num;
        }
        long long dec = num;
        while (dec > 0)
        {
            number.push_back(dec % 10);
            mantissa.push_back(0);
            dec /= 10;
            ind++;
        }
        dec = num * 10;
        while (ind < len)
        {
            number.push_back(dec % 10);
            mantissa.push_back(1);
            num *= 10;
            dec = num * 10;
            ind++;
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
                str.push_back(0);
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
        bfnum nthis(other, this->len);
        *this = nthis;

        return *this;
    }

    bool operator==(const bfnum &other)
    {
        bfnum nthis = *this;
        bfnum nother = other;
        nthis.levelout(nother);

        if (sign != other.sign)
            return false;

        for (int i = 0; i < len; i++)
        {
            if (number[i] != other.number[i])
                return false;
        }
        return true;
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
            new_num.number[0] = new_num.number[0] % 10;

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
            bfnum null(0.0);
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

                new_num.sign = !new_num.sign;

                if (new_num == null)
                {
                    new_num.sign = 1;
                }

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

        bfnum null(0.0);
        if (nthis == null || nother == null)
            return null;
        else
        {
            bfnum new_num;
            new_num.sign = nthis.sign;
            bfnum plus;
            plus.sign = nthis.sign;
            for (int i = nother.len; i >= 0; i--)
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

        bfnum null(0.0);
        if (nother == null)
        {
            std::cout << "ERROR: dividing by zero" << std::endl;
            exit(EXIT_FAILURE);
        }
        else if (nthis == null)
        {
            return null;
        }
        else
        {
            bfnum new_num(0, nthis.len + nthis.man_len);
            nthis.levelout(new_num);
            nother.levelout(new_num);
            nthis.sign = 1;
            nother.sign = 1;
            int dec_pt = 0;
            int ind = new_num.len - 1;

            while (nthis > null)
            {
                nthis = nthis - nother;
                if (nthis < null)
                {
                    nthis = nthis + nother;
                    nthis.sign = 1;
                    break;
                }
                else if (nthis == null)
                {
                    dec_pt++;
                    break;
                }
                else
                {
                    dec_pt++;
                }
            }
            int digits = 0;
            if (dec_pt == 0)
            {
                new_num.number[ind] = 0;
                digits = 1;
            }
            while (dec_pt > 0)
            {
                new_num.number[ind] = dec_pt % 10;
                ind--;
                dec_pt /= 10;
                digits++;
            }

            if (nthis == null)
            {
                new_num.push_left(new_num.man_len);
            }
            if (nthis != null)
            {
                new_num.push_left(new_num.len - digits);
                nthis.push_left(1);
                for (int i = digits; i < new_num.len; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        nthis = nthis - nother;
                        if (nthis < null)
                        {
                            nthis = nthis + nother;
                            nthis.sign = 1;
                            new_num.number[i] = j;
                            new_num.mantissa[i] = 1;
                            break;
                        }
                        else if (nthis == null)
                        {
                            j++;
                            new_num.number[i] = j;
                            new_num.mantissa[i] = 1;
                            goto stop;
                        }
                    }
                    nthis.push_left(1);
                }
            }
        stop:
            if (this->sign == other.sign || new_num == null)
            {
                new_num.sign = 1;
            }
            else
                new_num.sign = 0;

            return new_num;
        }
    }
};