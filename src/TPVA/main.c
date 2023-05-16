#include <stdlib.h>
#include <stdio.h>
#include "tpVA.h"

int main(void)
{
    int cantidadVeces = 1000;
    int corridas = 1;
    int valores[51];

    inicializarArray(valores, 51);

    while (corridas <= cantidadVeces)
    {

        int valor = (int)generarValor();

        valores[valor - 20] += 1;

        corridas++;
    }

    for (int i = 0; i < 50; i++)
    {
        printf("Cantidad de veces que salió el %d: %d\n", i + 20, valores[i]);
    }
}