#include "Channel.h"
#include <stdio.h>

Channel *newChannel(int fs, bool symmetric)
{
    Channel *channel = (Channel *)calloc(1, sizeof(Channel));

    double num[5] = {0.000024419565298361, 0.000097678261193446, 0.000146517391790169, 0.000097678261193446, 0.000024419565298361};
    double den[5] = {1.000000000000000, -3.615352702016196, 4.918315719139102, -2.982871345869219, 0.680299041791087};
    channel->iir = new_iir(num, den, 5, 5);

    channel->signal_decimator = newDecimator();
    channel->phase_decimator = newDecimator();
    channel->mag_decimator = newDecimator();
    channel->freq_decimator = newDecimator();
    channel->rocof_decimator = newDecimator();

    channel->freq_pronto = false;
    channel->fase_pronto = false;
    channel->mag_pronto = false;
    channel->rocof_pronto = false;
    channel->timestamp = 0;
    channel->frame_num = 0;
    channel->second = 0;
    channel->reportar = false;

    channel->fasor = new_fasor(960, symmetric);
    channel->processSample = processSample;
    channel->decimateParameters = decimateParameters;
    channel->nppc = (int)960 / 60.0;
    channel->fs = fs;

    return channel;
}
typedef Channel Channel;

static void processSample(Channel *self, double sample)
{
    Fasor *fasor = self->fasor;

    sample = self->signal_decimator->decimateSignal(self->iir, self->signal_decimator, sample);

    if (self->signal_decimator->flag)
    {
        estimaFasor(fasor, sample, self->signal_decimator->flag);
        fasor->frequencia = estimaFrequencia(&fasor->est_freq, self->signal_decimator->flag, fasor->fase, fasor->frequencia);
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

static void decimateParameters(Channel *self)
{
    Fasor *fasor = self->fasor;

    // Correção devido ao desvio de fase causado pelo filtro IIR
    double corr = 0, corr_a = -0.007332419963127, corr_b = -0.436483107452006;

    corr = corr_a * (-fasor->frequencia) + corr_b;

    fasor->fase_corr = fasor->fase - corr;
    // fasor->fase_corr = fasor->fase;

    fasor->fase_mm = calculaMediaMovel(&fasor->fmm_fase, fasor->fase_corr, self->nppc + 1, true);
    fasor->mag_mm = calculaMediaMovel(&fasor->fmm_mag, fasor->magnitude, self->nppc + 1, false);
    self->rocof_mm = calculaMediaMovel(&self->fmm_rocof, self->rocof, self->nppc + 1, false);

    self->phase_decimator->downsample(self->phase_decimator, fasor->fase_mm, 2 + 8, self->nppc);
    if (self->phase_decimator->flag)
    {
        self->fase_pronto = true;
        self->fase_rep = self->phase_decimator->decim_sample;
    }

    self->mag_decimator->downsample(self->mag_decimator, fasor->mag_mm, 2 + 8, self->nppc);
    if (self->mag_decimator->flag)
    {
        self->mag_pronto = true;
        self->mag_rep = self->mag_decimator->decim_sample;
    }

    self->freq_decimator->downsample(self->freq_decimator, fasor->freq_mm, 3, self->nppc);
    if (self->freq_decimator->flag)
    {
        self->freq_pronto = true;
        self->freq_rep = self->freq_decimator->decim_sample;
    }

    self->rocof_decimator->downsample(self->rocof_decimator, self->rocof, 3 + 8, self->nppc);
    if (self->rocof_decimator->flag)
    {
        self->rocof_pronto = true;
        self->rocof_rep = self->rocof_decimator->decim_sample;
    }
}

static void updateReport(Channel *self)
{
    if (self->fase_pronto && self->mag_pronto && self->freq_pronto && self->rocof_pronto)
    {
        self->frame_num = (self->phase_decimator->cnt_decim - 6) % 60;
        self->second = (self->phase_decimator->cnt_decim - 6) / 60;
        self->timestamp = self->frame_num + self->second * 60;

        self->fase_pronto = false;
        self->mag_pronto = false;
        self->freq_pronto = false;
        self->rocof_pronto = false;

        if (self->frame_num >= 0)
        {
            self->reportar = true;
        }
    }
    else
    {
        self->reportar = false;
    }
}