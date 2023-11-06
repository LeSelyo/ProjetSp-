#include "maths_extra.h"

double absolue(double x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

static const double EPSILON = 0.00000001;

bool double_equals(double a, double b)
{
    return absolue(a - b) < EPSILON;
}

double sigmoid(double x)
{
    return (1.0 / (1.0 + exp(-x)));
}
double sigmoidbis(double x)
{
    return (x * (1.0 - x));
}

double random_weight()
{
    return ((double)rand()) / ((double)RAND_MAX);
}

double ipt_random_XOR()
{
    double res = ((double)rand()) / ((double)RAND_MAX);
    if (res > 0.5)
    {
        return 0.1;
    }
    return 0.0;
    
}