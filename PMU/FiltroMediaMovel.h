#ifndef FMM_H
#define FMM_H

#include "FiltroMediaMovel.h"

#define N_MM_MAX 17

struct FMM
{
    int k0 = 0;
    int pos_sub = 1;
    double buffMM[N_MM_MAX];
    double y1 = 0;
    double y0 = 0;
};

double calculaMediaMovel(FMM *fmm, double amostra, int N, bool unwrap);

#endif