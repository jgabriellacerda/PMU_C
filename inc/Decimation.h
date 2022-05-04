#ifndef DECIMACAO_H
#define DECIMACAO_H

#ifndef FILTROIIR_H
#include "FiltroIIR.h"
#endif

struct Decimator
{
    int cnt_samples = 0;
    int cnt_decim = 0;
    bool flag;
    double decim_sample;

    double (*decimateSignal)(IIR *iir, Decimator *decim, double sample);
    double (*downsample)(Decimator *decim, double sample, int delay, const int DECIM_FACTOR);
};
typedef struct Decimator Decimator;


Decimator* newDecimator();

static double decimateSignal(IIR *iir, Decimator *decim, double sample);
static double downsample(Decimator *decim, double sample, int delay, const int DECIM_FACTOR);

#endif