#include "rutinas.h"

void inicializarArray(float arr[], int tam) {
    for (int i = tam ; i <= tam ; i++) {
        arr[i] = 0.f;
    }
}

float generarIntervaloDeArrivos(){
    float f = generarRandom();
    if (f == 1) {
        f = generarRandom();
    }

    float g = -1.1141*log(f);
    f=fmax(-8.1266*log(g), 0.0);

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
    for (int J=1 ; J <= NCOR ; J++) {
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
    float STEC = 0; // CREO QUUE NO VAN ACÁ
    float STOCOR[NCORTES]; // CREO QUUE NO VAN ACÁ
    //float STACOR[NCORTES];
    int NTC = 0;

    if(RANDOM > 1/*<=0.7*/){
        printf("RUTINA DE ELECCIÓN DE PELUQUERO\n");
        //I = rutinaEleccionDePeluquero();
    } else {
        printf("RUTINA DE ATENCIÓN SIN PREFERENCIA DE PELUQUERO\n");
        I = rutinaAtencionSinPreferenciaCorte(NCORTES,TCCORTES);
    }

    printf("\nAAAAAAAAAAAAAAAAAAAA I: %d \n", I);
    printf("\nAAAAAAAAAAAAAAAAAAAA T: %f \n", T);
    printf("\nAAAAAAAAAAAAAAAAAAAA TC: %f \n", TCCORTES[I]);

    if(T > TCCORTES[I]) {
        STOCOR[I] = STOCOR[I] + T - TCCORTES[I];
        printf("\n\n\nSTOCOR(%d) = %.2f\n\n\n", I, STOCOR[I]);
        TCCORTES[I] = T + TACOR;
    } else {
        // TODO acá falta arrepentimiento
        STEC = STEC + TCCORTES[I] - T;
        TCCORTES[I] = TCCORTES[I] + TACOR;
    }
    NTC = NTC + 1;
    printf("\n\n\nSTOCOR(%d) = %.2f\n\n\n", 1, STOCOR[1]);

    //STACOR[I] = STACOR[I] + TACOR;


    printf("ACA ENTRARIA A RUTINA DE FINALIZACION DE CORTE\n");
    rutinaFinalizacionCorte(&T,NTC,&NCORTES,&NTINTURA,STOCOR,&STEC,TCCORTES,TCTINTURA,TPLLEGADA);
}

void rutinaFinalizacionCorte(float *TIEMPO, int NUMERO_TOTAL_DE_CORTES,int *NCOR,int *NTIN, float STOCORTES[], float* STECORTE,float TCCOR[], float TCTIN[], float *TPLL) {
    printf("\nTIEMPO: %f\n", *TIEMPO);
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

int seleccionarPeluquero(){

    float r = generarRandom();
    int i;

    if(r < 0.1){
        i = 1;
    }else if (r > 0.1 && r < 0.2){
        i = 2;
    }else if (r > 0.2 && r < 0.3){
        i = 3;
    }else if (r > 0.3 && r < 0.4){
        i = 4;
    }else if (r > 0.4 && r < 0.5){
        i = 5;
    }else if (r > 0.5 && r < 0.6){
        i = 6;
    }else if (r > 0.65 && r < 0.7){
        i = 7;
    }else if (r > 0.7 && r < 0.75){
        i = 8;
    }else if (r > 0.75 && r < 0.8){
        i = 9;
    }else if (r > 0.8 && r < 0.85){
        i = 10;
    }else if (r > 0.85 && r < 0.9){
        i = 11;
    }else if (r > 0.9 && r < 0.95){
        i = 12;
    }else{
        i = 13;
    }
    return i;
}