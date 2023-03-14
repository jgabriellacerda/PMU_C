#include "Decimation.h"
#include <stdio.h>
#include <stdlib.h>

Decimator *newDecimator()
{
    Decimator *decim = (Decimator *)malloc(sizeof(Decimator));

    decim->cnt_samples = 0;
    decim->cnt_decim = 0;

    decim->decimateSignal = decimateSignal;
    decim->downsample = downsample;
    return decim;
}

static double decimateSignal(IIR *iir, Decimator *self, double sample)
{
    iir->calculaIIR(iir, (float)sample);
    sample = downsample(self, iir->out_IIR, 0, 16);
    return sample;
}

static double downsample(Decimator *self, double sample, int delay, const int DECIM_FACTOR)
{
    self->cnt_samples = self->cnt_samples % DECIM_FACTOR;

    if (self->cnt_samples == delay)
    {
        self->flag = true;
        self->decim_sample = sample;
        self->cnt_decim++;
        self->cnt_samples++;
        return sample;
    }
    else
    {
        self->cnt_samples++;
        self->flag = false;
        return 0;
    }
}