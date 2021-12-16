 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

uint sign(uint value)
{
    value >>= 31;
    return value;
}

uint mantissa(uint value)
{
    value <<= 9;
    value >>= 9;
    value = value | 8388608;
    return value;
}

int order(uint value)
{
    value <<= 1;
    value >>= 1;
    value >>= 23;
    return value;
}

uint integer_part(uint value)
{
    int p = order(value)-127;
    value = mantissa(value);
    value >>= (23-p);
    return value;
}

void bin (uint value)
{
    char bits[33];
    for(int i = 0;i<32;i++)
        bits[i] = '0';
    bits[32] = '\0';
    for(int i = 0; value > 0; i++)
    {
        bits[i] = value % 2 + '0';
        value /= 2;
    }

    for(int i = 0;i<16;i++)
    {
        char tmp = bits[i];
        bits[i] = bits[31-i];
        bits[31-i] = tmp;
    }
    printf("биты числа: %s\n",bits);
}
void print(uint value)
{
    printf("обратный перевод: ");
    if(sign(value) == 1)
        printf("-");
    int p = order(value)-127;

    uint integer = mantissa(value);
    integer >>= 23-p;
    printf("%d",integer);

    value <<= 41+p;
    value >>= 41+p;

    if(value != 0)
        printf(".");

    while(value != 0)
    {
        value *= 10;
        uint t = value;
        t >>= 23-p;
        printf("%d",t);
        value <<= 41+p;
        value >>= 41+p;
    }
    printf("\n");
}


int main(void)
{
    while(true)
    {
        printf("введите число: ");
        float number;
        scanf("%f",&number);
        uint n = *(uint*)(&number);
        bin(n);
        print(n);
    }
    return 0;
}
