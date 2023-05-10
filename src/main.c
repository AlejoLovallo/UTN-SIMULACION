#include <stdlib.h>
#include <stdio.h>
#include "rutinas.h"

int I = 0;
float TF = 1.0;

void codicionesIniciales(int *NCORTES, int *NTINTURA)
{
    printf("RUTINA PRINCIPAL\n");
    /*** DEFINICION DE CONDICIONES INICIALES*/
    float T_INICIAL = 0;
    float T_PROXIMA_LLEGADA = 0;
    int ncort = *NCORTES;
    int ntint = *NTINTURA;

    float TCCOR[ncort];
    float TCTIN[ntint];

    inicializarArray(TCCOR, *NCORTES);
    inicializarArray(TCTIN, *NTINTURA);

    rutinaPrincipal(NCORTES, NTINTURA, &T_INICIAL, &T_PROXIMA_LLEGADA, TCCOR, TCTIN);
}

// int main(int argc,char **argv){
//     if(argc != 3){
//         printf("INDICAR NCOR Y NTIN\n");
//         return -1;
//     }
//     int NCOR = atoi(argv[1]);
//     int NTIN = atoi(argv[2]);

//     srand(time(NULL));
//     codicionesIniciales(&NCOR,&NTIN);
//     return 0;
// }

int main(void)
{
    /*** DEFINICION DE CONDICIONES INICIALES*/
    int i, j;
    int I = 0;
    float T = 0;
    float TF = 100000.0;
    float cantDias = TF / 600;
    float T_INICIAL = 0;
    float T_PROXIMA_LLEGADA = 0;
    int NCOR = 15;
    int NCOL = 6;
    int NTCOR = 0;
    int NTCOL = 0;
    int NP10 = 0;
    float PP10;
    int contador_simulaciones = 0;
    float TCCOR[NCOR];
    float TCCOL1[NCOL];
    float TCCOL2[NCOL];
    float TCCOL3[NCOL];
    float menor;
    int X;
    int Z;
    /***** TERMINACION DE CONDICIONES INICIALES ******/

    /**** VARIABLES DE RESULTADO ********/
    float STECOR = 0;
    float PTECOR = 0;
    float PIGCOR;
    float SIGCOR = 0;
    float STECOL = 0;
    float PTECOL = 0;
    float PIGCOL;
    float SIGCOL = 0;
    float STOCOR[NCOR];
    float STOCOL[NCOL];
    float STACOR[NCOR];
    float STACOL[NCOL];
    float PTOCOR[NCOR];
    float PTOCOL[NCOL];
    /***** FINALIZACION DE VARIABLES DE RESULTADO *******/

    inicializarArray(TCCOR, NCOR);
    inicializarArray(STOCOR, NCOR);
    inicializarArray(STACOR, NCOR);
    inicializarArray(PTOCOR, NCOR);
    inicializarArray(TCCOL1, NCOL);
    inicializarArray(TCCOL2, NCOL);
    inicializarArray(TCCOL3, NCOL);
    inicializarArray(STOCOL, NCOL);
    inicializarArray(STACOL, NCOL);
    inicializarArray(PTOCOL, NCOL);

    while (T < TF)
    {
        contador_simulaciones++;
        T = T_PROXIMA_LLEGADA;
        float IA = generarIntervaloDeArrivos();
        printf("IA %f \n", IA);
        T_PROXIMA_LLEGADA = T + IA;
        float RAN = generarRandom();

        if (RAN < 0.71)
        {
            SIGCOR = SIGCOR + 1500;
            float TACOR = generarTAdeCorte();
            printf("TACOR %f \n", TACOR);
            float RAND = generarRandom();
            if (RAND <= 0.7)
            {
                printf("---- RUTINA DE SELECCION DE PELUQUERO -----\n");
                i = seleccionarPeluquero();
            }
            else
            {
                printf("---- RUTINA SIN SELECCION DE PELUQUERO -----\n");
                i = 0;
                j = 1;
                while (j < NCOR)
                {
                    if (TCCOR[i] >= TCCOR[j])
                    {
                        printf("TCCOR %f \n", TCCOR[j]);
                        i = j;
                    }
                    j = j + 1;
                }
            }

            printf("TCCOR %f \n", TCCOR[j]);
            printf("T %f \n", T);
            printf("i %d \n", i);
            printf("j %d \n", j);

            if (T >= TCCOR[i])
            {
                STOCOR[i] = STOCOR[i] + T - TCCOR[i];
                TCCOR[i] = T + TACOR;
            }
            else
            {
                if (TCCOR[i] - T > 10)
                {
                    NP10 = NP10 + 1;
                }
                STECOR = STECOR + TCCOR[i] - T;
                TCCOR[i] = TCCOR[i] + TACOR;
            }

            printf("TCCOR %f \n", TCCOR[j]);
            NTCOR = NTCOR + 1;
            STACOR[i] = STACOR[i] + TACOR;
        }
        else
        {
            SIGCOL = SIGCOL + 3500;
            printf("Nuevo run\n");
            float TACOL = generarTAdeColor();
            printf("TACOL %f \n", TACOL);
            float RAN = generarRandom();

            if (RAN < 0.4)
            {
                printf("---- RUTINA DE SELECCION DE COLORISTA -----\n");
                i = seleccionarColorista();
                X = buscarMenor(TCCOL1, TCCOL2, TCCOL3, i);
            }
            else
            {
                printf("---- RUTINA SIN SELECCION DE COLORISTA -----\n");
                i = 0;
                j = 1;
                menor = TCCOL1[i];
                X = 1;
                while (j < NCOL)
                {
                    if (menor >= TCCOL1[j])
                    {
                        menor = TCCOL1[j];
                        i = j;
                    }
                    j = j + 1;
                }
                j = 1;
                while (j < NCOL)
                {
                    if (menor >= TCCOL2[j])
                    {
                        menor = TCCOL2[j];
                        i = j;
                        X = 2;
                    }
                    j = j + 1;
                }
                j = 1;
                while (j < NCOL)
                {
                    if (menor >= TCCOL3[j])
                    {
                        menor = TCCOL3[j];
                        i = j;
                        X = 3;
                    }
                    j = j + 1;
                }
                if (X == 1)
                {
                    if (T >= TCCOL1[i])
                    {
                        Z = buscarMayor(TCCOL1, TCCOL2, TCCOL3, i);
                        if (Z == 2)
                        {
                            if (T >= TCCOL2[i])
                            {
                                STOCOL[i] = STOCOL[i] + T - TCCOL2[i];
                            }
                        }
                        else
                        {
                            if (T >= TCCOL3[i])
                            {
                                STOCOL[i] = STOCOL[i] + T - TCCOL3[i];
                            }
                        }
                        TCCOL1[i] = T + TACOL;
                    }
                    else
                    {
                        if (TCCOL1[i] - T > 10)
                        {
                            NP10 = NP10 + 1;
                        }
                        STECOL = STECOL + TCCOL1[i] - T;
                    }
                }
                else if (X == 2)
                {
                    if (T >= TCCOL2[i])
                    {
                        Z = buscarMayor(TCCOL1, TCCOL2, TCCOL3, i);
                        if (Z == 1)
                        {
                            if (T >= TCCOL1[i])
                            {
                                STOCOL[i] = STOCOL[i] + T - TCCOL1[i];
                            }
                        }
                        else
                        {
                            if (T >= TCCOL3[i])
                            {
                                STOCOL[i] = STOCOL[i] + T - TCCOL3[i];
                            }
                        }
                        TCCOL2[i] = T + TACOL;
                    }
                    else
                    {
                        if (TCCOL2[i] - T > 10)
                        {
                            NP10 = NP10 + 1;
                        }
                        STECOL = STECOL + TCCOL2[i] - T;
                    }
                }
                else
                {
                    if (T >= TCCOL3[i])
                    {
                        Z = buscarMayor(TCCOL1, TCCOL2, TCCOL3, i);
                        if (Z == 2)
                        {
                            if (T >= TCCOL2[i])
                            {
                                STOCOL[i] = STOCOL[i] + T - TCCOL2[i];
                            }
                        }
                        else
                        {
                            if (T >= TCCOL1[i])
                            {
                                STOCOL[i] = STOCOL[i] + T - TCCOL1[i];
                            }
                        }
                        TCCOL3[i] = T + TACOL;
                    }
                    else
                    {
                        if (TCCOL3[i] - T > 10)
                        {
                            NP10 = NP10 + 1;
                        }
                        STECOL = STECOL + TCCOL3[i] - T;
                    }
                }
            }
            NTCOL = NTCOL + 1;
            STACOL[i] = STACOL[i] + TACOL;
        }
    }

    PTECOR = STECOR / NTCOR;

    PTECOL = STECOL / NTCOL;

    PIGCOR = (SIGCOR / NCOR) / cantDias;

    PIGCOL = (SIGCOL / NCOL) / cantDias;

    PP10 = NP10 * 100 / (NTCOR + NTCOL);

    printf("--------- PTECOR GLOBAL: %f ---------------\n", PTECOR);
    printf("--------- PTECOL GLOBAL: %f ---------------\n", PTECOL);
    printf("--------- PIGCOR GLOBAL: %f ---------------\n", PIGCOR);
    printf("--------- PIGCOL GLOBAL: %f ---------------\n", PIGCOL);
    printf("--------- PP10 GLOBAL: %f ---------------\n", PP10);

    j = 0;

    while (j < NCOR)
    {
        PTOCOR[j] = STOCOR[j] * 100 / T;
        printf("--------- PTO CORTE %d: %f ---------------\n", j + 1, PTOCOR[j]);
        // printf("--------- STA CORTE %d: %f ---------------\n", j + 1, STACOR[j]);
        // printf("--------- STO CORTE %d: %f ---------------\n", j + 1, STOCOR[j]);
        j = j + 1;
    }

    // printf("--------- STECOR: %f ---------------\n", STECOR);
    // printf("--------- NTCOR: %d ---------------\n", NTCOR);

    j = 0;

    while (j < NCOL)
    {
        PTOCOL[j] = STOCOL[j] * 100 / T;
        printf("--------- PTO COLOR %d: %f ---------------\n", j + 1, PTOCOL[j]);
        // printf("--------- STA COLOR %d: %f ---------------\n", j + 1, STACOL[j]);
        // printf("--------- STO COLOR %d: %f ---------------\n", j + 1, STOCOL[j]);
        j = j + 1;
    }

    // printf("--------- STECOL: %f ---------------\n", STECOL);
    // printf("--------- NTCOL: %d ---------------\n", NTCOL);

    printf("--------- CANTIDAD DE SIMULACIONES %d---------------\n", contador_simulaciones);

    return 0;
}
