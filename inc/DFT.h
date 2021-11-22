#ifndef DFT_H
#define DFT_H

#include "../parameters.h"
#include <math.h>

const float pi = 3.14159265359;

struct DFT
{
	float re = 0, im = 0;
	float* bufS;
	float* bufC;
	long ii = 0;
	int k0 = 0;
	int N;
	int nppc;
	int len;
	bool odd;
};

DFT* new_dft(int fs);

static void init_DFT(int fs);

void calculaDFT(DFT *dft, float amostra);

void symmetricDFT(DFT *self, float amostra);

#endif