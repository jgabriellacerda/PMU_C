#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "../parameters.h"
#include "Channel.h"
#include <string.h>

// Prototipos de Funcoes

double get_sample(FILE *pFile);

int main()
{
    clock_t start, end;

    int fs = 960;

    Channel *channel1 = newChannel(fs, false);

    double sample;

    char sTest[] = "FRD";

    char filename[50] = "Matlab/SinaisTeste/sinal_";
    strcat(filename, sTest);
    strcat(filename, ".txt");
    FILE *sinal_teste = fopen(filename, "r");
    if (!sinal_teste)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char file_ext[8];
    strcpy(file_ext, sTest);
    strcat(file_ext, "0.txt");

    char fase_rep_file[60] = "Matlab/SinaisFaseMagReporte/fase_rep_";
    strcat(fase_rep_file, file_ext);
    FILE *fase_rep = fopen(fase_rep_file, "w");
    if (!fase_rep)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    printf("\n%s\n", fase_rep_file);

    char mag_rep_file[60] = "Matlab/SinaisFaseMagReporte/mag_rep_";
    strcat(mag_rep_file, file_ext);
    FILE *mag_rep = fopen(mag_rep_file, "w");
    if (!mag_rep)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char freq_rep_file[60] = "Matlab/SinaisFrequencia/freq_rep_";
    strcat(freq_rep_file, file_ext);
    FILE *freq_rep = fopen(freq_rep_file, "w");
    if (!freq_rep)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char rocof_rep_file[60] = "Matlab/SinaisFrequencia/rocof_rep_";
    strcat(rocof_rep_file, file_ext);
    FILE *rocof_rep = fopen(rocof_rep_file, "w");
    if (!rocof_rep)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    printf("> Start\n");

    printf("> Open Files\n");

    double signal[184320];

    for (int i = 0; i < 184320; i++)
    {
        signal[i] = get_sample(sinal_teste);
    }

    start = clock();

    for (int j = 0; j < 1; j++)
    {
        for (int i = 0; i < 184320; i++)
        {
            sample = signal[i];

            // while((sample = get_sample(sinal_teste)))
            // {
            sample = sample / (double)1000.0;

            channel1->processSample(channel1, sample);
            if (channel1->report)
            {
                // printf("%f\n", sample);
                fprintf(fase_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->fase_rep);
                fprintf(mag_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->mag_rep);
                fprintf(freq_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->freq_rep);
                fprintf(rocof_rep, "%d;%.12lf;\n", channel1->timestamp, channel1->rocof);
            }
        }
    }

    end = clock();

    long int clocks = (end - start);
    double time_taken = ((double)(end - start)) / (double)CLOCKS_PER_SEC;

    printf("Tempo = %lf\n", time_taken);
    printf("Clocks = %d\n", clocks);
    printf("Clocks/s = %d\n", CLOCKS_PER_SEC);

    // long int iterations = 100000000;

    // int n = 0;
    // start = clock();

    // for(long int j = 0; j < iterations; j++)
    // {
    //     n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}
    //     n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}n=n-1;if(n==0){n=100;}
    // }

    // end = clock();

    // clocks = (end - start);

    // printf("Ifs = %d\n", clocks);

    // n = 0;
    // start = clock();

    // for(long int j = 0; j < iterations; j++)
    // {
    //     n = (n+1) % 100;n = (n+1) % 100;n = (n+1) % 100;n = (n+1) % 100;n = (n+1) % 100;
    //     n = (n+1) % 100;n = (n+1) % 100;n = (n+1) % 100;n = (n+1) % 100;n = (n+1) % 100;
    // }

    // end = clock();

    // clocks = (end - start);

    // printf("Mod = %d\n", clocks);

    // n = 0;
    // start = clock();

    // for(long int j = 0; j < iterations; j++)
    // {
    //     n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);
    //     n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);n = (n == 100)*0 + (n < 100)*(n+1);
    // }

    // end = clock();

    // clocks = (end - start);

    // printf("Logic = %d\n", clocks);

    // n = 0;
    // start = clock();

    // for(long int j = 0; j < iterations; j++)
    // {
    //     n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;
    //     n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;n = (n == 0) ? 100 : n-1;
    // }

    // end = clock();

    // clocks = (end - start);

    // printf("Question = %d\n", clocks);

    // int iterations = 184320;

    // DFT* dft1 = new_dft(fs);
    // start = clock();

    // for(long int j = 0; j < iterations; j++)
    // {
    //     sample = signal[j];
    //     calculaDFT(dft1, sample);calculaDFT(dft1, sample);calculaDFT(dft1, sample);calculaDFT(dft1, sample);calculaDFT(dft1, sample);
    //     calculaDFT(dft1, sample);calculaDFT(dft1, sample);calculaDFT(dft1, sample);calculaDFT(dft1, sample);calculaDFT(dft1, sample);

    // }

    // end = clock();

    // clocks = (end - start);

    // printf("DFT = %d\n", clocks);

    // start = clock();

    // for(long int j = 0; j < iterations; j++)
    // {
    //     sample = signal[j];
    //     symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);
    //     symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);symmetricDFT(dft1, sample);
    // }

    // end = clock();

    // clocks = (end - start);

    // printf("Symmetric = %d\n", clocks);

    long int iterations = 184320 * 1;

    Channel *ch2 = newChannel(960, false);

    int p = 0;

    start = clock();

    for (long int j = 0; j < iterations; j++)
    {
        sample = signal[p];
        ch2->processSample(ch2, sample);
        p = (p == 184320 - 1) ? 0 : p + 1;
    }

    end = clock();

    clocks = (end - start);

    printf("Channel default = %d\n", clocks);

    Channel *ch3 = newChannel(960, true);

    p = 0;

    start = clock();

    for (long int j = 0; j < iterations; j++)
    {
        sample = signal[p];
        ch3->processSample(ch3, sample);
        p = (p == 184320 - 1) ? 0 : p + 1;
    }

    end = clock();

    clocks = (end - start);

    printf("Channel symmetric = %d\n", clocks);

    fclose(sinal_teste);
    fclose(fase_rep);
    fclose(mag_rep);
    fclose(freq_rep);
    fclose(rocof_rep);

    printf("> Close files\n");

    printf("> End\n");

    return 0;
}

double get_sample(FILE *pFile)
{
    double sample;

    char *file_contents = (char *)malloc(sizeof(char) * 40);

    if (fscanf(pFile, "%[^\n] ", file_contents) != EOF)
    {
        sscanf(file_contents, "%lf", &sample);
        return sample;
    }
    else
    {
        return 0;
    }
}