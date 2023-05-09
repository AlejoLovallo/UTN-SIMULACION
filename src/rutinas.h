#ifndef RUTINAS_DOT_H
#define RUTINAS_DOT_H

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

extern int I;
extern float TF;

float generarIntervaloDeArrivos();
float generarRandom();
float generarTAdeCorte();
float generarTAdeColor();
int rutinaEleccionDePeluquero();
int rutinaAtencionSinPreferenciaCorte(int NCOR, float TCCOR[]);
void codicionesIniciales(int *NCORTES, int *NTINTURA);
void inicializarArray(float arr[], int tam);
void rutinaPrincipal(int *NCOR, int *NTIN, float* T, float* TPLL,float TCCORTES[], float TCTINTURA[]);
void rutinaDeCorte(float T,float TCCORTES[], float TCTINTURA[],int NCORTES,int NTINTURA,float *TPLLEGADA);
void rutinaFinalizacionCorte(float *TIEMPO, int NUMERO_TOTAL_DE_CORTES,int *NCOR,int *NTIN, float STOCORTES[], float* STECORTE,float TCCOR[], float TCTIN[], float *TPLL);
void rutinaEstadisticasCorte(float T, int NCOR,float STOCOR[],float STEC, int NTCOR);
void rutinaEstadisticasTintura(float T,int NTIN, float STOCOL[],float STET,int NTTIN);
int seleccionarPeluquero();

#endif /* RUTINAS_S_H */