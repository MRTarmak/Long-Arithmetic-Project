#include <iostream>

typedef class bfnum
{
private:
    void push_left(int num)
    {
        for (int i = 0; i < this->len; i++)
        {
            if (i + num < len)
            {
                this->number[i] = this->number[i + num];
            }
            else
            {
                this->number[i] = 0;
            }
        }
    }

    void push_right(int num)
    {
        for (int i = this->len - 1; i >= 0; i--)
        {
            if (i - num >= 0)
            {
                this->number[i] = this->number[i - num];
            }
            else
            {
                this->number[i] = 0;
            }
        }
    }

    void levelout(bfnum &other)
    {
        if (this -> len != other.len || this->man_len != other.man_len)
        {
            int old_len_t = this->len;
            int old_man_len_t = this->man_len;
            int old_len_o = other.len;
            int old_man_len_o = other.man_len;

            int new_man_len = this->man_len > other.man_len ? this->man_len : other.man_len;
            int new_len = this->len > other.len ? this->len : other.len;

            this->len = new_len;
            this->man_len = new_man_len;

            this->number = (int *)realloc(this->number, sizeof(int) * this->len);
            this->mantissa = (int *)realloc(this->mantissa, sizeof(int) * this->len);
            for (int i = 0; i < this->len; i++)
            {
                this->mantissa[i] = (len - (i + 1) < man_len) ? 1 : 0;
            }

            other.len = new_len;
            other.man_len = new_man_len;

            other.number = (int *)realloc(other.number, sizeof(int) * other.len);
            other.mantissa = (int *)realloc(other.mantissa, sizeof(int) * other.len);
            for (int i = 0; i < other.len; i++)
            {
                other.mantissa[i] = (len - (i + 1) < man_len) ? 1 : 0;
            }

            if (new_len - old_len_t - (new_man_len - old_man_len_t) > 0)
                this->push_right(new_len - old_len_t - (new_man_len - old_man_len_t));
            else
                this->push_left(-(new_len - old_len_t - (new_man_len - old_man_len_t)));
            if (new_len - old_len_o - (new_man_len - old_man_len_o) > 0)
                other.push_right(new_len - old_len_o - (new_man_len - old_man_len_o));
            else
                other.push_left(-(new_len - old_len_o - (new_man_len - old_man_len_o)));
        }
    }

public:
    int len;
    int man_len;
    int *number;
    int *mantissa;
    bool sign;

    bfnum(void)
    {
        this->len = 0;
        this->man_len = 0;
        this->number = NULL;
        this->mantissa = NULL;
        this->sign = 1;
    }

    bfnum(int len, int man_len)
    {
        this->len = len;
        this->man_len = man_len;
        this->number = (int *)malloc(sizeof(int) * this->len);
        this->mantissa = (int *)malloc(sizeof(int) * this->len);
        this->sign = 1;

        for (int i = 0; i < this->len; i++)
        {
            this->number[i] = 0;
            this->mantissa[i] = (this->len - (i + 1) < this->man_len) ? 1 : 0;
        }
    }

    void print_num(void)
    {
        bool is_num = 0;
        bool is_frac = 0;
        if (this->sign == 0)
            std::cout << '-' << std::flush;
        for (int i = 0; i < this->len; i++)
        {
            if (is_num == 0 && this->mantissa[i] == 1)
            {
                std::cout << 0 << std::flush;
                is_num = 1;
            }
            if (is_frac == 0 && this->mantissa[i] == 1)
            {
                std::cout << '.' << std::flush;
                is_frac = 1;
            }
            if (this->number[i] != 0)
                is_num = 1;
            if (is_num == 1 || this->number[i] != 0)
            {
                std::cout << this->number[i] << std::flush;
            }
        }
        if (is_num == 0)
            std::cout << 0 << std::flush;
        std::cout << std::endl;
    }

    bfnum &operator=(const bfnum &other)
    {
        this->len = other.len;
        this->man_len = other.man_len;
        this->sign = other.sign;

        this->number = (int *)realloc(this->number, sizeof(int) * len);
        this->mantissa = (int *)realloc(this->mantissa, sizeof(int) * len);

        for (int i = 0; i < this->len; i++)
        {
            this->number[i] = other.number[i];
            this->mantissa[i] = other.mantissa[i];
        }

        return *this;
    }

    bfnum &operator=(int other)
    {
        if (other < 0)
        {
            this->sign = 0;
            other = -other;
        }
        for (int i = this->len - this->man_len - 1; i >= 0; i--)
        {
            this->number[i] = other % 10;
            other /= 10;
        }

        return *this;
    }

    bfnum &operator=(double other)
    {
        if (other < 0)
        {
            this->sign = 0;
            other = -other;
        }
        long num = other;
        for (int i = this->len - this->man_len - 1; i >= 0; i--)
        {
            this->number[i] = num % 10;
            num /= 10;
        }
        num = other * 10;
        for (int i = this->len - this->man_len; i < this->len; i++)
        {
            this->number[i] = num % 10;
            other *= 10;
            num = other * 10;
        }

        return *this;
    }

    bool operator==(bfnum &other)
    {
        this->levelout(other);

        for (int i = 0; i < this->len; i++)
        {
            if (this->number[i] != other.number[i]) return 0;
        }
        return 1;
    }

    bool operator!=(bfnum &other)
    {
        this->levelout(other);

        for (int i = 0; i < this->len; i++)
        {
            if (this->number[i] != other.number[i]) return 1;
        }
        return 0;
    }

    bool operator<(bfnum &other)
    {
        this->levelout(other);

        for (int i = 0; i < this->len; i++)
        {
            if (this->number[i] < other.number[i]) return 1;
            if (this->number[i] > other.number[i]) return 0;
        }
        return 0;
    }

    bool operator>(bfnum &other)
    {
        this->levelout(other);

        for (int i = 0; i < this->len; i++)
        {
            if (this->number[i] > other.number[i]) return 1;
            if (this->number[i] < other.number[i]) return 0;
        }
        return 0;
    }

    bfnum operator+(bfnum &other)
    {
        this->levelout(other);

        if (this->sign == other.sign)
        {
            bfnum new_num(this->len, this->man_len);
            new_num = *this;

            for (int i = this->len - 1; i > 0; i--)
            {
                new_num.number[i] += other.number[i];
                new_num.number[i - 1] += new_num.number[i] / 10;
                new_num.number[i] = new_num.number[i] % 10;
            }
            new_num.number[0] = new_num.number[0] % 10;

            return new_num;
        }
        else
        {
            if (*this > other)
            {
                bfnum new_num(this->len, this->man_len);
                new_num = *this;

                for (int i = this->len - 1; i >= 0; i--)
                {
                    new_num.number[i] -= other.number[i];
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

                return new_num;
            }
            else
            {
                bfnum new_num(other.len, other.man_len);
                new_num = other;

                for (int i = other.len - 1; i >= 0; i--)
                {
                    new_num.number[i] -= this->number[i];
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

                return new_num;
            }
        }
    }

    bfnum operator-(bfnum &other)
    {
        this->levelout(other);

        if (this->sign == other.sign)
        {
            if (*this > other)
            {
                bfnum new_num(this->len, this->man_len);
                new_num = *this;

                for (int i = this->len - 1; i >= 0; i--)
                {
                    new_num.number[i] -= other.number[i];
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

                return new_num;
            }
            else
            {
                bfnum new_num(other.len, other.man_len);
                new_num = other;

                for (int i = other.len - 1; i >= 0; i--)
                {
                    new_num.number[i] -= this->number[i];
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

                return new_num;
            }
        }
        else
        {
            bfnum new_num(this->len, this->man_len);
            new_num = *this;

            for (int i = this->len - 1; i > 0; i--)
            {
                new_num.number[i] += other.number[i];
                new_num.number[i - 1] += new_num.number[i] / 10;
                new_num.number[i] = new_num.number[i] % 10;
            }
            new_num.number[0] = new_num.number[0] % 10;

            return new_num;
        }
    }

    bfnum operator*(bfnum &other)
    {
        this->levelout(other);
        this->print_num(); //
        other.print_num(); //

        bfnum null(1, 1);
        if (*this == null || other == null) return null;
        else
        {
            bfnum new_num(this->len, this->man_len);
            new_num.sign = this->sign;
            bfnum plus(this->len, this->man_len);
            plus.sign = this->sign;
            for (int i = other.len; i >= 0; i--)
            {
                if (other.number[i] != 0)
                {
                    for (int j = 0; j < other.number[i]; j++)
                    {
                        plus = plus + *this;
                    }
                    if (this->len - this->man_len - 1 - i < 0)
                    {
                        plus.push_right(i - (this->len - this->man_len - 1));
                    }
                    else
                    {
                        plus.push_left(this->len - this->man_len - 1 - i);
                    }
                    new_num = new_num + plus;
                    plus = 0;
                }
            }
            if (this->sign == other.sign || new_num == null)
            {
                new_num.sign = 1;
            }
            else new_num.sign = 0;
            
            free(null.number);
            free(null.mantissa);
            free(plus.number);
            free(plus.mantissa);

            return new_num;
        }
    }
} bfn;