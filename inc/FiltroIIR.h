#ifndef FILTROIIR_H
#define FILTROIIR_H

#include <stdlib.h>

struct IIR
{
    double *num_IIR;
    double *den_IIR;

    int size_num;
    int size_den;

    double *buff_nIIR;
    double *buff_dIIR;

    int k0_n;
    int k0_d;

    double out_IIR_anterior;
    double out_IIR;

    void (*calculaIIR)(IIR *iir, double amostra);
};
typedef IIR IIR;

IIR *new_iir(double num[], double den[], int size_num, int size_den);

static void calculaIIR(IIR *iir, double amostra);

#endif