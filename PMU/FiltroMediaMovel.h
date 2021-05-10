#ifndef FMM_H
#define FMM_H

#include "FiltroMediaMovel.h"

#define N_MM_MAX 17

struct FMM
{
    int k0 = 0;
    int pos_sub = 1;
    int cont_unwrap = 0;
    double offset = 0;
    double buffMM[N_MM_MAX] = {0};
    double buff_unwrap[N_MM_MAX] = {0};
    double y1 = 0;
    double y0 = 0;
};

double calculaMediaMovel(FMM *fmm, double amostra, int N, bool unwrap);

#endif