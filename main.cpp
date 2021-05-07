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

#include "PMU/PMU.h"
#include "fabricio.h"

// Variaveis Globais
double x[8];
Fasor TensaoA, TensaoB, TensaoC, TensaoN, CorrenteA, CorrenteB, CorrenteC, CorrenteN;
Fasor FasorTeste;

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
    ofstream freq("freq.txt");

    ofstream sig_iir_teste("sig_iir_teste.txt");
    ofstream fase_teste("Matlab/SinaisFaseMagC/fase_c_FRD0.txt");
    ofstream mag_teste("Matlab/SinaisFaseMagC/mag_c_FRD0.txt");
    ofstream freq_teste("Matlab/SinaisFrequencia/freq_c_FRD0.txt");

    ofstream fase_rep("Matlab/SinaisFaseMagReporte/fase_rep_FRD0.txt");
    ofstream mag_rep("Matlab/SinaisFaseMagReporte/mag_rep_FRD0.txt");
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

        /*DecimarSinal(&TensaoA, x[0]);
        DecimarSinal(&TensaoB, x[1]);
        DecimarSinal(&TensaoC, x[2]);
        DecimarSinal(&TensaoN, x[3]);
        DecimarSinal(&CorrenteA, x[4]);
        DecimarSinal(&CorrenteB, x[5]);
        DecimarSinal(&CorrenteC, x[6]);
        DecimarSinal(&CorrenteN, x[7]);

        EstimarFasor(&TensaoA, x[0]);
        EstimarFasor(&TensaoB, x[1]);
        EstimarFasor(&TensaoC, x[2]);
        EstimarFasor(&TensaoN, x[3]);
        EstimarFasor(&CorrenteA, x[4]);
        EstimarFasor(&CorrenteB, x[5]);
        EstimarFasor(&CorrenteC, x[6]);
        EstimarFasor(&CorrenteN, x[7]);

        EstimarFrequencia(&TensaoA.est_freq, TensaoA.decim.estimar, TensaoA.fase, TensaoA.frequencia);
        EstimarFrequencia(&TensaoB.est_freq, TensaoB.decim.estimar, TensaoB.fase, TensaoB.frequencia);
        EstimarFrequencia(&TensaoC.est_freq, TensaoC.decim.estimar, TensaoC.fase, TensaoC.frequencia);
        EstimarFrequencia(&TensaoN.est_freq, TensaoN.decim.estimar, TensaoN.fase, TensaoN.frequencia);
        //EstimarFrequencia(&CorrenteA.est_freq, CorrenteA.decim.estimar, CorrenteA.fase);
        //EstimarFrequencia(&CorrenteB.est_freq, CorrenteB.decim.estimar, CorrenteB.fase);
        //EstimarFrequencia(&CorrenteC.est_freq, CorrenteC.decim.estimar, CorrenteC.fase);
        //EstimarFrequencia(&CorrenteN.est_freq, CorrenteN.decim.estimar, CorrenteN.fase);

        */

        /*
        for(int ii = 0; ii < 8; ii++)
        {
            THDInst_Canal(ii,x[ii]);            
            if(ii != 3 && ii != 7)
            {
                FZC_Canal(ii, x[ii], &ct, xbuf[ii], &alf[ii],&m[ii],x_int[ii],&aa[ii],&Ene2[ii],&x_w[ii],&aa1[ii],&s_min[ii],&s_max[ii],x_z[ii],x_z1[ii],&Ene1[ii],&Sru[ii],&n_ciclo[ii],Dref[ii],&refe[ii],Det[ii],&limiar[ii]);

            }
            myfile2 << THD[ii] << ";" ;
            myfile3 << f_ZC[ii]<< ";" ;
            myfile4 << Sru[ii] << ";" ;
            myfile5 << limiar[ii] << ";" ;
        }

        myfile2 << endl;
        myfile3 << endl;
        myfile4 << endl;
        myfile5 << endl; 
        */

        //myfile7 << TensaoA.fase << ";";
        /*
        fase << TensaoA.fase << ";";
        fase << TensaoB.fase << ";";
        fase << TensaoC.fase << ";";
        fase << TensaoN.fase << ";";
        fase << CorrenteA.fase << ";";
        fase << CorrenteB.fase << ";";
        fase << CorrenteC.fase << ";";
        fase << CorrenteN.fase << ";" << endl;

        freq << TensaoA.frequencia << ";";
        freq << TensaoB.frequencia << ";";
        freq << TensaoC.frequencia << ";";
        freq << TensaoN.frequencia << ";";
        freq << CorrenteA.frequencia << ";";
        freq << CorrenteB.frequencia << ";";
        freq << CorrenteC.frequencia << ";";
        freq << CorrenteN.frequencia << ";" << endl;
        */
    }

    

    while(getline(sinal_teste,line))
    {
        get_sample(line);

        x[0] = x[0]/1000.0;

        
        //sig_iir = CalcularIIR(&FasorTeste.iir, x[0]);
        //sig_iir_teste << std::fixed << std::setprecision(12) << sig_iir << ";" << endl;
        decimaSinal(&FasorTeste.iir, &FasorTeste.decim_sinal, x[0]);
        estimaFasor(&FasorTeste, x[0]);
        FasorTeste.frequencia = EstimarFrequencia(&FasorTeste.est_freq, FasorTeste.decim_sinal.flag, FasorTeste.fase, FasorTeste.frequencia);

        if(FasorTeste.decim_sinal.flag)
        {
            preparaReporte(&FasorTeste);

            sig_iir_teste << std::fixed << std::setprecision(12) << FasorTeste.iir.out_IIR << ";" << endl;
            fase_teste << std::fixed << std::setprecision(12) << FasorTeste.fase_rep << ";" << endl;
            mag_teste << std::fixed << std::setprecision(12) << FasorTeste.magnitude << ";" << endl;
            freq_teste << std::fixed << std::setprecision(12) << FasorTeste.frequencia << ";" << endl;

            if(FasorTeste.reportar)
            {
                fase_rep << FasorTeste.timestamp << ";";
                fase_rep << std::fixed << std::setprecision(12) << FasorTeste.fase_rep << ";" << endl;
                mag_rep << FasorTeste.timestamp << ";";
                mag_rep << std::fixed << std::setprecision(12) << FasorTeste.magnitude << ";" << endl;
            }
        }

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
    freq.close();

    sig_iir_teste.close();
    fase_teste.close();
    freq_teste.close();

    fase_rep.close();
    mag_rep.close();

    cout << "CLOSE FILES" << endl;

    cout << "TERMINOU\n";

    bool encerrar = false;

    while(encerrar == false)
    {
        cout << "Fechar?(1/0)\n";
        cin >> encerrar;
    }

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