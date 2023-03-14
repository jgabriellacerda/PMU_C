#include "DFT.h"
#include <stdio.h>
#include <stdlib.h>

static float DFT_Gain = 0.0481717187128816;
static float *W;
// const float W[N+1] = {0.005389, 0.006245, 0.007115, 0.008006, 0.008921, 0.009861, 0.010820, 0.011787, 0.012746, 0.013677, 0.014551, 0.015336, 0.015996, 0.016487, 0.016764, 0.016778, 0.016480, 0.015818, 0.014742, 0.013204, 0.011160, 0.008572, 0.005407, 0.001643, -0.002736, -0.007730, -0.013329, -0.019509, -0.026230, -0.033438, -0.041063, -0.049016, -0.057194, -0.065478, -0.073733, -0.081810, -0.089547, -0.096769, -0.103292, -0.108926, -0.113474, -0.116736, -0.118513, -0.118609, -0.116834, -0.113007, -0.106959, -0.098537, -0.087605, -0.074050, -0.057782, -0.038736, -0.016877, 0.007800, 0.035268, 0.065470, 0.098311, 0.133665, 0.171374, 0.211244, 0.253052, 0.296544, 0.341439, 0.387429, 0.434185, 0.481361, 0.528591, 0.575500, 0.621707, 0.666825, 0.710471, 0.752265, 0.791838, 0.828839, 0.862931, 0.893803, 0.921170, 0.944778, 0.964404, 0.979866, 0.991016, 0.997749, 1.000000, 0.997749, 0.991016, 0.979866, 0.964404, 0.944778, 0.921170, 0.893803, 0.862931, 0.828839, 0.791838, 0.752265, 0.710471, 0.666825, 0.621707, 0.575500, 0.528591, 0.481361, 0.434185, 0.387429, 0.341439, 0.296544, 0.253052, 0.211244, 0.171374, 0.133665, 0.098311, 0.065470, 0.035268, 0.007800, -0.016877, -0.038736, -0.057782, -0.074050, -0.087605, -0.098537, -0.106959, -0.113007, -0.116834, -0.118609, -0.118513, -0.116736, -0.113474, -0.108926, -0.103292, -0.096769, -0.089547, -0.081810, -0.073733, -0.065478, -0.057194, -0.049016, -0.041063, -0.033438, -0.026230, -0.019509, -0.013329, -0.007730, -0.002736, 0.001643, 0.005407, 0.008572, 0.011160, 0.013204, 0.014742, 0.015818, 0.016480, 0.016778, 0.016764, 0.016487, 0.015996, 0.015336, 0.014551, 0.013677, 0.012746, 0.011787, 0.010820, 0.009861, 0.008921, 0.008006, 0.007115, 0.006245, 0.005389};
// #define W (const float []) {0.005389, 0.006245, 0.007115, 0.008006, 0.008921, 0.009861, 0.010820, 0.011787, 0.012746, 0.013677, 0.014551, 0.015336, 0.015996, 0.016487, 0.016764, 0.016778, 0.016480, 0.015818, 0.014742, 0.013204, 0.011160, 0.008572, 0.005407, 0.001643, -0.002736, -0.007730, -0.013329, -0.019509, -0.026230, -0.033438, -0.041063, -0.049016, -0.057194, -0.065478, -0.073733, -0.081810, -0.089547, -0.096769, -0.103292, -0.108926, -0.113474, -0.116736, -0.118513, -0.118609, -0.116834, -0.113007, -0.106959, -0.098537, -0.087605, -0.074050, -0.057782, -0.038736, -0.016877, 0.007800, 0.035268, 0.065470, 0.098311, 0.133665, 0.171374, 0.211244, 0.253052, 0.296544, 0.341439, 0.387429, 0.434185, 0.481361, 0.528591, 0.575500, 0.621707, 0.666825, 0.710471, 0.752265, 0.791838, 0.828839, 0.862931, 0.893803, 0.921170, 0.944778, 0.964404, 0.979866, 0.991016, 0.997749, 1.000000, 0.997749, 0.991016, 0.979866, 0.964404, 0.944778, 0.921170, 0.893803, 0.862931, 0.828839, 0.791838, 0.752265, 0.710471, 0.666825, 0.621707, 0.575500, 0.528591, 0.481361, 0.434185, 0.387429, 0.341439, 0.296544, 0.253052, 0.211244, 0.171374, 0.133665, 0.098311, 0.065470, 0.035268, 0.007800, -0.016877, -0.038736, -0.057782, -0.074050, -0.087605, -0.098537, -0.106959, -0.113007, -0.116834, -0.118609, -0.118513, -0.116736, -0.113474, -0.108926, -0.103292, -0.096769, -0.089547, -0.081810, -0.073733, -0.065478, -0.057194, -0.049016, -0.041063, -0.033438, -0.026230, -0.019509, -0.013329, -0.007730, -0.002736, 0.001643, 0.005407, 0.008572, 0.011160, 0.013204, 0.014742, 0.015818, 0.016480, 0.016778, 0.016764, 0.016487, 0.015996, 0.015336, 0.014551, 0.013677, 0.012746, 0.011787, 0.010820, 0.009861, 0.008921, 0.008006, 0.007115, 0.006245, 0.005389}
static float *TabSeno = NULL;
static float *TabCosseno;

// const int N = (int)(NPPC*10.25);

DFT *new_dft(int fs)
{
	int nppc = fs / 60;
	DFT *dft = (DFT *)calloc(1, sizeof(DFT));
	dft->N = (int)nppc * 10.25;
	dft->len = dft->N + 1;
	dft->odd = (dft->len % 2 == 1);
	// dft->N = (int)nppc*5;
	dft->nppc = nppc;
	dft->re = 0;
	dft->im = 0;
	dft->ii = 0;
	dft->k0 = 0;

	if (!TabSeno)
	{
		TabSeno = (float *)calloc(nppc, sizeof(float));
	}
	if (!TabCosseno)
	{
		TabCosseno = (float *)calloc(nppc, sizeof(float));
	}
	if (!W)
	{
		W = (float *)calloc(dft->len, sizeof(float));
	}

	dft->bufS = (float *)calloc(dft->len, sizeof(float));
	dft->bufC = (float *)calloc(dft->len, sizeof(float));

	init_DFT(fs);
	return dft;
}

static void init_DFT(int fs)
{
	float T = (float)(1.0 / fs);
	int nppc = (int)(fs / 60.0);
	int N = (int)(nppc * 10.25);

	for (int i = 0; i < nppc; i++)
	{
		TabCosseno[i] = cos(i * W0 * T);
		TabSeno[i] = sin(i * W0 * T);
	}

	float hamming[N + 1];
	float Fr = 8.19;
	float soma_W = 0;

	for (int n = 0; n < N + 1; n++)
	{
		hamming[n] = 0.54 - 0.46 * cos((2 * pi / (float)N) * n);
		if (n == N / 2)
		{
			W[n] = 1;
		}
		else
		{
			W[n] = ((sin(2 * pi * (2 * Fr / (float)fs) * (n - N / 2))) / (float)(2 * pi * (2 * Fr / (float)fs) * (n - N / 2))) * hamming[n];
		}
		soma_W += W[n];
	}

	DFT_Gain = sqrt(2) / soma_W;
}

void calculaDFT(DFT *self, float amostra)
{

	int n = self->k0;

	self->bufC[n] = amostra * TabCosseno[self->ii];
	self->bufS[n] = amostra * TabSeno[self->ii];
	self->ii = (self->ii == self->nppc - 1) ? 0 : (self->ii + 1);
	self->re = 0;
	self->im = 0;

	for (int k = 0; k < self->len; k++)
	{
		self->re += self->bufC[n] * W[k];
		self->im += self->bufS[n] * W[k];

		n = (n == 0) ? self->N : n - 1;
	}

	self->k0 = (self->k0 == self->N) ? 0 : self->k0 + 1;

	self->re = self->re * DFT_Gain;
	self->im = -self->im * DFT_Gain;
}

void symmetricDFT(DFT *self, float amostra)
{
	int n = self->k0;
	int n1 = n;
	int n2 = (n == self->N) ? 0 : (n + 1);

	self->bufC[n] = amostra * TabCosseno[self->ii];
	self->bufS[n] = amostra * TabSeno[self->ii];
	self->ii = (self->ii == self->nppc - 1) ? 0 : (self->ii + 1);
	self->re = 0;
	self->im = 0;

	for (int k = 0; k < (int)self->len / 2; k++)
	{
		self->re += (self->bufC[n1] + self->bufC[n2]) * W[k];
		self->im += (self->bufS[n1] + self->bufS[n2]) * W[k];

		n1 = (n1 == 0) ? self->N : (n1 - 1);
		n2 = (n2 == self->N) ? 0 : (n2 + 1);
	}

	if (self->odd)
	{
		int k = (int)self->len / 2 + 1;
		self->re += (self->bufC[n1]) * W[k];
		self->im += (self->bufS[n1]) * W[k];
	}

	self->k0 = (self->k0 == self->N) ? 0 : self->k0 + 1;

	self->re = self->re * DFT_Gain;
	self->im = -self->im * DFT_Gain;
}