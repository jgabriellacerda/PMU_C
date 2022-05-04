#include "Fasor.h"
#include <stdio.h>
#include <stdlib.h>

Fasor* new_fasor(int fs, bool symmetric)
{
    Fasor* fasor = (Fasor*)calloc(1, sizeof(Fasor));
    fasor->dft = new_dft(fs);
    fasor->symmetric = symmetric;
    return fasor;
}

void estimaFasor(Fasor *fasor, double amostra, bool flag)
{
    //double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    if(flag)
    {
        if(fasor->symmetric)
        {
            symmetricDFT(fasor->dft, (float)amostra);
        }
        else
        {
            calculaDFT(fasor->dft, amostra);
        }
        
        fasor->fase = atan2f(fasor->dft->im,fasor->dft->re);// *180.00/pi;
        fasor->magnitude = sqrtf(fasor->dft->re*fasor->dft->re + fasor->dft->im*fasor->dft->im);


        //corr = corr_a * (-fasor->frequencia) + corr_b;
        //fasor->fase = fasor->fase - corr;
    }
}