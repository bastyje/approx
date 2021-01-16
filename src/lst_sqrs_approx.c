#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdlib.h>

double funHermite(double x, int level)
{
    if (level = 0)
    {
        return 1;
    }
    else if (level = 1)
    {
        return 2 * x;
    }

    return 2 * x * funHermite(x, level - 1) - 2 * (level - 1) * funHermite(x, level - 2);
}

double derivative1Hermite(double x, int level)
{
    if (level == 0)
    {
        return 0.0;
    }
    else if (level == 1)
    {
        return 2.0;
    }

    return 2 * funHermite(x, level - 1) + 2 * x * derivative1Hermite(x, level - 1) - 2 * (level - 1) * derivative1Hermite(x, level - 2);
}
double derivative2Hermite(double x, int level)
{
    if (level == 0 || level == 1)
    {
        return 0.0;
    }

    return 4 * derivative1Hermite(x, level - 1) + 2 * x * derivative2Hermite(x, level - 1) - 2 * (level - 1) * derivative2Hermite(x, level - 2);
}

double derivative3Hermite(double x, int level)
{
    if (level == 0 || level == 1 || level == 2)
    {
        return 0.0;
    }

    return 6 * derivative2Hermite(x, level - 1) + 2 * x * derivative3Hermite(x, level - 1) - 2 * (level - 1) * derivative3Hermite(x, level - 2);
}