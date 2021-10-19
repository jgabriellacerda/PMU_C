#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "../parameters.h"
#include "Channel.h"
#include <string.h>

// Prototipos de Funcoes

double get_sample(FILE* pFile);

int main ()
{
    clock_t start, end;

    int fs = 960;

    Channel* channel1 = newChannel(fs);

    double sample;

    char sTest[] = "FRD";

    char filename[50] = "Matlab/SinaisTeste/sinal_";
    strcat(filename, sTest);
    strcat(filename, ".txt");
    FILE* sinal_teste = fopen(filename,"r");
    if (!sinal_teste) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char file_ext[8];
    strcpy(file_ext, sTest);
    strcat(file_ext, "0.txt");

    char fase_rep_file[60] = "Matlab/SinaisFaseMagReporte/fase_rep_";
    strcat(fase_rep_file, file_ext);
    FILE* fase_rep = fopen(fase_rep_file,"w");
    if (!fase_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    printf("\n%s\n", fase_rep_file);

    char mag_rep_file[60] = "Matlab/SinaisFaseMagReporte/mag_rep_";
    strcat(mag_rep_file, file_ext);
    FILE* mag_rep = fopen(mag_rep_file,"w");
    if (!mag_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char freq_rep_file[60] = "Matlab/SinaisFrequencia/freq_rep_";
    strcat(freq_rep_file, file_ext);
    FILE* freq_rep = fopen(freq_rep_file,"w");
    if (!freq_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char rocof_rep_file[60] = "Matlab/SinaisFrequencia/rocof_rep_";
    strcat(rocof_rep_file, file_ext);
    FILE* rocof_rep = fopen(rocof_rep_file,"w");
    if (!rocof_rep) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    printf("> Start\n");

    printf("> Init DFT\n");

    // ofstream fase_teste("Matlab/SinaisFaseMagC/fase_c_FRD0.txt");
    // ofstream mag_teste("Matlab/SinaisFaseMagC/mag_c_FRD0.txt");
    // ofstream freq_teste("Matlab/SinaisFrequencia/freq_c_FRD0.txt");

    printf("> Open Files\n");

    double signal[184320];

    for(int i = 0; i < 184320; i++)
    {
        signal[i] = get_sample(sinal_teste);
    }

    start = clock();

    for(int j = 0; j < 1; j++)
    {
        for(int i = 0; i < 184320; i++)
        {
            sample = signal[i];

        // while((sample = get_sample(sinal_teste)))
        // {
            sample = sample/(double)1000.0;

            channel1->processSample(channel1, sample);


            if(channel1->reportar)
            {
                fprintf(fase_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->fase_rep);
                fprintf(mag_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->mag_rep);
                fprintf(freq_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->freq_rep);
                fprintf(rocof_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->rocof);
            }
        }
    }

    end = clock();

    double time_taken = ((double)(end - start))/(double)CLOCKS_PER_SEC;

    printf("Tempo = %lf\n", time_taken);

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