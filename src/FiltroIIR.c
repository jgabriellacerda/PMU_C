#include "FiltroIIR.h"
#include <stdio.h>

IIR* new_iir(double num[], double den[], int size_num, int size_den)
{   
    IIR* iir = (IIR*)calloc(1, sizeof(IIR));

    iir->size_num = size_num;
    iir->size_den = size_den-1;

    iir->num_IIR = (double*)calloc(size_num, sizeof(double));
    iir->den_IIR = (double*)calloc(size_den, sizeof(double));

    iir->buff_nIIR = (double*)calloc(size_num, sizeof(double));
    iir->buff_dIIR = (double*)calloc(size_den-1, sizeof(double));

    for(int i = 0; i < size_num; i++)
    {
        // printf("%.12lf, ",num[i]);
        iir->num_IIR[i] = num[i];
    }
    for(int i = 0; i < size_den; i++)
    {
        // printf("%.12lf, ",den[i]);
        iir->den_IIR[i] = den[i];
    }

    iir->calculaIIR = calculaIIR;

    return iir;
}

static void calculaIIR(IIR* self, double amostra)
{
    double out_nIIR, out_dIIR;

    // Numerador
    self->buff_nIIR[self->k0_n] = amostra;
    out_nIIR = 0; 
    for(int jj = 0; jj < self->size_num; jj++)
    {

        out_nIIR += self->buff_nIIR[self->k0_n] * self->num_IIR[jj];
        self->k0_n = (self->k0_n == 0) ? self->size_num-1 : self->k0_n - 1;
    }
    self->k0_n = (self->k0_n == self->size_num-1) ? 0 : self->k0_n + 1;

    // Denominador
    self->buff_dIIR[self->k0_d] = self->out_IIR_anterior; 
    out_dIIR = 0; 
    for(int jj = 0; jj < self->size_den; jj++)
    {

        out_dIIR += self->buff_dIIR[self->k0_d] * self->den_IIR[jj+1];
        self->k0_d = (self->k0_d == 0) ? self->size_den-1 : self->k0_d - 1;
    }
    self->k0_d = (self->k0_d == self->size_den-1) ? 0 : self->k0_d + 1;

    self->out_IIR = (out_nIIR - out_dIIR)/self->den_IIR[0];
    self->out_IIR_anterior = self->out_IIR;
}