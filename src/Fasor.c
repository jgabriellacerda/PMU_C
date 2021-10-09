#include "Fasor.h"

Fasor* new_fasor(int fs)
{
    Fasor* fasor = (Fasor*)calloc(1, sizeof(Fasor));
    fasor->dft = new_dft(fs);
    return fasor;
}

void estimaFasor(Fasor *fasor, double amostra)
{
    //double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    if(fasor->decim_sinal.flag)
    {
        calculaDFT(fasor->dft, fasor->decim_sinal.amostra_decim);
        
        fasor->fase = atan2f(fasor->dft->im,fasor->dft->re);// *180.00/pi;// + correcao*canal;
        fasor->magnitude = sqrtf(fasor->dft->re*fasor->dft->re + fasor->dft->im*fasor->dft->im);


        //corr = corr_a * (-fasor->frequencia) + corr_b;
        //fasor->fase = fasor->fase - corr;
    }
}