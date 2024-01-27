#include <iostream>

typedef struct bfnum
{
    int len;
    int man_len;
    bfnum(int len, int man_len)
    {
        this->number = (char *)malloc(sizeof(char) * len);
        this->mantissa = (char *)malloc(sizeof(char) * len);
        for (int i = 0; i < len; i++)
        {
            number[i] = 0;
            mantissa[i] = (len - (i + 1) <= man_len) ? 1 : 0;
        }
    }
    char *number;
    char *mantissa;

} bfn;