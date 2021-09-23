#include "FiltroSG.h"

void CalcularSG(SG *sg, double fase)
{
    //SG *sg = &fasor->sg1;

    sg->buffSG[sg->k0] = fase;

    sg->outSG = 0;

    for (int k=0; k < N_SG; k++)
    {
        sg->outSG += sg->buffSG[sg->k0]*SG_coef[k];
        sg->k0--;
        if (sg->k0 < 0) 
        { 
            sg->k0 += N_SG;
        }
    }

    sg->outSG *= SG_GAIN;//sa�da deriva��o (f_samp/(2*pi))

    sg->k0++;
    if (sg->k0 >= N_SG)
    { 
        sg->k0 -= N_SG;
    }
}

void AtualizarBufferSG(SG *sg, double fase)
{
    sg->buffSG[sg->k0] = fase;

    sg->outSG = 0;

    sg->k0++;
    if (sg->k0 >= N_SG)
    { 
        sg->k0 -= N_SG;
    }
}