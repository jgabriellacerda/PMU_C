#ifndef FASOR_C
#define FASOR_C

#ifndef FASOR_H
#include "Fasor.h"
#endif

void estimaFasor(Fasor *fasor, double amostra)
{
    //double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    if(fasor->decim_sinal.flag)
    {
        CalcularDFT(&fasor->dft, fasor->decim_sinal.amostra_decim);
        
        fasor->fase = atan2f(fasor->dft.im,fasor->dft.re);// *180.00/pi;// + correcao*canal;
        fasor->magnitude = sqrtf(fasor->dft.re*fasor->dft.re + fasor->dft.im*fasor->dft.im);


        //corr = corr_a * (-fasor->frequencia) + corr_b;
        //fasor->fase = fasor->fase - corr;
    }
}

void preparaReporte(Fasor *fasor)
{
    double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    corr = corr_a * (-fasor->frequencia) + corr_b;

    fasor->fase_corr = fasor->fase - corr;

    fasor->fase_mm = calculaMediaMovel(&fasor->fmm_fase, fasor->fase_corr, 17, true);
    fasor->mag_mm = calculaMediaMovel(&fasor->fmm_mag, fasor->magnitude, 17, false);

    downsample(&fasor->decim_fase, fasor->fase_mm, 2+8);
    downsample(&fasor->decim_mag, fasor->mag_mm, 2+8);

    if(fasor->decim_fase.flag)
    {
        fasor->fase_rep = fasor->decim_fase.amostra_decim;
        fasor->mag_rep = fasor->decim_mag.amostra_decim;
        
        fasor->frame_num = (fasor->decim_fase.cont_decim - 6) % 60;
        fasor->second = (fasor->decim_fase.cont_decim - 6) / 60;
        fasor->timestamp = fasor->frame_num + fasor->second*60;
        if(fasor->frame_num >= 0)
        {
            fasor->reportar = true;
        }
    }
    else{
        fasor->reportar = false;
    }
}

#endif