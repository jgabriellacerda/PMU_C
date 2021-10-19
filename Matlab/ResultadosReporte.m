clear all
close all
clc 

opengl hardware

tic

%% Parametros

nppc = 16;
N = nppc*10.25;
fs = 960;
ciclos = 30;
ind = 1; %canal
T = 1/fs;
Fr = 8.19;
ruido = false;

%[W,N] = gera_coef_w(N,fs,Fr);
%Gain = sqrt(2)/sum(W)

%% Sinal

FUND = 5;
HARMONIC = 0;
FREQ_RAMP = 1;
AMP_MOD = 2;
PHASE_MOD = 3;
PHASE_STEP = 4;

TEST = 1;

switch TEST
    case FREQ_RAMP        
        sTest = 'FRD';
        file = sprintf('Signals Data %dHz/database_FRD.mat',fs);
        data = load(file);
        data = data.FRD;

        file = sprintf('Signals Data %dHz/database_FRD.mat',960);
        data_dec = load(file);
        data_dec = data_dec.FRD;
        
        tve_lim = 1;
        fe_lim = 10;
        rfe_lim = 0.2;
        
    case PHASE_MOD
        sTest = 'PMD';
        file = sprintf('Signals Data %dHz/database_PMD.mat',fs);
        data = load(file);
        data = data.PMD;

        file = sprintf('Signals Data %dHz/database_PMD.mat',960);
        data_dec = load(file);
        data_dec = data_dec.PMD;
        
        tve_lim = 3;
        fe_lim = 300;
        rfe_lim = 14;
        
    case HARMONIC
        sTest = 'HRM';
        f = ones([1 fs*12])*60;
        t = (0:fs*12-1)*T; % 10 seconds
        theta = 0;
        fasor = exp(1i*(2*pi*60*t + theta)); %fundamental
        signal = real(fasor);

        for i = 3:2:7
            harm = 0.1*cos(2*pi*60*i*t);
            signal = signal + harm;
        end
        
        if ruido 
            signal = soma_ruido(signal,1,60); % Insere ruido no sinal
        end

        t_dec = (0:960*12-1)/960; % 10 seconds
        f_dec = ones([1 960*12])*60;
        theta = 0;
        fasor_dec = exp(1i*(2*pi*60*t_dec + theta)); % fundamental
        
        tve_lim = 1;
        fe_lim = 25;
        rfe_lim = 14;
        
    case FUND
        sTest = 'FND';
        f = ones([1 fs*12])*60;
        t = (0:fs*12-1)*T; % 10 seconds
        theta = 0;
        fasor = exp(1i*(2*pi*60*t + theta)); %fundamental
        signal = real(fasor);
        
        if ruido 
            signal = soma_ruido(signal,1,50); % Insere ruido no sinal
        end

        t_dec = (0:960*12-1)/960; % 10 seconds
        f_dec = ones([1 960*12])*60;
        fasor_dec = exp(1i*(2*pi*60*t_dec + theta)); % fundamental
        
        tve_lim = 1;
        fe_lim = 25;
        rfe_lim = 14;
        
    case AMP_MOD
        sTest = 'AMD';
        file = sprintf('Signals Data %dHz/database_AMD.mat',fs);
        data = load(file);
        data = data.AMD;
        
        file = sprintf('Signals Data %dHz/database_AMD.mat',960);
        data_dec = load(file);
        data_dec = data_dec.AMD;
        
        tve_lim = 3;
        fe_lim = 300;
        rfe_lim = 14;
    case PHASE_STEP
        sTest = 'PSD';
        file = sprintf('Signals Data %dHz/database_PSD.mat',fs);
        data = load(file);
        data = data.PSD;
        
        file = sprintf('Signals Data %dHz/database_PSD.mat',960);
        data_dec = load(file);
        data_dec = data_dec.PSD;
        
        tve_lim = 1;
        fe_lim = 5;
        rfe_lim = 0.1;
end

if TEST ~= HARMONIC & TEST ~= FUND
    t = data(1,:);
    f = data(2,:);
    fasor = data(3,:);
    signal = real(fasor);
    
    if ruido
        signal = soma_ruido(signal,1,60); % Insere ruido no sinal
    end
    
    t_dec = data_dec(1,:);
    f_dec = data_dec(2,:);
    fasor_dec = data_dec(3,:);

end

%% DFT

file = sprintf('SinaisFaseMagReporte/fase_rep_%s0.txt',sTest);
data_fase = load(file);
fase_rep = data_fase(:,2)';
timestamp = data_fase(:,1)';

file = sprintf('SinaisFaseMagReporte/mag_rep_%s0.txt',sTest);
mag_rep = load(file);
mag_rep = mag_rep(:,2)';

file = sprintf('SinaisFaseMagMatlab/fase_dec_matlab_%s.txt',sTest);
fase_matlab = load(file);

file = sprintf('SinaisFaseMagMatlab/mag_dec_matlab_%s.txt',sTest);
mag_matlab = load(file);

% valores certos
coef_a = -0.007332419963127;
coef_b = -0.436483107452006;


%% Estima��o de frequ�ncia

delay_N = (N+1)/2;

file = sprintf('SinaisFrequencia/freq_rep_%s0.txt',sTest);
freq_rep = load(file);
delay_freq_rep = freq_rep(1,1);
freq_rep = -freq_rep(:,2)';
delay_SG = floor(17/2);

[freq_matlab,legs,delay_SG_dec] = FreqSG(unwrap(fase_matlab),960);
corr_matlab = (coef_a*(-freq_matlab(1,1:length(fase_matlab)))' + coef_b);

corr_ideal = (coef_a*(f-60)' + coef_b);

% fase_c = fase_c - corr_cm;
fase_matlab = fase_matlab - corr_matlab;

delay_N_dec = 165/2;

%% Filtro Media-Movel de ordem variavel
janela_frac = true;

[freq_matlab,janela] = MAF_Variavel(freq_matlab,janela_frac,1/960,16,true,false);
freq_matlab = -freq_matlab;

delay_mm_dec = 16/2;
delay_f_dec = floor(delay_N_dec + delay_SG_dec + delay_mm_dec);
freq_matlab = freq_matlab(delay_f_dec+1:end);

%janela = janela(:,1:length(f));

%% Plots

T = 1/fs;
t = (0:length(fasor)-1)*T;
fasor_fund = 1*exp(1i*2*(60)*pi.*t);
ang_ref = (angle(fasor_fund) - angle(fasor));

t_rep = timestamp*(1/60);

figure;
plot(t_rep,unwrap(fase_rep),'-o','LineWidth',3);
hold on
plot(t,unwrap(fase_matlab),'-o','LineWidth',3);
plot(t,-unwrap(ang_ref),'-o','LineWidth',3);
title('Fase');
legend("C","MatLab");
xlim([floor(delay_N+1)*(1/960) inf]);

figure;
plot(mag_rep,'-o','LineWidth',3);
hold on
plot(mag_matlab,'-o','LineWidth',3);
title('Magnitude');
legend("C","MatLab");

%% TVE

fasor = downsample(fasor, 16);
TVE_cm = TVE_timestamp(fase_rep, mag_rep, fasor, 60, N, 65, timestamp);
TVE_matlab = TVE(fase_matlab, mag_matlab, fasor_dec, 960, 164);

figure;

lim_tve = ones([length(TVE_cm) 1])*tve_lim;
subplot(2,1,1);
plot(TVE_cm,'-o','LineWidth',3); hold on
plot(lim_tve,'LineWidth',3);
title("C");
xlim([fs/16 length(TVE_cm)-fs/16]);
ylim([0 tve_lim])
ylabel("TVE(%)");
legend("TVE","Limite");

lim_tve = ones([length(TVE_matlab) 1])*tve_lim;
subplot(2,1,2);
plot(TVE_matlab,'-o','LineWidth',3); hold on
plot(lim_tve,'LineWidth',3);
title("Matlab");
xlim([960 length(f_dec)-960]);
ylim([0 tve_lim])
xlabel("Amostra");
ylabel("TVE(%)");

%% FE 

freq_ref_60hz = downsample(f,16);

% freq_rep = (freq_rep(2:end) + freq_rep(1:end-1))/2;
% freq_rep = freq_rep(delay_SG_dec:end)
freq_rep = freq_rep(2:end);

tam_freq = min([length(freq_ref_60hz) length(freq_rep)]);
FE_rep = abs(freq_ref_60hz(1:tam_freq) - (60+freq_rep(1:tam_freq)))*1000;
FE_matlab = abs(f_dec(1:length(freq_matlab)) - (60+freq_matlab))*1000;

figure;

t = (0:length(FE_rep)-1)/60;

lim_fe = ones([length(FE_rep) 1])*fe_lim;
subplot(2,1,1);
plot(t,FE_rep,'-o','LineWidth',3); hold on
plot(t,lim_fe,'LineWidth',3);
title('C');
xlim([1 length(FE_rep)/60-1]);
ylim([0 fe_lim]);
ylabel("FE(mHz)");
legend("FE","Limite");

lim_fe = ones([length(FE_matlab) 1])*fe_lim;
subplot(2,1,2);
plot(FE_matlab,'-o','LineWidth',3); hold on
plot(lim_fe,'LineWidth',3);
title('Matlab');
xlim([960 length(f_dec)-960]);
ylim([0 fe_lim])
ylabel("FE(mHz)");
xlabel("Amostra");

%% ROCOF

file = sprintf('SinaisFrequencia/rocof_rep_%s0.txt',sTest);
rocof_rep = load(file);
rocof_rep = -rocof_rep(2:end,2)';

%rocof_rep = diff(freq_rep)/T;

rocof_matlab = diff(freq_matlab)*960;

tam_rocof = min([length(rocof_rep) length(freq_ref_60hz)]);
rocof_ref_60hz = diff(freq_ref_60hz(1:tam_rocof+1))*60;
RFE_cm = abs(rocof_ref_60hz - rocof_rep(1:tam_rocof));

rocof_ref = diff(f_dec(1:length(rocof_matlab)+1))*960;
RFE_matlab = abs(rocof_ref - rocof_matlab);

figure;

lim_rfe = ones([length(RFE_cm) 1])*rfe_lim;
subplot(2,1,1);
plot(RFE_cm,'-o','LineWidth',3); hold on
plot(lim_rfe,'LineWidth',3);
title('C');
xlim([60 length(RFE_cm)-60]);
ylim([0 rfe_lim])
ylabel("RFE(Hz/s)");
legend("RFE","Limite");

lim_rfe = ones([length(RFE_matlab) 1])*rfe_lim;
subplot(2,1,2);
plot(RFE_matlab,'-o','LineWidth',3); hold on
plot(lim_rfe,'LineWidth',3);
title('Matlab');
xlim([960 length(f_dec)-960]);
ylim([0 rfe_lim])
ylabel("RFE(Hz/s)");
xlabel("Amostra");


%% Resultados

max_TVE_rep = max(TVE_cm(60:length(TVE_cm)-60))
max_FE_rep = max(FE_rep(60:length(TVE_cm)-60))
max_RFE_rep = max(RFE_cm(60:length(TVE_cm)-60))

max_TVE_matlab = max(TVE_matlab(960:length(f_dec)-960))
max_FE_matlab = max(FE_matlab(960:length(f_dec)-960))
max_RFE_matlab = max(RFE_matlab(960:length(f_dec)-960))

% resultados = [max_TVE_cm max_FE_cm max_RFE_cm max_TVE_matlab max_FE_matlab max_RFE_matlab];
resultados = [max_TVE_rep max_FE_rep max_RFE_rep];


%% Response time 

if TEST == PHASE_STEP
    over_limit_phase = find(TVE_matlab(960:end-960) > 1);
    over_limit_phase_samples = max(over_limit_phase) - min(over_limit_phase);
    over_limit_phase_time = over_limit_phase_samples*(1/960)

    over_limit_freq = find(FE_matlab(960:end-960) > 0.005);
    over_limit_freq_samples = max(over_limit_freq) - min(over_limit_freq);
    over_limit_freq_time = over_limit_freq_samples*(1/960)

    over_limit_rocof = find(RFE_matlab(960:end-960) > 0.005);
    over_limit_rocof_samples = max(over_limit_rocof) - min(over_limit_rocof);
    over_limit_rocof_time = over_limit_rocof_samples*(1/960)
    
    over_limit_phase = find(TVE_cm(960:end-960) > 1);
    over_limit_phase_samples = max(over_limit_phase) - min(over_limit_phase);
    over_limit_phase_time_cm = over_limit_phase_samples*(1/960)

    over_limit_freq = find(FE_rep(960:end-960) > 0.005);
    over_limit_freq_samples = max(over_limit_freq) - min(over_limit_freq);
    over_limit_freq_time_cm = over_limit_freq_samples*(1/960)

    over_limit_rocof = find(RFE_cm(960:end-960) > 0.005);
    over_limit_rocof_samples = max(over_limit_rocof) - min(over_limit_rocof);
    over_limit_rocof_time_cm = over_limit_rocof_samples*(1/960)
end


T = 1/60;
t = (0:length(fasor)-1)*T;
fasor_fund = 1*exp(1i*2*(60)*pi.*t);
fase_ref = -unwrap((angle(fasor_fund) - angle(fasor)));
diff_fase = diff(fase_ref);
degrau = find(diff_fase == max(diff_fase));
mag_ref = abs(fasor)*sqrt(2)/2;

overshoot = (max(fase_rep(degrau+floor(delay_N)+1:end))/fase_ref(degrau+1) - 1)*100;


if TEST ~= PHASE_STEP
    if ruido 
        writematrix(resultados,'Resultados_decimacao.xls','Sheet',1,'Range',['C' num2str( 15 + TEST) ':E' num2str( 15 + TEST )]);
    else
        writematrix(resultados,'Resultados_decimacao.xls','Sheet',1,'Range',['C' num2str( 5 + TEST) ':E' num2str( 5 + TEST )]);
    end
else
    resultados = [ over_limit_phase_time_cm over_limit_freq_time_cm over_limit_rocof_time_cm overshoot];
    writematrix(resultados,'Resultados_decimacao.xls','Sheet',1,'Range',['C' num2str(14) ':F' num2str(14)]);
    
end

toc