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

struct Canal
{
    Fasor fasor;
    bool freq_pronto = false, fase_pronto = false, mag_pronto = false;
    int timestamp = 0;
    int frame_num = 0;
    int second = 0;
    bool reportar = false;
    double rocof;
};

void processaAmostra(Canal* canal, double amostra);
void preparaReporte(Canal *canal);

#endif