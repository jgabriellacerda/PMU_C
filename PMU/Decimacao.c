#ifndef DECIMACAO_C
#define DECIMACAO_C

#ifndef DECIMACAO_H
#include "Decimacao.h"
#endif

void decimaSinal(IIR *iir, Decimador *decim, double amostra)
{
    //IIR *iir = &fasor->iir;
    //Decimador *decim = &fasor->decim;

    CalcularIIR(iir, amostra);

    downsample(decim, iir->out_IIR, 0);

    // decim->cont_amostras = decim->cont_amostras % FATOR_DECIM;

    // if(decim->cont_amostras == 0)
    // {
    //     decim->estimar = true;
    //     decim->amostra_decim = iir->out_IIR;
    // }
    // else
    // {
    //     decim->estimar = false;
    // }
    // decim->cont_amostras++;
    
}

void downsample(Decimador *decim, double amostra, int delay)
{
    decim->cont_amostras = decim->cont_amostras % FATOR_DECIM;

    if(decim->cont_amostras == delay)
    {
        decim->flag = true;
        decim->amostra_decim = amostra;
        decim->cont_decim++;
    }
    else
    {
        decim->flag = false;
    }
    decim->cont_amostras++;
}


#endif