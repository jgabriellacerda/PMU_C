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
    Fasor *fasor;

    IIR *iir;
    Decimator *signal_decimator;
    Decimator *phase_decimator;
    Decimator *mag_decimator;
    Decimator *freq_decimator;
    Decimator *rocof_decimator;

    double fase_rep;
    double mag_rep;
    double freq_rep;
    bool freq_ready;
    bool phase_ready;
    bool mag_ready;
    bool rocof_ready;
    int timestamp;
    int frame_num;
    int second;
    bool report;
    double rocof;
    double rocof_mm;
    double rocof_rep;
    FMM fmm_rocof;

    int fs;
    int nppc;

    void (*processSample)(Channel *channel, double sample);
    void (*decimateParameters)(Channel *channel);
};
typedef Channel Channel;

Channel *newChannel(int fs, bool symmetric);

static void processSample(Channel *channel, double sample);
static void decimateParameters(Channel *channel);
static void updateReport(Channel *channel);

#endif