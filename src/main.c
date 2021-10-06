#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../parameters.h"
#include "Canal.h"

// Variaveis Globais

Canal canal1;

// Prototipos de Funcoes

double get_sample(FILE* pFile);

int main ()
{
    double sample;

    const char* filename = "Matlab/SinaisTeste/sinal_FRD.txt";
    FILE* sinal_teste = fopen(filename,"r");
    if (!sinal_teste) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE* fase_rep = fopen("Matlab/SinaisFaseMagReporte/fase_rep_FRD0.txt","w");
    if (!fase_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE* mag_rep = fopen("Matlab/SinaisFaseMagReporte/mag_rep_FRD0.txt","w");
    if (!mag_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE* freq_rep = fopen("Matlab/SinaisFrequencia/freq_rep_FRD0.txt","w");
    if (!freq_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE* rocof_rep = fopen("Matlab/SinaisFrequencia/rocof_rep_FRD0.txt","w");
    if (!rocof_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    printf("> Start\n");

    init_DFT();

    printf("> Init DFT\n");

    // ofstream fase_teste("Matlab/SinaisFaseMagC/fase_c_FRD0.txt");
    // ofstream mag_teste("Matlab/SinaisFaseMagC/mag_c_FRD0.txt");
    // ofstream freq_teste("Matlab/SinaisFrequencia/freq_c_FRD0.txt");

    printf("> Open Files\n");

    while((sample = get_sample(sinal_teste)))
    {
        sample = sample/(double)1000.0;
        // printf("%f\n",sample);
        processaAmostra(&canal1, sample);


        if(canal1.reportar)
        {
            fprintf(fase_rep, "%d;%.12lf;\n", canal1.timestamp, canal1.fasor.fase_rep);
            fprintf(mag_rep, "%d;%.12lf;\n", canal1.timestamp, canal1.fasor.mag_rep);
            fprintf(freq_rep, "%d;%.12lf;\n", canal1.timestamp, canal1.fasor.freq_rep);
            fprintf(rocof_rep, "%d;%.12lf;\n", canal1.timestamp, canal1.rocof);
        }
    }

    fclose(sinal_teste);
    fclose(fase_rep);
    fclose(mag_rep);
    fclose(freq_rep);
    fclose(rocof_rep);

    printf("> Close files\n");

    printf("> End\n");

    return 0;
}

double get_sample(FILE* pFile)
{
    double sample;

    char *file_contents = (char*)malloc(sizeof(char)*40);
    

    if(fscanf(pFile, "%[^\n] ", file_contents) != EOF)
    {
        sscanf(file_contents,"%lf", &sample);
        return sample;
    }
    else
    {
        return 0;
    }
}