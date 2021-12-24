#include <stdio.h>
#include <math.h>

const double  x_min = -0.4, x_max = 2.5;
const double h = 0.05,eps = 0.001;
const int  intervals = (x_max-x_min)/h-1;

double f(double x)
{
    return pow(x-1,2)*log10(x+11)-1;
}

double find_root(double x1, double x2)
{
    double x = (x1+x2)/2;

    if(f(x) < eps)
        return x;

    if (f(x1)*f(x) <0)
        find_root(x,x1);

    if(f(x2)*f(x) < 0)
        find_root(x2,x);
}

int main(void)
{
    double* y = (double*)malloc(intervals*sizeof(double));
    double x = x_min;

    for(int i = 0; i < intervals; x += h, i++)
    {
        y[i] = f(x);
    }

    for(int i = 0;i<intervals-1;i++)
    {
        if(y[i]*y[i+1] < 0)
        {
            printf("корень: %lf \n",find_root(x_min+(i*h),x_min+(i*h)+h));
        }
    }
    free(y);
    return 0;
}
