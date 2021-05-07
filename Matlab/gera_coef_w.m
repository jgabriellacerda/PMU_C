function [W,N]=gera_coef_w(N,fs,Fr)

% fs=1440;
% Rep_rate=60;
% N = 96; 
% Fr = 10.320;
% Fr = 18.960;

% h = hanning(N+1); 
h = hamming(N+1); 
% h = kaiser(N+1);
k = (-N/2):(N/2);


W = (((sin(2*pi*(2*Fr/fs)*k)))./(2*pi*(2*Fr/fs)*k)).*h';

W((N/2)+1) = 1;

% figure
% plot(W,'-*')
% grid on