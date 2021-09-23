#ifndef FASOR_H
#define FASOR_H

#ifndef DFT_H
#include "DFT.h"
#endif
#ifndef FREQUENCIA_H
#include "Frequencia.h"
#endif
#ifndef FILTROIIR_H
#include "FiltroIIR.h"
#endif
#ifndef DECIMACAO_H
#include "Decimacao.h"
#endif

#include "FiltroMediaMovel.h"

struct Fasor
{
    double fase, fase_rep, fase_mm, fase_corr;
    double magnitude, mag_rep, mag_mm;
    double frequencia = 0, freq_mm, freq_rep;

    DFT dft;
    EstimacaoFrequencia est_freq;
    IIR iir;
    Decimador decim_sinal;
    Decimador decim_fase;
    Decimador decim_mag;
    Decimador decim_freq;
    FMM fmm_fase;
    FMM fmm_mag;

    //SG sg1;
    //SG sg2;
};

void estimaFasor(Fasor *fasor, double amostra);


#endif