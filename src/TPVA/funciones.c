#include "tpVA.h"

float generarValor()
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

void inicializarArray(int arr[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        arr[i] = 0.0;
    }
}