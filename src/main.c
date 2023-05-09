#include <stdlib.h>
#include <stdio.h>
#include "rutinas.h"


void rutinaPrincipal(int NCOR,int NTIN,float T, float TPLL){
    int IA = generarIntervaloDeAtencion();
    TPLL = TPLL + IA;
    float RANDOM = generarRandom();

    if(RANDOM <= 1/*0.71*/){
        printf("RUTINA DE ATENCION CORTE");
        void rutinaDeCorte(T);
    } else {
        printf("RUTINA DE ATENCION TINTURA");
    }

}

void rutinaDeCorte(float T) {
    float TACOR = generarTAdeCorte();
    float RANDOM = generarRandom();
    if(RANDOM > 1/*<=0.7*/){
        printf("RUTINA DE ELECCIÓN DE PELUQUERO");
        //I = rutinaEleccionDePeluquero();
    } else {
        printf("RUTINA DE ATENCIÓN SIN PREFERENCIA DE PELUQUERO");
        //I = rutinaAtencionSinPreferenciaCorte();
    }

    if(T >= TC[I]) {
        STOCOR[I] = STOCOR[I] + T - TC[I];
        TC[I] = T + TACOR;
    } else {
        // TODO acá falta arrepentimiento
        STEC = STEC + TC[I] - T;
        TC[I] = TC[I] + TACOR;
    }

    NTC = NTC + 1
    STACOR[I] = STACOR[I] + TACOR

    printf("RUTINA DE FINALIZACION");
    rutinaFinalizacion();
}

void rutinaFinalizacion() {
    if (T < TF) {
        printf("RUTINA PRINCIPAL");
        rutinaPrincipal();
    } else {
        printf("RUTINA DE ESTADISTICAS");
        rutinaEstadisticas();
    }
}

void rutinaEstadisticas() {
    I = 1;

    for (I = 1 ; I <= NCOR ; I++) {
        PTOCOR[I] = (STOCOR[I] * 100) / T;
        printf(PTOCOR[I]);
    }

    I = 1;

    for (I = 1 ; I <= NTIN ; I++) {
        PTOCOL[I] = (STOCOL[I] * 100) / T;
        printf(PTOCOL[I]);
    }

    float PTEC = STEC/NTCOR;
    printf("PTEC %f", PTEC);
    float PTET = STET/NTTIN;
    printf("PTET %f", PTET);
    float PP10 = (N10 * 100) / (NTCOR + NTTIN);
    printf("PP10 %f", PP10);
}

void codicionesIniciales(int NCORTES, int NTINTURA){
    printf("RUTINA PRINCIPAL"); 
    /*** DEFINICION DE CONDICIONES INICIALES*/
    float T_INICIAL = 0;
    float T_PROXIMA_LLEGADA = 0;
    rutinaPrincipal(NCORTES,NTINTURA,T_INICIAL,T_PROXIMA_LLEGADA);
}      


int main(int argc,char **argv){
    if(argc != 3){
        printf("INDICAR NCOR Y NTIN");
        return -1;
    }
    int NCOR = atoi(argv[1]);
    int NTIN = atoi(argv[2]);

    codicionesIniciales(NCOR,NTIN);
    return 0;
}