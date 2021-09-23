#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <bits/stdc++.h>

// Constantes 

#define PI 3.14159265358979323846
#define NPPC 16
#define W0 (2*PI*60)
#define FS (NPPC*60)

using namespace std;

#include "Fasor.h"
// #include "DFT.h"
// #include "FiltroSG.h"
// #include "Frequencia.h"
// #include "FiltroIIR.h"
// #include "Decimacao.h"
// #include "FiltroMediaMovel.h"

#include "Canal.h"
#include "fabricio.h"

// Variaveis Globais
double x[8];
Fasor TensaoA, TensaoB, TensaoC, TensaoN, CorrenteA, CorrenteB, CorrenteC, CorrenteN;
Fasor FasorTeste;

Canal canal1;

// Prototipos de Funcoes
void get_sample(string s);

int main ()
{
    double sig_iir = 0;

    cout << "INICIOU \n" << N << endl;
    //return 0;

    //cout << FS << endl;

    init_DFT();

    cout << "INIT DFT" << endl;

    string line;
    ifstream sinais("sinais.txt");
    ifstream sinal_teste("Matlab/SinaisTeste/sinal_FRD.txt");

    
    ofstream fase("Matlab/SinaisFaseMagCM/fase_cm_PSD0.txt");
    ofstream mag("Matlab/SinaisFaseMagCM/mag_cm_PSD0.txt");
    //ofstream freq("freq.txt");

    //ofstream sig_iir_teste("sig_iir_teste.txt");
    ofstream fase_teste("Matlab/SinaisFaseMagC/fase_c_FRD0.txt");
    ofstream mag_teste("Matlab/SinaisFaseMagC/mag_c_FRD0.txt");
    ofstream freq_teste("Matlab/SinaisFrequencia/freq_c_FRD0.txt");

    ofstream fase_rep("Matlab/SinaisFaseMagReporte/fase_rep_FRD0.txt");
    ofstream mag_rep("Matlab/SinaisFaseMagReporte/mag_rep_FRD0.txt");
    ofstream freq_rep("Matlab/SinaisFrequencia/freq_rep_FRD0.txt");
    ofstream rocof_rep("Matlab/SinaisFrequencia/rocof_rep_FRD0.txt");

    /*
    ofstream myfile2("THDinsts.txt");
    ofstream myfile3("Freqs.txt");
    ofstream myfile4("similaridade.txt");
    ofstream myfile5("limiar.txt");
    ofstream myfile6("Det.txt");
    */

    cout << "OPEN FILES" << endl;

    while(getline(sinais,line))
    {
        get_sample(line);

    }

    

    while(getline(sinal_teste,line))
    {
        get_sample(line);

        x[0] = x[0]/1000.0;

        processaAmostra(&canal1, x[0]);

        if(canal1.reportar)
        {
            fase_rep << canal1.timestamp << ";";
            fase_rep << std::fixed << std::setprecision(12) << canal1.fasor.fase_rep << ";" << endl;
            mag_rep << canal1.timestamp << ";";
            mag_rep << std::fixed << std::setprecision(12) << canal1.fasor.mag_rep << ";" << endl;
            freq_rep << canal1.timestamp +1 << ";";
            freq_rep << std::fixed << std::setprecision(12) << canal1.fasor.freq_rep << ";" << endl;
            rocof_rep << canal1.timestamp << ";";
            rocof_rep << std::fixed << std::setprecision(12) << canal1.rocof << ";" << endl;

        }

        
        //sig_iir = CalcularIIR(&FasorTeste.iir, x[0]);
        // //sig_iir_teste << std::fixed << std::setprecision(12) << sig_iir << ";" << endl;
        // decimaSinal(&FasorTeste.iir, &FasorTeste.decim_sinal, x[0]);
        // estimaFasor(&FasorTeste, x[0]);
        // FasorTeste.frequencia = EstimarFrequencia(&FasorTeste.est_freq, FasorTeste.decim_sinal.flag, FasorTeste.fase, FasorTeste.frequencia);
        // if(FasorTeste.decim_sinal.flag)
        // {
        //     FasorTeste.freq_rep = calculaMMFracionario(&FasorTeste.est_freq.fmmf, FasorTeste.frequencia, FasorTeste.frequencia, FS);
        // }
        
        // if(FasorTeste.decim_sinal.flag)
        // {
        //     preparaReporte(&FasorTeste);

        //     //sig_iir_teste << std::fixed << std::setprecision(12) << FasorTeste.iir.out_IIR << ";" << endl;
        //     fase_teste << std::fixed << std::setprecision(12) << FasorTeste.fase_corr << ";" << endl;
        //     mag_teste << std::fixed << std::setprecision(12) << FasorTeste.magnitude << ";" << endl;
        //     freq_teste << std::fixed << std::setprecision(12) << FasorTeste.frequencia << ";" << FasorTeste.freq_rep << ";" << endl;

        //     if(FasorTeste.reportar)
        //     {
        //         // fase_rep << FasorTeste.timestamp << ";";
        //         // fase_rep << std::fixed << std::setprecision(12) << FasorTeste.fase_rep << ";" << endl;
        //         // mag_rep << FasorTeste.timestamp << ";";
        //         // mag_rep << std::fixed << std::setprecision(12) << FasorTeste.mag_rep << ";" << endl;
        //     }
        // }

        //freq << TensaoA.frequencia << ";" << endl;
    }

    cout << "DFT" << endl;

    /*  
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < Nciclos; j++)
        {
            myfile6 << Det[i][j] << ";" ;
        }
        myfile6 << endl;
    }
    */


    sinais.close();
    sinal_teste.close();
    /*
    myfile2.close();
    myfile3.close();
    myfile4.close();
    myfile5.close();
    myfile6.close();
    */

    fase.close();
    //freq.close();

    //sig_iir_teste.close();
    fase_teste.close();
    freq_teste.close();

    fase_rep.close();
    mag_rep.close();

    cout << "CLOSE FILES" << endl;

    cout << "TERMINOU\n";

    // system("pause");

    return 0;
}

void get_sample(string s)
{
        string delimiter = ";";
        size_t pos = 0;
        string token;
        int ii = 0;
        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            x[ii++] = stof(token);
            s.erase(0, pos + delimiter.length());
        }
}