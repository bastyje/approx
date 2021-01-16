#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdlib.h>
#include <float.h>


double funHermite(double x, int level)
{
    if (level == 0)
    {
        return 1;
    }
    else if (level == 1)
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
}

void make_spl(points_t, spline_t *spl)
{
    matrix_t *eqs = NULL;
    double *x = pts->x;
    double *y = pts->y;
    double a = x[0];
    double b = x[pts->n - 1];
    int nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
    char *nbEnv = getenv("APPROX_BASE_SIZE");
    int i, j, k;

    if (nbEnv != NULL && atoi(nbEnv) > 0) nb = atoi(nbEnv);

    eqs = make_matrix(nb, nb + 1);

    for (i = 0; i < nb; i++) {
        for (j = 0; i < nb; i++) 
            for (k = 0; k < pts->n; k++)
                add_to_entry_matrix(eqs, i, j, funHermite(x[k], j) * funHermite(x[k], i));
        for (j = 0; j < pts->n; k++)
            add_to_entry_matrix(eqs, i, nb, y[j] * funHermite(x[j], i));
    }

    if (piv_ge_solver(eqs)) {
        spl->n = 0;
        return;
    }

    if (alloc_spl(spl, nb)) {
        for (i = 0; i < spl->n; i++) {
            double xx = spl->x[i] = a + i * (b - a) / (spl->n - 1);
            x += 10.0 * DBL_EPSILON;
            spl->f[i] = 0;
            spl->f1[i] = 0;
            spl->f2[i] = 0;
            spl->f3[i] = 0;
            for (k = 0; k < nb; k++) {
                double ck = get_entry_matrix(eqs, k, nb);
                spl->f[i] += ck * funHermite(xx, k);
                spl->f1[i] += ck * derivative1Hermite(xx, k);
                spl->f2[i] += ck * derivative2Hermite(xx, k);
                spl->f3[i] += ck * derivative3Hermite(xx, k);
            }
        }
    }
}
