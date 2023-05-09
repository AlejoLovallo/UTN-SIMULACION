#include "rutinas.h"

void inicializarArray(float arr[], int tam) {
    for (int i = tam ; i <= tam ; i++) {
        arr[i] = 0.f;
    }
}

float generarIntervaloDeArrivos(){
    float f =  generarRandom();
    return f;
}

float generarRandom(){
    double a = ((double) rand()) / ((double) RAND_MAX);
    return (float) a;
}

float generarTAdeCorte() {
    float R = generarRandom();
    return 32.395 / pow( ( 1 / pow(R,1.7143) ) - 1, 0.078229);
}

float generarTAdeColor() {
    float R = generarRandom();
    return 10.648 / pow( ( 1 / pow(R,1.29749) ) - 1, 0.040813);
}

int rutinaAtencionSinPreferenciaCorte(int NCOR,float TCCOR[]) {
    int I = 1;
    for (int J=1 ; J < NCOR ; J++) {
        if (TCCOR[I] > TCCOR[J]) {
            I = J;
        }
    }
    return I;
}

void rutinaPrincipal(int *NCOR, int *NTIN, float* T, float* TPLL,float TCCORTES[], float TCTINTURA[]){
    printf("LLEGA A RUTINA PPP\n");
    float IA = generarIntervaloDeArrivos();
    *T = *TPLL;   
    *TPLL = *TPLL + IA;
    float RANDOM = generarRandom();


    if(RANDOM <= 1/*0.71*/){
        printf("RUTINA DE ATENCION CORTE\n");
        rutinaDeCorte(*T,TCCORTES,TCTINTURA,*NCOR,*NTIN,TPLL);
    } else {
        printf("RUTINA DE ATENCION TINTURA\n");
    }
}


void rutinaDeCorte(float T,float TCCORTES[], float TCTINTURA[],int NCORTES,int NTINTURA,float *TPLLEGADA) {
    float TACOR = generarTAdeCorte();
    float RANDOM = generarRandom();
    float STEC = 0;
    float STOCOR[NCORTES];
    //float STACOR[NCORTES];
    int NTC = 0;

    if(RANDOM > 1<=0.7){
        printf("RUTINA DE ELECCIÓN DE PELUQUERO\n");
        //I = rutinaEleccionDePeluquero();
    } else {
        printf("RUTINA DE ATENCIÓN SIN PREFERENCIA DE PELUQUERO\n");
        I = rutinaAtencionSinPreferenciaCorte(NCORTES,TCCORTES);
    }

    if(T >= TCCORTES[I]) {
        STOCOR[I] = STOCOR[I] + T - TCCORTES[I];
        TCCORTES[I] = T + TACOR;
    } else {
        // TODO acá falta arrepentimiento
        STEC = STEC + TCCORTES[I] - T;
        TCCORTES[I] = TCCORTES[I] + TACOR;
    }

    NTC = NTC + 1;
    //STACOR[I] = STACOR[I] + TACOR;


    printf("ACA ENTRARIA A RUTINA DE FINALIZACION DE CORTE\n");
    rutinaFinalizacionCorte(&T,NTC,&NCORTES,&NTINTURA,STOCOR,&STEC,TCCORTES,TCTINTURA,TPLLEGADA);
}

void rutinaFinalizacionCorte(float *TIEMPO, int NUMERO_TOTAL_DE_CORTES,int *NCOR,int *NTIN, float STOCORTES[], float* STECORTE,float TCCOR[], float TCTIN[], float *TPLL) {
    printf("\nTIMEMPO: %f\n", *TIEMPO);
    if (*TIEMPO < TF) {
        printf("RUTINA PRINCIPAL\n");
        printf("ACA ENTRARIA DE NUEVO A LA RUTINA PRINCIPAL\n");
        rutinaPrincipal(NCOR, NTIN, TIEMPO, TPLL,TCCOR,TCTIN);
    } else {
        printf("RUTINA DE ESTADISTICAS\n");
        printf("ACA ENTRARIA A LA RUTINA DE ESTADISTICAS DE CORTE\n");
        rutinaEstadisticasCorte(*TIEMPO, *NCOR, STOCORTES, *STECORTE, NUMERO_TOTAL_DE_CORTES);
    }
}

/**
void rutinaDeTintura(){}
**/


void rutinaEstadisticasCorte(float T, int NCOR,float STOCOR[],float STEC, int NTCOR) {
    float PTOCOR[NCOR];
    inicializarArray(PTOCOR, NCOR);


    for (int I = 1 ; I <= NCOR ; I++) {
        PTOCOR[I] = (STOCOR[I] * 100) / T;
        printf("PTOCOR(%d) = %.2f\n", I,PTOCOR[I]);
    }


    float PTEC = STEC/NTCOR;
    printf("PTEC %.2f\n", PTEC);

    //float PP10 = (N10 * 100) / (NTCOR + NTTIN);
    //printf("PP10 %.2f\n", PP10);
}


/**
void rutinaEstadisticasTintura(float T,int NTIN, float STOCOL[],float STET,int NTTIN) {
    float PTOCOL[NTIN];
    inicializarArray(PTOCOL, NTIN);

    for (int I = 1 ; I <= NTIN ; I++) {
        PTOCOL[I] = (STOCOL[I] * 100) / T;
        printf("PTO(%d): %2.f\n",I,PTOCOL[I]);
    }

    float PTET = STET/NTTIN;
    printf("PTET %.2f\n", PTET);
}
**/