function [freq_filt,janela,N_f] = MAF_Variavel(Freq,janela_frac,T,nppc)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

l = 1;

tam = length(Freq(1,:));
freq_filt = zeros([l,tam]);
freq_aux = zeros([l,tam]);
T_freq = zeros([l,tam]);
N_f = zeros([l,tam]);
N_int = zeros([l,tam]);
janela = zeros([l,tam]);
precision = zeros([l,tam]);
N_MM = [floor(nppc/16*15) nppc floor(nppc/16*17)];
k0 = ones([1 3]);
soma = zeros([1 3]);
N_MM_max = max(N_MM);
buffMM = zeros([1 N_MM_max]);
pos_sub = zeros([1 3]);
Freq_MM = zeros([3 tam]);



for c = 2:tam
    freq_aux(l,c) = (60-Freq(l,c-1));
%         freq_aux(l,c) = (60-freq_filt(l,c-1));
    T_freq(l,c) = 1/freq_aux(l,c); % periodo de um ciclo da frequencia estimada
    N_f(l,c) = T_freq(l,c)/T;               % numero de amostras referente ao periodo
    N_int(l,c) = round(N_f(l,c));           % arredonda para o inteiro mais proximo
%         N_int(l-2,c) = 2*round(N_f(l-2,c)/2);  %apenas ordens par

    % Apenas 3 filtros 
    N_int(l,c) = round(round(N_int(l,c)*(15/nppc))*(nppc/15));

    %N_int(i) = 12;

    precision(l,c) = eps(T_freq(l,c));

    if janela_frac
        janela(l,c) = N_f(l,c);
        Lf = N_f(l,c);  % Tamanho fracionario de janela
        n = c;

        L = floor(abs(Lf));
        Lfrac = Lf - L;  % Parte fracionaria do tamanho da janela

        if n <= L+1
            soma(1) = sum(Freq(l,1:n));
        else
            if n - L + 1 < length(Freq(1,:))
              soma(1) = sum(Freq(l,n-L+1:n));
              x_Lf = Freq(l,n-L+1) - Lfrac*(Freq(l,n-L+1) - Freq(l,n-L)); % Valor interpolado
              soma(1) = soma(1) + x_Lf*Lfrac; % Soma valor interpolado
              amostras_frac(l,n) = x_Lf;      
              tfrac(l,n) = n - Lf+1;
            end                
        end

        freq_filt(l,c) = soma(1)/Lf;
    else
        for n = 1:3
            pos_sub(n) = k0(n) - N_MM(n) + 1;
            if pos_sub(n) < 1
                pos_sub(n) = pos_sub(n) + N_MM_max;
            end
            soma(n) = soma(n) - buffMM(pos_sub(n));
            k0(n) = k0(n) + 1;
            if k0(n) > N_MM_max
                k0(n) = k0(n) - N_MM_max;
            end
            soma(n) = soma(n) + Freq(l,c);
            Freq_MM(n,c) = soma(n)/N_MM(n);

            if N_int(l,c) == N_MM(n)
                freq_filt(l,c) = Freq_MM(n,c);
            end

        end
        buffMM(k0(1)) = Freq(l,c);



        janela(l,c) = N_int(l,c);
%             if N_int(l,c) <= c
%                 freq_filt(l,c) = sum(Freq(l,c-N_int(l,c)+1:c))/N_int(l,c);
%             else
%                 freq_filt(l,c) = sum(Freq(l,1:c))/c;
%             end
    end
end


% if janela_frac
%     figure;
%     plot(Freq(1,:),'-o');
%     hold on
%     plot(tfrac(1,:),amostras_frac(1,:),'o');
%     title("Amostras Fracion�rias");
% end

end

