#ifndef FASOR_H
#define FASOR_H

#include "DFT.h"
#include "Frequencia.h"
#include "FiltroMediaMovel.h"
#include <stdbool.h>

struct Fasor
{
    double fase, fase_mm, fase_corr;
    double magnitude, mag_mm;
    double frequencia;
    double freq_mm;

    bool symmetric;

    DFT *dft;
    EstimacaoFrequencia est_freq;
    FMM fmm_fase;
    FMM fmm_mag;
};
typedef struct Fasor Fasor;

Fasor *new_fasor(int fs, bool symmetric);

void estimaFasor(Fasor *fasor, double amostra, bool flag);

#endif