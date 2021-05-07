#ifndef PMU
#define PMU

#ifndef PI
    #define PI 3.14159265358979323846
#endif

#ifndef NPPC
    #define NPPC 16
#endif

#ifndef W0
    #define W0 (2*PI*60)
#endif

#ifndef FS_D
    #define FS_D (NPPC*60)
#endif

/*
#ifndef FASOR_H
#include "Fasor.h"
#endif
#ifndef DFT_H
#include "DFT.h"
#endif
#ifndef FREQUENCIA_H
#include "EstimacaoFrequencia/Frequencia.h"
#endif
#ifndef FILTROSG_H
#include "EstimacaoFrequencia/FiltroSG.h"
#endif
#ifndef FILTROIIR_H
#include "FiltroIIR.h"
#endif
#ifndef DECIMACAO_H
#include "Decimacao.h"
#endif

g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/DFT.c -o DFT.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU/EstimacaoFrequencia -c ./PMU/EstimacaoFrequencia/FiltroSG.c -o FiltroSG.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU/EstimacaoFrequencia -c ./PMU/EstimacaoFrequencia/Frequencia.c -o Frequencia.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/FiltroIIR.c -o FiltroIIR.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/Decimacao.c -o Decimacao.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I ./PMU -c ./PMU/Fasor.c -o Fasor.o

Fasor.o DFT.o FiltroSG.o Frequencia.o FiltroIIR.o Decimacao.o

*/


#include "Fasor.c"
#include "DFT.c"
#include "FiltroSG.c"
#include "Frequencia.c"
#include "FiltroIIR.c"
#include "Decimacao.c"
#include "FiltroMediaMovel.c"


#endif