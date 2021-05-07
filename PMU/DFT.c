#ifndef DFT_C
#define DFT_C

#ifndef DFT_H
#include "DFT.h"
#endif

//double DFT_Gain = 0.042121698635337;
double DFT_Gain = 0.0481717187128816;
double W[N+1];
double TabSeno[NPPC];
double TabCosseno[NPPC];

void init_DFT()
{
	double T = 1/(float)FS_D;
	for(int i = 0; i < NPPC; i++)
	{
		TabCosseno[i] = cos(i*W0*T);
		TabSeno[i] = sin(i*W0*T);
	}

	//oFS_Dtream myfile8("W.txt");
	//oFS_Dtream myfile9("hamming.txt");

	double hamming[N+1];
	double Fr = 8.19;
	double soma_W = 0;

	for(int k = 0; k < N+1; k++)
	{
		hamming[k] = 0.54 - 0.46*cos((2*pi/(float)N)*k);
		if(k == N/2)
		{
				W[k] = 1;
		}
		else
		{		
			W[k] = ((sin(2*pi*(2*Fr/(float)FS_D)*(k-N/2)))/(float)(2*pi*(2*Fr/(float)FS_D)*(k-N/2)))*hamming[k];
		}
		//myfile8 << W[k] << endl;
		//myfile9 << hamming[k] << endl;
		soma_W += W[k];
	}

	DFT_Gain = sqrt(2)/soma_W;

	//myfile8.close();
	//myfile9.close();
}

void CalcularDFT(DFT *dft, double amostra){

	//DFT *dft = &fasor->dft;
	int k = dft->k0;

	/*static float re, im;
	static float bufS[N+1], bufC[N+1];
	static long ii = 0;
	static int jj = 0, k = 0;
	*/

	dft->bufC[k] = amostra * TabCosseno[dft->ii%NPPC];
	dft->bufS[k] = amostra * TabSeno[dft->ii%NPPC];
	dft->ii++;
	dft->re = 0;
	dft->im = 0;

	for(int jj = 0; jj < N+1; jj++){
		dft->re += dft->bufC[k] * W[jj];
		dft->im += dft->bufS[k] * W[jj];

		k--;
		if(k < 0){
			k += (N+1);
		}
	}

	dft->k0++;
	if(dft->k0 > N){
		dft->k0 -= (N+1);
	}

	dft->re = dft->re*DFT_Gain;
	dft->im = -dft->im*DFT_Gain;
}

#endif