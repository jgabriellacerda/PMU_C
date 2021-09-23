#ifndef FILTROIIR_H
#define FILTROIIR_H

const double num_IIR[5] = {0.000024419565298361,   0.000097678261193446,   0.000146517391790169,   0.000097678261193446,   0.000024419565298361};
const double den_IIR[5] = {1.000000000000000,  -3.615352702016196,   4.918315719139102,  -2.982871345869219,   0.680299041791087};

const int size_num_IIR = 5;
const int size_den_IIR = 4;

struct IIR 
{
    double buff_nIIR[size_num_IIR];
    double buff_dIIR[size_den_IIR];

    int k0_n;
    int k0_d;

    double out_IIR_anterior;
    double out_IIR;
};

//double out_nIIR = 0;
//double out_dIIR = 0;


void CalcularIIR(IIR *iir, double amostra);

#endif