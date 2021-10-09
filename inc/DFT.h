#ifndef DFT_H
#define DFT_H

#include "../parameters.h"
#include <math.h>

const double pi = 3.14159265359;

struct DFT
{
	double re = 0, im = 0;
	double* bufS;
	double* bufC;
	long ii = 0;
	int k0 = 0;
	int N;
	int nppc;
};

DFT* new_dft(int fs);

static void init_DFT(int fs);

void calculaDFT(DFT *dft, double amostra);

#endif