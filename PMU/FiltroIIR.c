#ifndef FILTROIIR_C
#define FILTROIIR_C

#ifndef FILTROIIR_H
#include "FiltroIIR.h"
#endif

void CalcularIIR(IIR *iir, double amostra)
{
    double out_nIIR, out_dIIR;

    // Numerador
    iir->buff_nIIR[iir->k0_n] = amostra;
    out_nIIR = 0; 
    for(int jj = 0; jj < size_num_IIR; jj++)
    {

        out_nIIR += iir->buff_nIIR[iir->k0_n]*num_IIR[jj];
        iir->k0_n--;
        if (iir->k0_n < 0) 
        {
            iir->k0_n = iir->k0_n + size_num_IIR; 
        }
    }
    iir->k0_n++;
    if (iir->k0_n > size_num_IIR-1)
    {
        iir->k0_n -= size_num_IIR; 
    }

    // Denominador
    iir->buff_dIIR[iir->k0_d] = iir->out_IIR_anterior; 
    out_dIIR = 0; 
    for(int jj = 0; jj < size_den_IIR; jj++)
    {

        out_dIIR += iir->buff_dIIR[iir->k0_d]*den_IIR[jj+1];
        iir->k0_d--;
        if (iir->k0_d < 0) 
        {
            iir->k0_d += size_den_IIR; 
        }
    }
    iir->k0_d++;
    if (iir->k0_d > size_den_IIR-1) 
    {
        iir->k0_d -= size_den_IIR; 
    }

    iir->out_IIR = (out_nIIR - out_dIIR)/den_IIR[0];
    iir->out_IIR_anterior = iir->out_IIR;

    //return iir->out_IIR;
}

#endif