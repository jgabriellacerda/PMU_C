#ifndef DECIMACAO_H
#define DECIMACAO_H

#ifndef FILTROIIR_H
#include "FiltroIIR.h"
#endif

// #define FATOR_DECIM 16

struct Decimador
{
    int cont_amostras = 0;
    int cont_decim = 0;
    bool flag;
    double amostra_decim;

};

void decimaSinal(IIR *iir, Decimador *decim, double amostra);
bool downsample(Decimador *decim, double amostra, int delay, const int FATOR_DECIM);

#endif