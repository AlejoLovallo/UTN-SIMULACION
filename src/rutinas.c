#include "rutinas.h"
#include <stdio.h>
#include <stdlib.h>

int generarIntervaloDeAtencion(){
    return 0;
}

float generarRandom(){
    return (float) rand() / RAND_MAX;
}

float generarTAdeCorte() {
    float R = generarRandom();
    return 32.395 / pow( ( 1 / pow(R,1.7143) ) - 1, 0.078229);
}

float generarTAdeColor() {
    float R = generarRandom();
    return 10.648 / pow( ( 1 / pow(R,1.29749) ) - 1, 0.040813);
}

/*int rutinaEleccionDePeluquero() {
    float R = generarRandom();
    if (R <= ) {

    } else if (R <= ) {

    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else if (R <= ) {
        
    } else {

    }
}

int rutinaAtencionSinPreferenciaCorte() {
    int I = 1;
    for (int J=1 ; J < NCOR ; J++) {
        if (TC[I] > TC[J]) {
            I = J;
        }
    }
}*/