#ifndef DFT_H
#define DFT_H

//#include "../parameters.h"
#include <math.h>

const int N = (int)(NPPC*10.25);

const double pi = 3.14159265359;
extern double DFT_Gain;

extern double W[N+1];
extern double TabSeno[NPPC];
extern double TabCosseno[NPPC];

//float Magnitude[3];
//static float Fase[3] = {0,0,0};

struct DFT
{
	double re = 0, im = 0;
	double bufS[N+1], bufC[N+1];
	long ii = 0;
	int k0 = 0;
};

//static float correcao = -2.209696979232202;
//static float correcao = 0;

//static unsigned int dt_atan2f, dt_filter;

void init_DFT();

void CalcularDFT(DFT *dft, double amostra);

#endif