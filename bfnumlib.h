#include <iostream>

typedef class bfnum
{
    public:
        int len;
        int man_len;
        int *number;
        int *mantissa;

        bfnum(int len, int man_len)
        {
            this->len = len;
            this->man_len = man_len;
            this->number = (int *)malloc(sizeof(int) * len);
            this->mantissa = (int *)malloc(sizeof(int) * len);

            for (int i = 0; i < len; i++)
            {
                number[i] = 0;
                mantissa[i] = (len - (i + 1) < man_len) ? 1 : 0;
            }
        }

        void push_left(int num)
        {
            for (int i = 0; i < this->len; i++)
            {
                if (i + num < len) this->number[i] = this->number[i + num];
                else break;
            }
        }

        void print_num(void)
        {
            bool is_num = 0;
            bool is_frac = 0;
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
                if (this->number[i] != 0) is_num = 1;
                if (is_num == 1 || this->number[i] != 0)
                {
                    std::cout << this->number[i] << std::flush;
                }
            }
            if (is_num == 0) std::cout << 0 << std::flush;
            std::cout << std::endl;
        }

        bfnum &operator=(const bfnum &other)
        {
            this->len = other.len;
            this->man_len = other.man_len;

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
            for (int i = this->len - 1; i >= 0; i--)
            {
                this->number[i] = other % 10;
                other /= 10;
            }

            return *this;
        }

        bfnum &operator=(double other)
        {
            int num = other;
            for (int i = this->len - this->man_len - 1; i >= 0; i--)
            {
                this->number[i] = num % 10;
                num /= 10;
            }
            num = other * 10;
            for (int i = this->len - this->man_len; i < this->len; i++)
            {
                this->number[i] = num % 10;
                num *= 10;
            }

            return *this;
        }
} bfn;