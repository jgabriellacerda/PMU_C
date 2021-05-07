function [Freq,legs,delay_SG] = FreqSG(fase_unwrap,fs)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%% SG projetado por frequência de amostragem

if fs ==  1440
    n = 2;
    N_SG = 8;
elseif fs == 960
    n = 3;
    N_SG = 8;
elseif fs == 15360
    n = 1;
    N_SG = 92;
else
    n = 3;
    N_SG = 3;
end

x = -N_SG:N_SG;
dn = 1;
x0 = 0;
W = [];
flag = 0;

[fc,df] = savitzkyGolay(x,n,dn,x0,W,flag);
SG(1,1:length(fc)) = fc;

sSG = sprintf("SG(%d,%d)",n,length(SG));
SG_new = SG(1,:);

% for i = 1:length(SG)
%     fprintf("%f, ",SG(i));
% end

% freqz(SG(1,:),1,1000000,fs);

%% SG de tamanho mínimo (leve)
 
n = 1;
N_SG = 1;
x = -N_SG:N_SG;
dn = 1;
x0 = 0;
W = [];
flag = 0;

[fc,df] = savitzkyGolay(x,n,dn,x0,W,flag);
SG = fc;

sSG_leve = sprintf("SG(%d,%d)",n,length(SG));
SG_leve = SG;

%% Calcula frequência
   
Freq_SG_new = conv( SG_new, fase_unwrap)' * 229.183118052 * (fs/1440);

Freq =  Freq_SG_new;

legs = [sSG  " + Media-movel"];
delay_SG = [length(SG_new)]/2;
end

