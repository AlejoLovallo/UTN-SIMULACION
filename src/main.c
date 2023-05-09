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
    float TF = 1000.0;
    float T_INICIAL = 0;
    float T_PROXIMA_LLEGADA = 0;
    int NCOR = 13;
    int NTCOR = 0;
    int contador_simulaciones = 0;
    float TCCOR[NCOR];
    /***** TERMINACION DE CONDICIONES INICIALES ******/

    /**** VARIABLES DE RESULTADO ********/
    float STECOR = 0;
    float PTEC = 0;
    float STOCOR[NCOR];
    float STACOR[NCOR];
    float PTO[NCOR];
    /***** FINALIZACION DE VARIABLES DE RESULTADO *******/
    
    inicializarArray(TCCOR, NCOR);
    inicializarArray(STOCOR, NCOR);
    inicializarArray(STACOR, NCOR);
    inicializarArray(PTO, NCOR);
    

    while(T<TF){
        contador_simulaciones++;
        T = T_PROXIMA_LLEGADA;
        float IA = generarIntervaloDeArrivos();
        T_PROXIMA_LLEGADA = T + IA;
        float TACOR = generarTAdeCorte();
        float RAND = generarRandom();
        if (RAND <= 0.7){ 
            printf("---- RUTINA DE SELECCION DE PELUIQUERO -----\n");
            i = seleccionarPeluquero();
        }else{
            printf("---- RUTINA SIN SELECCION DE PELUIQUERO -----\n");
            i = 0;
            j = 1;
            while(j < NCOR){
                if(TCCOR[i] > TCCOR[j]){
                    i = j;
                }
                j = j + 1;
            }
        }

        if(T >= TCCOR[i]){
            STOCOR[i] =  STOCOR[i] + T - TCCOR[i];
            TCCOR[i] = T + TACOR;
        }else{
            STECOR = STECOR + TCCOR[i] - T;
            TCCOR[i] = TCCOR[i] + TACOR;
        }
        
        NTCOR = NTCOR + 1;
        STACOR[i] = STACOR[i] + TACOR;
    }
    
    i = 0;
    j = 1;

    while(j < NCOR){
        PTO[j] = STOCOR[j] * 100 / T;
        printf("--------- PTO CORTE %d: %f ---------------\n",NCOR,PTO[j]);
        j = j + 1;
    }
    PTEC = STECOR/NTCOR;
    printf("--------- PTEC GLOBAL: %f ---------------\n",PTEC);
    
    printf("--------- CANTIDAD DE SIMULACIONES %d---------------\n",contador_simulaciones);
    

    return 0;
}
