#ifndef FREQUENCIA_C
#define FREQUENCIA_C

#ifndef FREQUENCIA_H
#include "Frequencia.h"
#endif

double EstimarFrequencia(EstimacaoFrequencia *est_freq, bool estimar, double fase, double frequencia)
{
    //EstimacaoFrequencia *est_freq = &fasor->est_freq;
    FreqMux *freqmux = &est_freq->freqmux;

    if(estimar)
    {
        DetectarSalto(freqmux, fase);
        AtualizarEstado(freqmux);
        AtualizarUnwrapFase(freqmux);

        if(freqmux->SG_out == SG1)
        {
            CalcularSG(&est_freq->sg1, fase + freqmux->offset_SG1);
            AtualizarBufferSG(&est_freq->sg2, fase + freqmux->offset_SG2);
            frequencia = est_freq->sg1.outSG;
        }
        else if(freqmux->SG_out == SG2)
        {
            CalcularSG(&est_freq->sg2, fase + freqmux->offset_SG2);
            AtualizarBufferSG(&est_freq->sg1, fase + freqmux->offset_SG1);
            frequencia = est_freq->sg2.outSG;
        }
    }
    return frequencia;
}

void DetectarSalto(FreqMux *freqmux, float fase)
{
    if(fase - freqmux->fase_ant < -6)
    {
        freqmux->salto_fase = -1;
    }
    else if(fase - freqmux->fase_ant > 6)
    {
        freqmux->salto_fase = 1;
    }
    else
    {
        freqmux->salto_fase = 0;
    }
    freqmux->fase_ant = fase;
}

void AtualizarEstado(FreqMux *freqmux)
{
    // Controle de estado
    switch(freqmux->estado)
    {
        case NORMAL:
            if(freqmux->salto_fase)
            {
                freqmux->estado = TRANS_SG1;
                freqmux->cnt = 0;
            }
            break;

        case TRANS_SG1:
            if(freqmux->salto_fase != 0)
            {
                freqmux->cnt = 0;
            }
            else
            {
                freqmux->cnt += 1;
            }
            if(freqmux->cnt == N_SG)
            {
                if(freqmux->offset_SG2 != 0)
                {
                    freqmux->estado = TRANS_SG2;
                    freqmux->cnt = 0;
                }
                else
                {
                    freqmux->estado = NORMAL;
                }
            }
            break;

        case TRANS_SG2:
            if(freqmux->salto_fase)
            {
                freqmux->cnt = 0;
            }
            else
            {
                freqmux->cnt += 1;
            }
            if(freqmux->cnt == N_SG)
            {
                if(freqmux->offset_SG1 != 0)
                {
                    freqmux->estado = TRANS_SG1;
                    freqmux->cnt = 0;
                }
                else
                {
                    freqmux->estado = NORMAL;
                }
            }
            break;
    }
}

void AtualizarUnwrapFase(FreqMux *freqmux)
{
    switch(freqmux->estado)
    {
        case NORMAL:
            freqmux->SG_out = SG1;
            freqmux->offset_SG1 = 0;   
            freqmux->offset_SG2 = 0;

        case TRANS_SG1:
            freqmux->SG_out = SG2;
            freqmux->offset_SG1 = 0;      
            freqmux->offset_SG2 -= 2*PI*freqmux->salto_fase;
            break;
            
        case TRANS_SG2:
            freqmux->SG_out = SG1;
            freqmux->offset_SG1 -= 2*PI*freqmux->salto_fase;
            freqmux->offset_SG2 = 0;
            break;
    }
}



#endif