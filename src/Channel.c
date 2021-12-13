#include "Channel.h"
#include <stdio.h>

Channel* newChannel(int fs, bool symmetric)
{
    Channel* channel = (Channel*)calloc(1, sizeof(Channel));

    double num[5] = {0.000024419565298361,   0.000097678261193446,   0.000146517391790169,   0.000097678261193446,   0.000024419565298361};
    double den[5] = {1.000000000000000,  -3.615352702016196,   4.918315719139102,  -2.982871345869219,   0.680299041791087};
    channel->iir = new_iir(num, den, 5, 5);

    channel->decim_sinal = newDecimator();
    channel->decim_fase = newDecimator();
    channel->decim_mag = newDecimator();
    channel->decim_freq = newDecimator();
    channel->decim_rocof = newDecimator();

    channel->fasor = new_fasor(960, symmetric);
    channel->processSample = processSample;
    channel->decimateParameters = decimateParameters;
    channel->nppc = (int)960/60.0;
    channel->fs = fs;

    return channel;
}

static void processSample(Channel* self, double sample)
{
    Fasor* fasor = self->fasor;

    sample = self->decim_sinal->decimateSignal(self->iir, self->decim_sinal, sample);
    
    if(self->decim_sinal->flag)
    {
        estimaFasor(fasor, sample, self->decim_sinal->flag);
        fasor->frequencia = estimaFrequencia(&fasor->est_freq, self->decim_sinal->flag, fasor->fase, fasor->frequencia);
        fasor->freq_mm = calculaMMFracionario(&fasor->est_freq.fmmf, fasor->frequencia, fasor->frequencia, self->fs);
        self->rocof = estimaROCOF(&fasor->est_freq, fasor->freq_mm);

        decimateParameters(self);
        updateReport(self);
    }
    else
    {
        self->reportar = false;
    }
}

static void decimateParameters(Channel* self)
{
    Fasor* fasor = self->fasor;

    // Correção devido ao desvio de fase causado pelo filtro IIR
    double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    corr = corr_a * (-fasor->frequencia) + corr_b;

    fasor->fase_corr = fasor->fase - corr;
    // fasor->fase_corr = fasor->fase;

    fasor->fase_mm = calculaMediaMovel(&fasor->fmm_fase, fasor->fase_corr, self->nppc+1, true);
    fasor->mag_mm = calculaMediaMovel(&fasor->fmm_mag, fasor->magnitude, self->nppc+1, false);
    self->rocof_mm = calculaMediaMovel(&self->fmm_rocof, self->rocof, self->nppc+1, false);

    self->decim_fase->downsample(self->decim_fase, fasor->fase_mm, 2+8, self->nppc);
    if(self->decim_fase->flag)
    {
        self->fase_pronto = true;
        self->fase_rep = self->decim_fase->decim_sample;
    }

    self->decim_mag->downsample(self->decim_mag, fasor->mag_mm, 2+8, self->nppc);
    if(self->decim_mag->flag)
    {
        self->mag_pronto = true;
        self->mag_rep = self->decim_mag->decim_sample;
    }

    self->decim_freq->downsample(self->decim_freq, fasor->freq_mm, 3, self->nppc);
    if(self->decim_freq->flag)
    {
        self->freq_pronto = true;
        self->freq_rep = self->decim_freq->decim_sample;
    }

    self->decim_rocof->downsample(self->decim_rocof, self->rocof, 3+8, self->nppc);
    if(self->decim_rocof->flag)
    {
        self->rocof_pronto = true;
        self->rocof_rep = self->decim_rocof->decim_sample;
    }

}

static void updateReport(Channel* self)
{
    if(self->fase_pronto && self->mag_pronto && self->freq_pronto && self->rocof_pronto)
    {        
        self->frame_num = (self->decim_fase->cnt_decim - 6) % 60;
        self->second = (self->decim_fase->cnt_decim - 6) / 60;
        self->timestamp = self->frame_num + self->second*60;

        self->fase_pronto = false;
        self->mag_pronto = false;
        self->freq_pronto = false;
        self->rocof_pronto = false;

        if(self->frame_num >= 0)
        {
            self->reportar = true;
        }
    }
    else
    {
        self->reportar = false;
    }
}