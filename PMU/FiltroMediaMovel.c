#ifndef FMM_C
#define FMM_C

#include "FiltroMediaMovel.h"


double calculaMediaMovel(FMM *fmm, double amostra, int N, bool unwrap)
{
    static const double pi = 3.141592653589793;
    static const double dois_pi = 6.283185307179586;
    double diff = 0;
    double soma = 0;
    int k = 0;
    int k0 = 0;
    int k1 = 0;

    if (N < 1 || N > N_MM_MAX)
    {
        return 0;
    }

    if(unwrap)
    {
        k0 = fmm->k0;
        k1 = (fmm->k0 + 1) % N_MM_MAX;

        fmm->buffMM[k1] = amostra;

        fmm->buff_unwrap[k1] = amostra;

        diff = fmm->buffMM[k1] - fmm->buffMM[k0];
        if (diff > pi*3/4)
        {
            fmm->cont_unwrap = 0;
            fmm->offset -= dois_pi;
        }
        else if (diff < -pi*3/4)
        {
            fmm->cont_unwrap = 0;
            fmm->offset += dois_pi;
        }
        else
        {
            fmm->cont_unwrap++; 
        }

        fmm->buff_unwrap[k1] = amostra + fmm->offset;
        
        if (fmm->cont_unwrap > 17)
        {
            fmm->offset = 0;
            for(int i = 0; i < N_MM_MAX; i++)
            {
                fmm->buff_unwrap[i] = fmm->buffMM[i];
            }
        }

        fmm->k0 = k1;

        soma = 0;
        for(int i = 0; i < N; i++ )
        {
            k = fmm->k0 - i;
            if(k < 0)
            {
                k += N_MM_MAX;
            }
            soma += fmm->buff_unwrap[k];
        }
        fmm->y1 = soma / N;

        if(fmm->y1 > pi)
        {
            fmm->y1 -= dois_pi;
        }
        else if(fmm->y1 < -pi)
        {
            fmm->y1 += dois_pi;
        }
    }
    else
    {
        fmm->pos_sub = fmm->k0 - N + 1;
        if(fmm->pos_sub < 0)
        {
            fmm->pos_sub += N_MM_MAX;
        }

        fmm->y1 = fmm->y0 + (amostra - fmm->buffMM[fmm->pos_sub]) / N;
        fmm->k0 = (fmm->k0 + 1) % N_MM_MAX;
        fmm->buffMM[fmm->k0] = amostra;
        fmm->y0 = fmm->y1;
    }

    return fmm->y1;
}


#endif