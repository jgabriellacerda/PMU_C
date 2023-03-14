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
    Decimator *signal_decimation;
    Decimator *phase_decimator;
    Decimator *mag_decimator;
    Decimator *freq_decimator;
    Decimator *rocof_decimator;

    double fase_rep;
    double mag_rep;
    double freq_rep;
    bool freq_pronto;
    bool fase_pronto;
    bool mag_pronto;
    bool rocof_pronto;
    int timestamp;
    int frame_num;
    int second;
    bool reportar;
    double rocof;
    double rocof_mm;
    double rocof_rep;
    FMM fmm_rocof;

    int fs;
    int nppc;

    void (*processSample)(Channel *canal, double amostra);
    void (*decimateParameters)(Channel *channel);
};
typedef Channel Channel;

Channel *newChannel(int fs, bool symmetric);

static void processSample(Channel *canal, double amostra);
static void decimateParameters(Channel *channel);
static void updateReport(Channel *canal);

#endif