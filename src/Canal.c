#include "Canal.h"

void processaAmostra(Canal* canal, double amostra)
{
    Fasor* fasor = &canal->fasor; 

    decimaSinal(&fasor->iir, &fasor->decim_sinal, amostra);
    
    if(fasor->decim_sinal.flag)
    {
        estimaFasor(fasor, amostra);
        fasor->frequencia = EstimarFrequencia(&fasor->est_freq, fasor->decim_sinal.flag, fasor->fase, fasor->frequencia);
        fasor->freq_mm = calculaMMFracionario(&fasor->est_freq.fmmf, fasor->frequencia, fasor->frequencia, FS);
        canal->rocof = estimaROCOF(&fasor->est_freq, fasor->freq_mm);

        preparaReporte(canal);
    }
    else
    {
        canal->reportar = false;
    }
}

void preparaReporte(Canal* canal)
{
    Fasor* fasor = &canal->fasor;

    double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    corr = corr_a * (-fasor->frequencia) + corr_b;

    fasor->fase_corr = fasor->fase - corr;

    fasor->fase_mm = calculaMediaMovel(&fasor->fmm_fase, fasor->fase_corr, 17, true);
    fasor->mag_mm = calculaMediaMovel(&fasor->fmm_mag, fasor->magnitude, 17, false);

    if(downsample(&fasor->decim_fase, fasor->fase_mm, 2+8, 16))
    {
        canal->fase_pronto = true;
    }
    if(downsample(&fasor->decim_mag, fasor->mag_mm, 2+8, 16))
    {
        canal->mag_pronto = true;
    }
    if(downsample(&fasor->decim_freq, fasor->freq_mm, 3, 16))
    {
        canal->freq_pronto = true;
        fasor->freq_rep = fasor->freq_mm;
    }
    

    if(canal->fase_pronto == true && canal->mag_pronto == true && canal->freq_pronto == true)
    {
        fasor->fase_rep = fasor->decim_fase.amostra_decim;
        fasor->mag_rep = fasor->decim_mag.amostra_decim;
        
        canal->frame_num = (fasor->decim_fase.cont_decim - 6) % 60;
        canal->second = (fasor->decim_fase.cont_decim - 6) / 60;
        canal->timestamp = canal->frame_num + canal->second*60;

        canal->fase_pronto = false;
        canal->mag_pronto = false;
        canal->freq_pronto = false;

        if(canal->frame_num >= 0)
        {
            canal->reportar = true;
        }
    }
    else
    {
        canal->reportar = false;
    }
}