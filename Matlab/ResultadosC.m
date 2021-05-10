clear all
close all
clc 

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

%  file = sprintf('Signals Data %dHz/database_%s.mat',15360,sTest);
%  data = load(file);
%  data = data.PSD;
%  fasor_sigtest = data(3,:);
%  signal = real(fasor_sigtest);
%
%  sFile = sprintf('SinaisTeste/sinal_%s.txt',sTest);
%  fileID = fopen(sFile,'w');
%  formatSpec = '%.12f;0;0;0;0;0;0;0;\n';
%  for i = 1:length(signal)
%      fprintf(fileID,formatSpec,signal(i)*1000);
%  end
%  fclose(fileID);
%
%else
%  t_sigtest = (0:15360*12-1)*(1/15360); % 10 seconds
%  theta = 0;
%  fasor_sigtest = exp(1i*(2*pi*60*t_sigtest + theta)); %fundamental
%  signal = real(fasor_sigtest); 
% 
%  sFile = sprintf('SinaisTeste/sinal_%s.txt',sTest);
%  fileID = fopen(sFile,'w');
%  formatSpec = '%.12f;0;0;0;0;0;0;0;\n';
%  for i = 1:length(signal)
%      fprintf(fileID,formatSpec,signal(i)*1000);
%  end
%  fclose(fileID); 
end

%% DFT

file = sprintf('SinaisFaseMagC/fase_c_%s0.txt',sTest);
fase_c = load(file);
fase_c = fase_c(1:end);

file = sprintf('SinaisFaseMagC/mag_c_%s0.txt',sTest);
mag_c = load(file);
mag_c = mag_c(1:end);

file = sprintf('SinaisFaseMagMatlab/fase_dec_matlab_%s.txt',sTest);
fase_matlab = load(file);

file = sprintf('SinaisFaseMagMatlab/mag_dec_matlab_%s.txt',sTest);
mag_matlab = load(file);

% valores certos
coef_a = -0.007332419963127;
coef_b = -0.436483107452006;

% y = a*x + b
% x = freq - 60
f = f(1:length(fase_c));
%fase_cm = fase_cm - (coef_a*(f-60)' + coef_b);

%[fase_dec,mag_dec,~,~,~,~] = DFT(sig_dec', 960, 164, Fr);


%% Estima��o de frequ�ncia

delay_N = (N+1)/2;

[freq_cm,legs,delay_SG] = FreqSG(unwrap(fase_c),fs);
corr_cm = (coef_a*(-freq_cm(1,1:length(fase_c)))' + coef_b);

[freq_matlab,legs,delay_SG_dec] = FreqSG(unwrap(fase_matlab),960);
corr_matlab = (coef_a*(-freq_matlab(1,1:length(fase_matlab)))' + coef_b);

corr_ideal = (coef_a*(f-60)' + coef_b);

% fase_c = fase_c - corr_cm;
fase_matlab = fase_matlab - corr_matlab;

figure;
plot(corr_cm,'-o');
hold on
plot(corr_ideal,'-o');


% corr = (coef_a.*-freq_matlab(2,1:end-16) + coef_b)';

%freq_dec = freq_dec(2:end);

delay_N_dec = 165/2;


%fase_dec = (fase_dec - corr);

%% Filtro Media-Movel de ordem variavel

janela_frac = true;
[freq_cm,janela] = MAF_Variavel(freq_cm,janela_frac,T,nppc);
freq_cm = -freq_cm;

[freq_matlab,janela] = MAF_Variavel(freq_matlab,janela_frac,1/960,16);
freq_matlab = -freq_matlab;

delay_mm = nppc/2;
delay_f = floor(delay_N + delay_SG + delay_mm);
freq_cm = freq_cm(delay_f+1:end);

delay_mm_dec = 16/2;
delay_f_dec = floor(delay_N_dec + delay_SG_dec + delay_mm_dec);
freq_matlab = freq_matlab(delay_f_dec+1:end);

%janela = janela(:,1:length(f));

%% Plots

T = 1/fs;
t = (0:length(fasor)-1)*T;
fasor_fund = 1*exp(1i*2*(60)*pi.*t);
ang_ref = (angle(fasor_fund) - angle(fasor));

figure;
plot(unwrap(fase_c(floor(delay_N+1):end)),'-o','LineWidth',3);
hold on
plot(unwrap(fase_matlab(floor(delay_N+1):end)),'-o','LineWidth',3);
plot(-unwrap(ang_ref),'-o','LineWidth',3);
title('Fase');
legend("C","MatLab");

figure;
plot(mag_c,'-o','LineWidth',3);
hold on
plot(mag_matlab,'-o','LineWidth',3);
title('Magnitude');
legend("C","MatLab");

%% TVE

TVE_cm = TVE(fase_c, mag_c, fasor, fs, N);
TVE_matlab = TVE(fase_matlab, mag_matlab, fasor_dec, 960, 164);

figure;

lim_tve = ones([length(TVE_cm) 1])*tve_lim;
subplot(2,1,1);
plot(TVE_cm,'-o','LineWidth',3); hold on
plot(lim_tve,'LineWidth',3);
title("C");
xlim([fs length(f)-fs]);
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

FE_cm = abs(f(1:length(freq_cm)) - (60+freq_cm))*1000;
FE_matlab = abs(f_dec(1:length(freq_matlab)) - (60+freq_matlab))*1000;

figure;

lim_fe = ones([length(FE_cm) 1])*fe_lim;
subplot(2,1,1);
plot(FE_cm,'-o','LineWidth',3); hold on
plot(lim_fe,'LineWidth',3);
title('C');
xlim([fs length(f)-fs]);
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

rocof_cm = diff(freq_cm)/T;

rocof_matlab = diff(freq_matlab)*960;

RFE_cm = abs(diff(f(1:length(rocof_cm)+1))/T - rocof_cm);

RFE_matlab = abs(diff(f_dec(1:length(rocof_matlab)+1))*960 - rocof_matlab);

figure;

lim_rfe = ones([length(RFE_cm) 1])*rfe_lim;
subplot(2,1,1);
plot(RFE_cm,'-o','LineWidth',3); hold on
plot(lim_rfe,'LineWidth',3);
title('C');
xlim([fs length(f)-fs]);
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

max_TVE_cm = max(TVE_cm(fs:length(f)-fs))
max_FE_cm = max(FE_cm(fs:length(f)-fs))
max_RFE_cm = max(RFE_cm(fs:length(f)-fs))

max_TVE_matlab = max(TVE_matlab(960:length(f_dec)-960))
max_FE_matlab = max(FE_matlab(960:length(f_dec)-960))
max_RFE_matlab = max(RFE_matlab(960:length(f_dec)-960))

% resultados = [max_TVE_cm max_FE_cm max_RFE_cm max_TVE_matlab max_FE_matlab max_RFE_matlab];
resultados = [max_TVE_cm max_FE_cm max_RFE_cm];


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

    over_limit_freq = find(FE_cm(960:end-960) > 0.005);
    over_limit_freq_samples = max(over_limit_freq) - min(over_limit_freq);
    over_limit_freq_time_cm = over_limit_freq_samples*(1/960)

    over_limit_rocof = find(RFE_cm(960:end-960) > 0.005);
    over_limit_rocof_samples = max(over_limit_rocof) - min(over_limit_rocof);
    over_limit_rocof_time_cm = over_limit_rocof_samples*(1/960)
end



fase_ref = -unwrap((angle(fasor_fund) - angle(fasor)));
diff_fase = diff(fase_ref);
degrau = find(diff_fase == max(diff_fase));
mag_ref = abs(fasor)*sqrt(2)/2;

overshoot = (max(fase_c(degrau+floor(delay_N)+1:end))/fase_ref(degrau+1) - 1)*100;


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

buff = []
offset = 0;
diff_fase = 0;
for i = 1:length(fase_c)
    offset = 0;
   if i > 17
       buff(17) = fase_c(i);
      for j = 0:15
          k = i - j;
          diff_fase = fase_c(k) - fase_c(k-1);
          if diff_fase > pi
              offset = offset + 2*pi;
          elseif diff_fase < -pi
              offset = offset - 2*pi;
          end
          buff(17-j-1) = fase_c(k-1) + offset;
      end
      fase_filt(i) = sum(buff) / 17;
%       buff
   end
end

buff = zeros([1 17]);
buff_unwrap = zeros([1 17]);
offset = 0;
diff_fase = 0;
cont_unwrap = 0;
for i = 1:length(fase_c)
   if i > 17
       buff = fase_c(i-17+1:i);
      diff_fase = buff(17) - buff(16);
      if diff_fase > pi
          cont_unwrap = 0;
          offset = offset + 2*pi;
      elseif diff_fase < -pi
          cont_unwrap = 0;
          offset = offset - 2*pi;
      else
         cont_unwrap = cont_unwrap + 1; 
      end
      buff_unwrap(1:16) = buff_unwrap(2:17);
      buff_unwrap(17) = fase_c(i) - offset;
      
      if cont_unwrap > 17
          offset = 0;
          buff_unwrap = buff;
      end

      fase_filt2(i) = sum(buff_unwrap) / 17;
   end
end

figure;
plot(mod(fase_filt2,pi),'-o');
hold on
plot(mod(fase_c,pi),'-o');

toc