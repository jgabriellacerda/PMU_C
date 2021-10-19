#ifndef PMU
#define PMU

/*

g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/DFT.c -o DFT.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU/EstimacaoFrequencia -c ./PMU/EstimacaoFrequencia/FiltroSG.c -o FiltroSG.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU/EstimacaoFrequencia -c ./PMU/EstimacaoFrequencia/Frequencia.c -o Frequencia.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/FiltroIIR.c -o FiltroIIR.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/Decimacao.c -o Decimacao.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/Fasor.c -o Fasor.o

Fasor.o DFT.o FiltroSG.o Frequencia.o FiltroIIR.o Decimacao.o

*/

#include "Fasor.h"
#include "FiltroIIR.h"
#include "Decimation.h"

struct Channel
{
    Fasor* fasor;

    IIR* iir;
    Decimator* decim_sinal;
    Decimator* decim_fase;
    Decimator* decim_mag;
    Decimator* decim_freq;
    Decimator* decim_rocof;

    double fase_rep, mag_rep, freq_rep;
    bool freq_pronto = false, fase_pronto = false, mag_pronto = false, rocof_pronto = false;
    int timestamp = 0;
    int frame_num = 0;
    int second = 0;
    bool reportar = false;
    double rocof, rocof_mm, rocof_rep;
    FMM fmm_rocof;

    int fs, nppc;

    void (*processSample)(Channel* canal, double amostra);
    void (*decimateParameters)(Channel* channel);
};

Channel* newChannel(int fs);

static void processSample(Channel* canal, double amostra);
static void decimateParameters(Channel* channel);
static void updateReport(Channel *canal);

#endif