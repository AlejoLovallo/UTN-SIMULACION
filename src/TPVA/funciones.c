#include "tpVA.h"

float generarValor(int dias)
{
    float f = generarRandom();
    if (f == 1)
    {
        f = generarRandom();
    }

    f = 50 * f + 20;

    return f;
}

float generarRandom()
{
    double a = ((double)rand()) / ((double)RAND_MAX);
    return (float)a;
}