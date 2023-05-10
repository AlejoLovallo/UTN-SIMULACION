#include "rutinas.h"

void inicializarArray(float arr[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        arr[i] = 0.0;
    }
}

float generarIntervaloDeArrivos()
{
    float f = generarRandom();
    if (f == 1)
    {
        f = generarRandom();
    }

    // float g = -1.1141 * log(f);
    // f = fmax(-8.1266 * log(g), 0.0);
    // float g = -1.1141 * log(f);
    // f = fmax(-6.9266 * log(g), 0.0);

    // f = -3.8133 * log(-1 * (-1 + f)); // Lun-Jue
    f = -2.30771 * log(-1 * (-1 + f)); // Vie-Sab

    return f;
}

float generarRandom()
{
    double a = ((double)rand()) / ((double)RAND_MAX);
    return (float)a;
}

float generarTAdeCorte()
{
    float R = generarRandom();
    return 32.395 / pow((1 / pow(R, 1.7143)) - 1, 0.078229);
}

float generarTAdeColor()
{
    float R = generarRandom();
    return 106.48 / pow((1 / pow(R, 1.29749)) - 1, 0.040813);
}

int rutinaAtencionSinPreferenciaCorte(int NCOR, float TCCOR[])
{
    int I = 1;
    for (int J = 1; J <= NCOR; J++)
    {
        if (TCCOR[I] > TCCOR[J])
        {
            I = J;
        }
    }
    return I;
}

void rutinaPrincipal(int *NCOR, int *NTIN, float *T, float *TPLL, float TCCORTES[], float TCTINTURA[])
{
    printf("LLEGA A RUTINA PPP\n");
    float IA = generarIntervaloDeArrivos();
    *T = *TPLL;
    *TPLL = *TPLL + IA;
    float RANDOM = generarRandom();

    if (RANDOM <= 1 /*0.71*/)
    {
        printf("RUTINA DE ATENCION CORTE\n");
        rutinaDeCorte(*T, TCCORTES, TCTINTURA, *NCOR, *NTIN, TPLL);
    }
    else
    {
        printf("RUTINA DE ATENCION TINTURA\n");
    }
}

void rutinaDeCorte(float T, float TCCORTES[], float TCTINTURA[], int NCORTES, int NTINTURA, float *TPLLEGADA)
{
    float TACOR = generarTAdeCorte();
    float RANDOM = generarRandom();
    float STEC = 0;        // CREO QUUE NO VAN ACÁ
    float STOCOR[NCORTES]; // CREO QUUE NO VAN ACÁ
    // float STACOR[NCORTES];
    int NTC = 0;

    if (RANDOM > 1 /*<=0.7*/)
    {
        printf("RUTINA DE ELECCIÓN DE PELUQUERO\n");
        // I = rutinaEleccionDePeluquero();
    }
    else
    {
        printf("RUTINA DE ATENCIÓN SIN PREFERENCIA DE PELUQUERO\n");
        I = rutinaAtencionSinPreferenciaCorte(NCORTES, TCCORTES);
    }

    printf("\nAAAAAAAAAAAAAAAAAAAA I: %d \n", I);
    printf("\nAAAAAAAAAAAAAAAAAAAA T: %f \n", T);
    printf("\nAAAAAAAAAAAAAAAAAAAA TC: %f \n", TCCORTES[I]);

    if (T > TCCORTES[I])
    {
        STOCOR[I] = STOCOR[I] + T - TCCORTES[I];
        printf("\n\n\nSTOCOR(%d) = %.2f\n\n\n", I, STOCOR[I]);
        TCCORTES[I] = T + TACOR;
    }
    else
    {
        // TODO acá falta arrepentimiento
        STEC = STEC + TCCORTES[I] - T;
        TCCORTES[I] = TCCORTES[I] + TACOR;
    }
    NTC = NTC + 1;
    printf("\n\n\nSTOCOR(%d) = %.2f\n\n\n", 1, STOCOR[1]);

    // STACOR[I] = STACOR[I] + TACOR;

    printf("ACA ENTRARIA A RUTINA DE FINALIZACION DE CORTE\n");
    rutinaFinalizacionCorte(&T, NTC, &NCORTES, &NTINTURA, STOCOR, &STEC, TCCORTES, TCTINTURA, TPLLEGADA);
}

void rutinaFinalizacionCorte(float *TIEMPO, int NUMERO_TOTAL_DE_CORTES, int *NCOR, int *NTIN, float STOCORTES[], float *STECORTE, float TCCOR[], float TCTIN[], float *TPLL)
{
    printf("\nTIEMPO: %f\n", *TIEMPO);
    if (*TIEMPO < TF)
    {
        printf("RUTINA PRINCIPAL\n");
        printf("ACA ENTRARIA DE NUEVO A LA RUTINA PRINCIPAL\n");
        rutinaPrincipal(NCOR, NTIN, TIEMPO, TPLL, TCCOR, TCTIN);
    }
    else
    {
        printf("RUTINA DE ESTADISTICAS\n");
        printf("ACA ENTRARIA A LA RUTINA DE ESTADISTICAS DE CORTE\n");
        rutinaEstadisticasCorte(*TIEMPO, *NCOR, STOCORTES, *STECORTE, NUMERO_TOTAL_DE_CORTES);
    }
}

/**
void rutinaDeTintura(){}
**/

void rutinaEstadisticasCorte(float T, int NCOR, float STOCOR[], float STEC, int NTCOR)
{
    float PTOCOR[NCOR];
    inicializarArray(PTOCOR, NCOR);

    for (int I = 1; I <= NCOR; I++)
    {
        PTOCOR[I] = (STOCOR[I] * 100) / T;
        printf("PTOCOR(%d) = %.2f\n", I, PTOCOR[I]);
    }

    float PTEC = STEC / NTCOR;
    printf("PTEC %.2f\n", PTEC);

    // float PP10 = (N10 * 100) / (NTCOR + NTTIN);
    // printf("PP10 %.2f\n", PP10);
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

// int seleccionarPeluquero()
// {

//     float r = generarRandom();
//     int i;

//     if (r < 0.1)
//     {
//         i = 1;
//     }
//     else if (r > 0.1 && r < 0.2)
//     {
//         i = 2;
//     }
//     else if (r > 0.2 && r < 0.3)
//     {
//         i = 3;
//     }
//     else if (r > 0.3 && r < 0.35)
//     {
//         i = 4;
//     }
//     else if (r > 0.35 && r < 0.43)
//     {
//         i = 5;
//     }
//     else if (r > 0.43 && r < 0.51)
//     {
//         i = 6;
//     }
//     else if (r > 0.51 && r < 0.57)
//     {
//         i = 7;
//     }
//     else if (r > 0.57 && r < 0.62)
//     {
//         i = 8;
//     }
//     else if (r > 0.62 && r < 0.69)
//     {
//         i = 9;
//     }
//     else if (r > 0.69 && r < 0.77)
//     {
//         i = 10;
//     }
//     else if (r > 0.77 && r < 0.82)
//     {
//         i = 11;
//     }
//     else if (r > 0.82 && r < 0.91)
//     {
//         i = 12;
//     }
//     else
//     {
//         i = 13;
//     }
//     return i;
// }

// int seleccionarColorista()
// {

//     float r = generarRandom();
//     int i;

//     if (r < 0.1853)
//     {
//         i = 1;
//     }
//     else if (r > 0.1853 && r < 0.3986)
//     {
//         i = 2;
//     }
//     else if (r > 0.3986 && r < 0.6434)
//     {
//         i = 3;
//     }
//     else if (r > 0.6434 && r < 0.8147)
//     {
//         i = 4;
//     }
//     else
//     {
//         i = 5;
//     }

//     return i;
// }

int buscarMayor(float arr1[], float arr2[], float arr3[], int i)
{

    if (arr1[i] >= arr2[i] && arr1[i] >= arr3[i])
    {
        i = 1;
    }
    else if (arr2[i] >= arr1[i] && arr2[i] >= arr3[i])
    {
        i = 2;
    }
    else
    {
        i = 3;
    }

    return i;
}

int buscarMenor(float arr1[], float arr2[], float arr3[], int i)
{

    if (arr1[i] <= arr2[i] && arr1[i] <= arr3[i])
    {
        i = 1;
    }
    else if (arr2[i] <= arr1[i] && arr2[i] <= arr3[i])
    {
        i = 2;
    }
    else
    {
        i = 3;
    }

    return i;
}

// ----------- 14P y 5C

// int seleccionarPeluquero()
// {

//     float r = generarRandom();
//     int i;

//     if (r < 0.1)
//     {
//         i = 1;
//     }
//     else if (r > 0.1 && r < 0.2)
//     {
//         i = 2;
//     }
//     else if (r > 0.2 && r < 0.3)
//     {
//         i = 3;
//     }
//     else if (r > 0.3 && r < 0.35)
//     {
//         i = 4;
//     }
//     else if (r > 0.35 && r < 0.45)
//     {
//         i = 5;
//     }
//     else if (r > 0.45 && r < 0.55)
//     {
//         i = 6;
//     }
//     else if (r > 0.55 && r < 0.6)
//     {
//         i = 7;
//     }
//     else if (r > 0.6 && r < 0.65)
//     {
//         i = 8;
//     }
//     else if (r > 0.65 && r < 0.7)
//     {
//         i = 9;
//     }
//     else if (r > 0.7 && r < 0.75)
//     {
//         i = 10;
//     }
//     else if (r > 0.75 && r < 0.8)
//     {
//         i = 11;
//     }
//     else if (r > 0.8 && r < 0.85)
//     {
//         i = 12;
//     }
//     else if (r > 0.85 && r < 0.93)
//     {
//         i = 13;
//     }
//     else
//     {
//         i = 14;
//     }
//     return i;
// }

// int seleccionarColorista()
// {

//     float r = generarRandom();
//     int i;

//     if (r < 0.2)
//     {
//         i = 1;
//     }
//     else if (r > 0.2 && r < 0.45)
//     {
//         i = 2;
//     }
//     else if (r > 0.45 && r < 0.6)
//     {
//         i = 3;
//     }
//     else if (r > 0.6 && r < 0.7)
//     {
//         i = 4;
//     }
//     else
//     {
//         i = 5;
//     }

//     return i;
// }

// ----------- 14P y 6C

// int seleccionarPeluquero()
// {

//     float r = generarRandom();
//     int i;

//     if (r < 0.1)
//     {
//         i = 1;
//     }
//     else if (r > 0.1 && r < 0.2)
//     {
//         i = 2;
//     }
//     else if (r > 0.2 && r < 0.3)
//     {
//         i = 3;
//     }
//     else if (r > 0.3 && r < 0.35)
//     {
//         i = 4;
//     }
//     else if (r > 0.35 && r < 0.45)
//     {
//         i = 5;
//     }
//     else if (r > 0.45 && r < 0.55)
//     {
//         i = 6;
//     }
//     else if (r > 0.55 && r < 0.6)
//     {
//         i = 7;
//     }
//     else if (r > 0.6 && r < 0.65)
//     {
//         i = 8;
//     }
//     else if (r > 0.65 && r < 0.7)
//     {
//         i = 9;
//     }
//     else if (r > 0.7 && r < 0.75)
//     {
//         i = 10;
//     }
//     else if (r > 0.75 && r < 0.8)
//     {
//         i = 11;
//     }
//     else if (r > 0.8 && r < 0.85)
//     {
//         i = 12;
//     }
//     else if (r > 0.85 && r < 0.93)
//     {
//         i = 13;
//     }
//     else
//     {
//         i = 14;
//     }
//     return i;
// }

// int seleccionarColorista()
// {

//     float r = generarRandom();
//     int i;

//     if (r < 0.2)
//     {
//         i = 1;
//     }
//     else if (r > 0.2 && r < 0.35)
//     {
//         i = 2;
//     }
//     else if (r > 0.35 && r < 0.55)
//     {
//         i = 3;
//     }
//     else if (r > 0.55 && r < 0.7)
//     {
//         i = 4;
//     }
//     else if (r > 0.7 && r < 0.9)
//     {
//         i = 5;
//     }
//     else
//     {
//         i = 6;
//     }

//     return i;
// }

// ----------- 15P y 6C

int seleccionarPeluquero()
{

    float r = generarRandom();
    int i;

    if (r < 0.1)
    {
        i = 1;
    }
    else if (r > 0.1 && r < 0.15)
    {
        i = 2;
    }
    else if (r > 0.15 && r < 0.2)
    {
        i = 3;
    }
    else if (r > 0.2 && r < 0.27)
    {
        i = 4;
    }
    else if (r > 0.27 && r < 0.35)
    {
        i = 5;
    }
    else if (r > 0.35 && r < 0.41)
    {
        i = 6;
    }
    else if (r > 0.41 && r < 0.48)
    {
        i = 7;
    }
    else if (r > 0.48 && r < 0.57)
    {
        i = 8;
    }
    else if (r > 0.57 && r < 0.66)
    {
        i = 9;
    }
    else if (r > 0.66 && r < 0.7)
    {
        i = 10;
    }
    else if (r > 0.7 && r < 0.8)
    {
        i = 11;
    }
    else if (r > 0.8 && r < 0.85)
    {
        i = 12;
    }
    else if (r > 0.85 && r < 0.9)
    {
        i = 13;
    }
    else if (r > 0.9 && r < 0.95)
    {
        i = 14;
    }
    else
    {

        i = 15;
    }
    return i;
}

int seleccionarColorista()
{

    float r = generarRandom();
    int i;

    if (r < 0.2)
    {
        i = 1;
    }
    else if (r > 0.2 && r < 0.35)
    {
        i = 2;
    }
    else if (r > 0.35 && r < 0.55)
    {
        i = 3;
    }
    else if (r > 0.55 && r < 0.7)
    {
        i = 4;
    }
    else if (r > 0.7 && r < 0.9)
    {
        i = 5;
    }
    else
    {
        i = 6;
    }

    return i;
}
