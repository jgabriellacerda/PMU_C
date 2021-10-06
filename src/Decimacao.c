#include "Decimacao.h"

void decimaSinal(IIR *iir, Decimador *decim, double amostra)
{
    //IIR *iir = &fasor->iir;
    //Decimador *decim = &fasor->decim;

    CalcularIIR(iir, amostra);

    downsample(decim, iir->out_IIR, 0, 16);

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

bool downsample(Decimador *decim, double amostra, int delay, const int FATOR_DECIM)
{
    decim->cont_amostras = decim->cont_amostras % FATOR_DECIM;

    if(decim->cont_amostras == delay)
    {
        decim->flag = true;
        decim->amostra_decim = amostra;
        decim->cont_decim++;
        decim->cont_amostras++;
        return true;
    }
    else
    {
        decim->cont_amostras++;
        decim->flag = false;
        return false;
    }
    
}