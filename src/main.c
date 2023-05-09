#include <stdlib.h>
#include <stdio.h>
#include "rutinas.h"


void rutinaPrincipal(int NCOR,int NTIN,int T, int TPLL){
    int IA = generarIntervaloDeAtencion();
    TPLL = TPLL + IA;
    float RANDOM = generarRandomPorcentajeDeAtencion();

    if(RANDOM <= 0.71){
        printf("RUTINA DE ATENCION CORTE");
    }else{
        printf("RUTINA DE ATENCION TINTURA");
    }

}

void codicionesIniciales(int NCORTES, int NTINTURA){
    printf("RUTINA PRINCIPAL"); 
    /*** DEFINICION DE CONDICIONES INICIALES*/
    int T_INICIAL = 0;
    int T_PROXIMA_LLEGADA = 0;
    rutinaPrincipal(NCORTES,NTINTURA,T_INICIAL,T_PROXIMA_LLEGADA);
}      


int main(int argc,char **argv){
    if(argc != 3){
        printf("INDICAR NCOR Y NTIN");
        return -1;
    }
    int NCOR = atoi(argv[1]);
    int NTIN = atoi(argv[2]);

    rutinaPrincipal(NCOR,NTIN);
    return 0;
}