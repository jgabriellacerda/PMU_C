#include "FiltroMediaMovel.h"


double calculaMediaMovel(FMM *fmm, double amostra, int N, bool unwrap)
{
    static const double pi = 3.141592653589793;
    static const double dois_pi = 6.283185307179586;
    double diff = 0;
    double soma = 0;
    int k = 0;
    int k0 = 0;
    int k1 = 0;

    if (N < 1 || N > N_MM_MAX)
    {
        return 0;
    }

    if(unwrap)
    {
        k0 = fmm->k0;
        k1 = (fmm->k0 + 1) % N_MM_MAX;

        fmm->buffMM[k1] = amostra;

        fmm->buff_unwrap[k1] = amostra;

        diff = fmm->buffMM[k1] - fmm->buffMM[k0];
        if (diff > pi*3/4)
        {
            fmm->cont_unwrap = 0;
            fmm->offset -= dois_pi;
        }
        else if (diff < -pi*3/4)
        {
            fmm->cont_unwrap = 0;
            fmm->offset += dois_pi;
        }
        else
        {
            fmm->cont_unwrap++; 
        }

        fmm->buff_unwrap[k1] = amostra + fmm->offset;
        
        if (fmm->cont_unwrap > 17)
        {
            fmm->offset = 0;
            for(int i = 0; i < N_MM_MAX; i++)
            {
                fmm->buff_unwrap[i] = fmm->buffMM[i];
            }
        }

        fmm->k0 = k1;

        soma = 0;
        for(int i = 0; i < N; i++ )
        {
            k = fmm->k0 - i;
            if(k < 0)
            {
                k += N_MM_MAX;
            }
            soma += fmm->buff_unwrap[k];
        }
        fmm->y1 = soma / N;

        if(fmm->y1 > pi)
        {
            fmm->y1 -= dois_pi;
        }
        else if(fmm->y1 < -pi)
        {
            fmm->y1 += dois_pi;
        }
    }
    else
    {
        fmm->pos_sub = fmm->k0 - N + 1;
        if(fmm->pos_sub < 0)
        {
            fmm->pos_sub += N_MM_MAX;
        }

        fmm->y1 = fmm->y0 + (amostra - fmm->buffMM[fmm->pos_sub]) / N;
        fmm->k0 = (fmm->k0 + 1) % N_MM_MAX;
        fmm->buffMM[fmm->k0] = amostra;
        fmm->y0 = fmm->y1;
    }

    return fmm->y1;
}

double calculaMMFracionario(FMMFracionario *fmmf, double amostra, double freq, int fs){
    
    double freq_aux = 60-freq;
    double Nf = fs/freq_aux;
    double saida = 0;

    Nf = Nf < N_MM_MIN ? N_MM_MIN : Nf;
    Nf = Nf > N_MM_MAX*0.999 ? N_MM_MAX : Nf; // limita o valor de L a 17

    int L = (int)Nf;

    double Nfrac = Nf - L;

    fmmf->k0 = (fmmf->k0 + 1) % N_MM_MAX;
    

    // amostra posicionada em k0-L+1
    int k_L_1 = fmmf->k0-L+1;
    k_L_1 = k_L_1 < 0 ? k_L_1 + N_MM_MAX : k_L_1;

    // amostra posicionada em k0-L
    int k_L = fmmf->k0-L;
    k_L = k_L < 0 ? k_L + N_MM_MAX : k_L;

    double amostra_interp = fmmf->buffMM[k_L_1] - Nfrac*(fmmf->buffMM[k_L_1] - fmmf->buffMM[k_L]);

    //cout << amostra_interp << endl;

    // posicao da amostra mais antiga
    int pos_sub_N14 = fmmf->k0-14;
    pos_sub_N14 = pos_sub_N14 < 0 ? pos_sub_N14 + N_MM_MAX : pos_sub_N14;

    // soma das ultimas 14 amostras
    fmmf->soma_N14 = fmmf->soma_N14 + (amostra - fmmf->buffMM[pos_sub_N14]);

    // posicao da amostra mais antiga
    int pos_sub_N15 = fmmf->k0-15;
    pos_sub_N15 = pos_sub_N15 < 0 ? pos_sub_N15 + N_MM_MAX : pos_sub_N15;

    // soma das ultimas 15 amostras
    fmmf->soma_N15 = fmmf->soma_N15 + (amostra - fmmf->buffMM[pos_sub_N15]);

    // posicao da amostra mais antiga
    int pos_sub_N16 = fmmf->k0-16;
    pos_sub_N16 = pos_sub_N16 < 0 ? pos_sub_N16 + N_MM_MAX : pos_sub_N16;

    // soma das ultimas 16 amostras
    fmmf->soma_N16 = fmmf->soma_N16 + (amostra - fmmf->buffMM[pos_sub_N16]);

    // posicao da amostra mais antiga
    int pos_sub_N17 = fmmf->k0-17;
    pos_sub_N17 = pos_sub_N17 < 0 ? pos_sub_N17 + N_MM_MAX : pos_sub_N17;

    // soma das ultimas 17 amostras
    fmmf->soma_N17 = fmmf->soma_N17 + (amostra - fmmf->buffMM[pos_sub_N17]);

    switch(L)
    {
        case 14:
            saida = (fmmf->soma_N14 + Nfrac*amostra_interp)/Nf;
            break;
        case 15:
            saida = (fmmf->soma_N15 + Nfrac*amostra_interp)/Nf;
            break;
        case 16:
            saida = (fmmf->soma_N16 + Nfrac*amostra_interp)/Nf;
            break;
        case 17:
            saida = (fmmf->soma_N17 + Nfrac*amostra_interp)/Nf;
            break;
        default:
            saida = 0;
            break;
    }

    fmmf->buffMM[fmmf->k0] = amostra;
    
    return saida;

}