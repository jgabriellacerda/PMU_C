#ifndef FREQUENCIA_H
#define FREQUENCIA_H

#ifndef FILTROSG_H
#include "FiltroSG.h"
#endif

#include "FiltroMediaMovel.h"

#define SG1 1
#define SG2 2

#define NORMAL 0
#define TRANS_SG1 1
#define TRANS_SG2 2

struct FreqMux
{
    float fase_ant = 0; // fase estimada anterior 
    int salto_fase = 0;
    double offset_SG1 = 0;
    double offset_SG2 = 0;
    int SG_out = SG1;
    int estado = NORMAL;
    int cnt = 0;
};

struct EstimacaoFrequencia
{
    SG sg1;
    SG sg2;
    FreqMux freqmux;
    FMMFracionario fmmf;
};

double EstimarFrequencia(EstimacaoFrequencia *est_freq, bool estimar, double fase, double frequencia);
void DetectarSalto(FreqMux *freqmux, float fase);
void AtualizarEstado(FreqMux *freqmux);
void AtualizarUnwrapFase(FreqMux *freqmux);

#endif