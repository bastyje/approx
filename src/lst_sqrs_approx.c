#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdlib.h>
#include <float.h>
#include <math.h>

double funHermite(double x, int level, double **funk)
{
    if (level == 0)
    {
        return 1.0;
    }
    else if (level == 1)
    {
        return 2.0 * x;
    }

    double temp1, temp2;

    if (isnan(funk[0][level - 1]))
    {
        funk[0][level - 1] = funHermite(x, level - 1, funk);
        
    }

    temp1 = funk[0][level - 1];

    if (isnan(funk[0][level - 2]))
    {
        funk[0][level - 2] = funHermite(x, level - 2, funk);
    }

    temp2 = funk[0][level - 2];

    return 2 * x * temp1 - 2 * (level - 1) * temp2;
}

double derivative1Hermite(double x, int level, double **funk)
{
    if (level == 0)
    {
        return 0.0;
    }
    else if (level == 1)
    {
        return 2.0;
    }

    double temp1;
    double temp2;
    double temp3;

    if (isnan(funk[0][level - 1]))
    { 
        funk[0][level - 1] = funHermite(x, level - 1, funk);
    }

    temp1 = funk[0][level - 1];

    if (isnan(funk[1][level - 1]))
    {
        funk[1][level - 1] = derivative1Hermite(x, level - 1, funk);
    }

    temp2 = funk[1][level - 1];

    if (isnan(funk[1][level - 2]))
    {
        funk[1][level - 2] = derivative1Hermite(x, level - 2, funk);
    }

    temp3 = funk[1][level - 2];

    return 2 * temp1 + 2 * x * temp2 - 2 * (level - 1) * temp3;
}

double derivative2Hermite(double x, int level, double **funk)
{
    if (level == 0 || level == 1)
    {
        return 0.0;
    }

    double temp1, temp2, temp3;

    if (isnan(funk[1][level - 1]))
    {
        funk[1][level - 1] = derivative1Hermite(x, level - 1, funk);
    }

    temp1 = funk[1][level - 1];

    if (isnan(funk[2][level - 1]))
    {
        funk[2][level - 1] = derivative2Hermite(x, level - 1, funk);
    }

    temp2 = funk[2][level - 1];

    if (isnan(funk[2][level - 2]))
    {
        funk[2][level - 2] = derivative2Hermite(x, level - 2, funk);
    }

    temp3 = funk[2][level - 2];
    return 4 * temp1 + 2 * x * temp2 - 2 * (level - 1) * temp3;
}

double derivative3Hermite(double x, int level, double **funk)
{
    if (level == 0 || level == 1 || level == 2)
    {
        return 0.0;
    }

    double temp1, temp2, temp3;

    if (isnan(funk[2][level - 1]))
    {
        funk[2][level - 1] = derivative2Hermite(x, level - 1, funk);
    }

    temp1 = funk[2][level - 1];

    if (isnan(funk[3][level - 1]))
    {
        funk[3][level - 1] = derivative3Hermite(x, level - 1, funk);
    }

    temp2 = funk[3][level - 1];

    if (isnan(funk[3][level - 2]))
    {
        funk[3][level - 2] = derivative3Hermite(x, level - 2, funk);
    }

    temp3 = funk[3][level - 2];

    return 6 * temp1 + 2 * x * temp2 - 2 * (level - 1) * temp3;
}

double valueHermite(double x, int level)
{
    double **valueTabHermite = malloc(sizeof(double*)*4);
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        valueTabHermite[i] = malloc(sizeof(double)*level);
    } 

    int j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < level; j++)
        {
            valueTabHermite[i][j] = NAN;
        }
    }

    double result = funHermite(x, level, valueTabHermite);

    for(i = 0; i < 4; i++)
    {
        free(valueTabHermite[i]);
    }
    free(valueTabHermite);

    return result;
}

double valueDerivative1(double x, int level)
{
    double **valueHermite = malloc(sizeof(double*)*4);
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        valueHermite[i] = malloc(sizeof(double)*level);
    } 

    int j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < level; j++)
        {
            valueHermite[i][j] = NAN;
        }
    }

    double result = derivative1Hermite(x, level, valueHermite);

    for(i = 0; i < 4; i++)
    {
        free(valueHermite[i]);
    }
    free(valueHermite);

    return result;
}

double valueDerivative2(double x, int level)
{
    double **valueHermite = malloc(sizeof(double*)*4);
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        valueHermite[i] = malloc(sizeof(double)*level);
    } 

    int j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < level; j++)
        {
            valueHermite[i][j] = NAN;
        }
    }

    double result = derivative2Hermite(x, level, valueHermite);

    for(i = 0; i < 4; i++)
    {
        free(valueHermite[i]);
    }
    free(valueHermite);

    return result;
}

double valueDerivative3(double x, int level)
{
    double **valueHermite = malloc(sizeof(double*)*4);
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        valueHermite[i] = malloc(sizeof(double)*level);
    } 

    int j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < level; j++)
        {
            valueHermite[i][j] = NAN;
        }
    }

    double result = derivative3Hermite(x, level, valueHermite);

    for(i = 0; i < 4; i++)
    {
        free(valueHermite[i]);
    }
    free(valueHermite);

    return result;
}

void make_spl(points_t *pts, spline_t *spl)
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
                add_to_entry_matrix(eqs, i, j, valueHermite(x[k], j) * valueHermite(x[k], i));
        for (j = 0; j < pts->n; k++)
            add_to_entry_matrix(eqs, i, nb, y[j] * valueHermite(x[j], i));
    }

    if (piv_ge_solver(eqs)) {
        spl->n = 0;
        return;
    }

    if (alloc_spl(spl, nb)) {
        for (i = 0; i < spl->n; i++) {
            double xx = spl->x[i] = a + i * (b - a) / (spl->n - 1);
            xx += 10.0 * DBL_EPSILON;
            spl->f[i] = 0;
            spl->f1[i] = 0;
            spl->f2[i] = 0;
            spl->f3[i] = 0;
            for (k = 0; k < nb; k++) {
                double ck = get_entry_matrix(eqs, k, nb);
                spl->f[i] += ck * valueHermite(xx, k);
                spl->f1[i] += ck * valueDerivative1(xx, k);
                spl->f2[i] += ck * valueDerivative2(xx, k);
                spl->f3[i] += ck * valueDerivative3(xx, k);
            }
        }
    }
}
