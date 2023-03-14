#ifndef DFT_H
#define DFT_H

#include "../parameters.h"
#include <math.h>
#include <stdbool.h>

const float pi = 3.14159265359;

struct DFT
{
	float re;
	float im;
	float *bufS;
	float *bufC;
	long ii;
	int k0;
	int N;
	int nppc;
	int len;
	bool odd;
};
typedef DFT DFT;

DFT *new_dft(int fs);

static void init_DFT(int fs);

void calculaDFT(DFT *dft, float amostra);

void symmetricDFT(DFT *self, float amostra);

#endif