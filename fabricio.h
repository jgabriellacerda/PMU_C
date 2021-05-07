#define apc 256
#define Nw 256
#define M_PI 3.14159265358979323846
#define Nciclos 200
#define gamma 3         // Constante de sensibilidade do detector
#define wo 5              //tamanho da janela de refer�ncia do detector


//Prototipos de Funcoes

void THDInst_Canal(int ii, float x);
float iir_filter(float x, float* xbuff, float* Yc, float* Ys, int* jj);
void FZC_Canal(int ii, float x,int *ct,float xbuf[],float* alf,int *m,float x_int[],int *aa,float *Ene2,float *px_w,int *aa1,float *s_min,float *s_max,float x_z[],float x_z1[],float *pEne1,float *Sru,int *n_ciclo,float Dref[],int *refe,int Det[],float *limiar);
float calc_mediana(float vet[],int tam); // C�lculo da mediana usado no limiar do detector

float Yc[8] = {};
float Ys[8] = {};
int kk[8] = {};
int jj[8] = {};
float x_buff[8][apc]= {};
float x60[8]= {};
float x60_buff[8][apc] = {};
float xHs_buff[8][apc] = {};
float RMS_x60[8]={};
float RMS_xHs[8]={};
float THD[8]={};

float f_ZC[8]={};

float va[8]={};
float Tsc[8] = {1.0/60,1.0/60,1.0/60,1.0/60,1.0/60,1.0/60,1.0/60,1.0/60};
float cnt[8]={};
float T1[8]={};

float  xbuffZC[8][apc] = {};
float YcZC[8] = {};
float YsZC[8] = {};

// novas variaveis

float xbuf[8][4] = {};
int ct = 0; //contador para condi��o inicial do buffer
float alf[8] = {};
int m[8] = {};
float x_int[8][NPPC*Nciclos];

int aa[8] = {}; //kk
float Ene2[8] = {}; //Armazena energia dos ciclos
float Ene1[8] = {};
float x_w[8] = {}; // Amostra mais recente
int aa1[8] = {}; //kk1
float s_min[8] = {}; //Somat�rio dos valores m�nimos entre dois ciclos
float s_max[8] = {};  //Somat�rio dos valores m�ximos
float x_z[8][NPPC] = {}; //Ciclo anterior
float x_z1[8][NPPC] = {}; //Ciclo de refer�ncia para o limiar (atualizado toda vez que ocorre uma detec��o)
float Sru[8] = {}; // M�trica de similaridade de Ruzicka
int n_ciclo[8] = {};  // N�mero do ciclo
float Dref[8][wo] = {}; // Dissimilaridade de refer�ncia
int refe[8] = {};
int Det[8][Nciclos] = {}; // Detec��es
float limiar[8] = {};

float iir_filter(float x, float* xbuff, float* Yc, float* Ys, int* jj)
{
    float x_N, y;
    // Filtro SWRDFT para extrair componente de 60 Hz

    x_N = xbuff[*jj];

    *Yc = *Yc - (x*cos(2*M_PI*(1.0/apc)*(*jj)) - x_N*cos(2*M_PI*(1.0/apc)*((*jj)-apc)));
    *Ys = *Ys - (x*sin(2*M_PI*(1.0/apc)*(*jj)) - x_N*sin(2*M_PI*(1.0/apc)*((*jj)-apc)));

    y = (*Yc*cos(2*M_PI*(1.0/apc)*(*jj)) - *Ys*sin(2*M_PI*(1.0/apc)*(*jj)))*2.0/apc;

    xbuff[*jj] = x;

    (*jj)++;
    if(*jj >= apc)
    {
        *jj = 0;
    }

    return y;
}

void THDInst_Canal(int ii, float x)
{

     float x_N, x60, xHs, x60_N, xHs_N;

    // Filtro SWRDFT para extrair componente de 60 Hz

    x_N = x_buff[ii][kk[ii]];

    Yc[ii] = Yc[ii] + (x*cos(2*M_PI*(1.0/apc)*kk[ii]) - x_N*cos(2*M_PI*(1.0/apc)*(kk[ii]-apc)));
    Ys[ii] = Ys[ii] - (x*sin(2*M_PI*(1.0/apc)*kk[ii]) - x_N*sin(2*M_PI*(1.0/apc)*(kk[ii]-apc)));

    x60 = (Yc[ii]*cos(2*M_PI*(1.0/apc)*kk[ii]) - Ys[ii]*sin(2*M_PI*(1.0/apc)*kk[ii]))*2.0/apc;

    // Calculo do RMS2 instant�neo do componente de 60Hz e dos Harmonicos

    xHs = x - x60;

    x60_N = x60_buff[ii][kk[ii]];
    xHs_N = xHs_buff[ii][kk[ii]];

    RMS_x60[ii] = RMS_x60[ii] + (1.0/Nw)*(pow(x60,2) - pow(x60_N,2));
    RMS_xHs[ii] = RMS_xHs[ii] + (1.0/Nw)*(pow(xHs,2) - pow(xHs_N,2));

    // Calculo do THD
    THD[ii] = sqrt(RMS_xHs[ii]/RMS_x60[ii]);

    // Atualizacao dos Buffers
    x_buff[ii][kk[ii]] = x;
    x60_buff[ii][kk[ii]] = x60;
    xHs_buff[ii][kk[ii]] = xHs;

    kk[ii] = kk[ii] + 1;

    if(kk[ii] >= apc)
        {
            kk[ii] = 0;
        }
}

float calc_mediana(float vet[],int tam)
{
	float mediana;
	sort(vet,vet+tam);

	if(tam%2 == 1)
	{
		mediana = vet[tam/2];
		return mediana;
	}
	else
	{
		mediana = (vet[tam/2]+vet[tam/2-1])/2;
		return mediana;
	}
}


void FZC_Canal(int ii, float x,int *ct,float xbuf[],float *alf,int *m,float x_int[],int *kk,float *Ene2,float *px_w,int *kk1,float *s_min,float *s_max,float x_z[],float x_z1[],float *pEne1,float *Sru,int *n_ciclo,float Dref[],int *refe,int Det[],float *limiar)
{
    float v, sig, Nb, T2, Ts;

    Ts = 1.0/(256*60);

    v=iir_filter(x, xbuffZC[ii], &YcZC[ii], &YsZC[ii], &jj[ii]);

    if (va[ii] >= 0)
    {
        sig = va[ii] * v;
    }
    else
    {
        sig = 1;
    }

    Tsc[ii] = Tsc[ii] + Ts;
    cnt[ii] = cnt[ii] + 1;

    if (sig < 0)
    {
        Nb = v/(v - va[ii]);
        T2 = Nb * Ts;
        Tsc[ii] = Tsc[ii] + T1[ii] - T2;
        f_ZC[ii] = 1.0/Tsc[ii];
        T1[ii] = T2;
        Tsc[ii] = 0;
        cnt[ii] = 0;

        if (f_ZC[ii] > 64)
            f_ZC[ii] = 64;
        if (f_ZC[ii] < 56)
            f_ZC[ii] = 56;
    }

    if ((*ct) < 8*NPPC)
        f_ZC[ii] = 60;

    va[ii] = v;

    //interpolador

	float H0[4] = {1.0/6,-1.0/2,1.0/2,-1.0/6};
    float H1[4] = {1.0/2,-1,1.0/2,0};
    float H2[4] = {1.0/3,1.0/2,-1,1.0/6};
    float Ts_out = 1.0/(f_ZC[ii]*256);
    float lamb = Ts_out/Ts;
    float y0 = 0,y1 = 0,y2 = 0;

    (*ct)++;

    if ((*ct) <= 8)
    {
        xbuf[0] = x;
    }

    for(int i = 0; i < 4; i++)
    {
        y0 = H0[i]*xbuf[i] + y0;
        y1 = H1[i]*xbuf[i] + y1;
        y2 = H2[i]*xbuf[i] + y2;
    }


    while ((*alf) <= 1)
    {
        if ((*alf) == 0)
            {
                x_int[(*m)] = xbuf[1];
            }
            else
            {
                x_int[(*m)] = (*alf)*((*alf)*((*alf)*y0+y1)+y2)+xbuf[1];
            }

        (*alf) = (*alf) + lamb;
        (*m)++;
            int op = (*kk)%NPPC; // variavel usada para definir o final de um ciclo

    px_w = &x_w[ii];
    pEne1 = &Ene1[ii];
    (*Ene2) = (*Ene2) + x_int[*kk]*x_int[*kk];
    x_w[ii] = fabs(x_int[*kk]);


    *s_min = *s_min + fmin((x_w[ii])/sqrt(Ene1[ii]),x_z1[*kk1]/sqrt(Ene1[ii])); // somando o valor minimo entre o ciclo atual e o de refer�ncia
    *s_max = *s_max + fmax((x_w[ii])/sqrt(Ene1[ii]),x_z1[*kk1]/sqrt(Ene1[ii])); // somando o valor m�ximo

    x_z[*kk1] = x_w[ii];

    (*kk1)++;

    if(op == 0)
    {
        (*Sru) = (*s_min)/(*s_max);
        Ene1[ii] = *Ene2;
        *Ene2 = 0;
        (*s_min) = 0;
        (*s_max) = 0;
        (*kk1) = 0;

        Dref[(*refe)] = 1 - *Sru;

        (*refe)++;

        int op2 = (*n_ciclo)%wo;

        if(op2 == 0)
        {
            (*refe)= 0;
        }

        (*n_ciclo)++;
    }

    float mediana;
    float nS;
    mediana = calc_mediana(Dref,wo);

    nS = fabs(1 - gamma*mediana); // Limiar adapt�vel
    *limiar = nS;

    if (*Sru < nS)
    {
        for(int l = 0; l < NPPC; l++)
        {
            x_z1[l] = x_z[l]; //Atualizando o ciclo de refer�ncia
        }
        Det[*n_ciclo] = 1; // Detec��o
    }

    (*kk)++;


    }

    (*alf) = (*alf) - 1;

    xbuf[3] = xbuf[2];
    xbuf[2] = xbuf[1];
    xbuf[1] = xbuf[0];
    xbuf[0] = x;

}
