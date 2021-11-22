#include "Fasor.h"

Fasor* new_fasor(int fs)
{
    Fasor* fasor = (Fasor*)calloc(1, sizeof(Fasor));
    fasor->dft = new_dft(fs);

    return fasor;
}

void estimaFasor(Fasor *fasor, double amostra, bool flag)
{
    //double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    if(flag)
    {
        // calculaDFT(fasor->dft, amostra);
        symmetricDFT(fasor->dft, (float)amostra);
        
        fasor->fase = atan2f(fasor->dft->im,fasor->dft->re);// *180.00/pi;
        fasor->magnitude = sqrtf(fasor->dft->re*fasor->dft->re + fasor->dft->im*fasor->dft->im);


        //corr = corr_a * (-fasor->frequencia) + corr_b;
        //fasor->fase = fasor->fase - corr;
    }
}