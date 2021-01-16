#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdlib.h>

double funHermite(double x, int level)
{
    if(level = 0)
    {
        return 1;
    }
    else if(level = 1)
    {
        return 2*x;
    }

    return 2*x*funHermite(x, level-1) - 2*(level-1)*funHermite(x, level - 2);
}