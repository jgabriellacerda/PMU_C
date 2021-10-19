#ifndef FASOR_H
#define FASOR_H

#include "DFT.h"
#include "Frequencia.h"
#include "FiltroMediaMovel.h"

struct Fasor
{
    double fase, fase_mm, fase_corr;
    double magnitude, mag_mm;
    double frequencia = 0, freq_mm;

    DFT* dft;
    EstimacaoFrequencia est_freq;
    FMM fmm_fase;
    FMM fmm_mag;
};

Fasor* new_fasor(int fs);

void estimaFasor(Fasor *fasor, double amostra, bool flag);


#endif