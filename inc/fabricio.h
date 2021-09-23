#ifndef FABRICIO_H
#define FABRICIO_H

#include "../parameters.h"

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
float iir_filter(float x, float* xbuff, float* Yc, float* Ys, int* jj);
void THDInst_Canal(int ii, float x);
float calc_mediana(float vet[],int tam);
void FZC_Canal(int ii, float x,int *ct,float xbuf[],float *alf,int *m,float x_int[],int *kk,float *Ene2,float *px_w,int *kk1,float *s_min,float *s_max,float x_z[],float x_z1[],float *pEne1,float *Sru,int *n_ciclo,float Dref[],int *refe,int Det[],float *limiar);

#endif