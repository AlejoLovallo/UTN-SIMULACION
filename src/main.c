#include <stdlib.h>
#include <stdio.h>
#include "rutinas.h"

int I = 0;
float TF = 5000.0;


void codicionesIniciales(int *NCORTES, int *NTINTURA){
    printf("RUTINA PRINCIPAL\n"); 
    /*** DEFINICION DE CONDICIONES INICIALES*/
    float T_INICIAL = 0;
    float T_PROXIMA_LLEGADA = 0;
    int ncort = *NCORTES;
    int ntint = *NTINTURA;

    float TCCOR[ncort];
    float TCTIN[ntint];
    
    inicializarArray(TCCOR,*NCORTES);
    inicializarArray(TCTIN,*NTINTURA);

    rutinaPrincipal(NCORTES,NTINTURA,&T_INICIAL,&T_PROXIMA_LLEGADA,TCCOR,TCTIN);
}  


int main(int argc,char **argv){
    if(argc != 3){
        printf("INDICAR NCOR Y NTIN\n");
        return -1;
    }
    int NCOR = atoi(argv[1]);
    int NTIN = atoi(argv[2]);

    codicionesIniciales(&NCOR,&NTIN);
    return 0;
}