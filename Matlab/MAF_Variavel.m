function [freq_filt,janela,N_f,Freq_MM,Lint,N_MM] = MAF_Variavel(Freq,janela_frac,T,nppc,mm_variavel,mm_recursivo)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

n_sinais = length(Freq(:,1));

tam = length(Freq(1,:));
freq_filt = zeros([n_sinais,tam]);
freq_aux = zeros([n_sinais,tam]);
T_freq = zeros([n_sinais,tam]);
N_f = zeros([n_sinais,tam]);
Lint = zeros([n_sinais,tam]);
janela = zeros([n_sinais,tam]);
precision = zeros([n_sinais,tam]);
k0 = 1;
soma = zeros([1 3]);

pos_sub = zeros([1 3]);
Freq_MM = zeros([3 tam]);
Freq_rec = zeros([1 tam]);

N_MM_MIN = 14;
N_MM_MAX = 18;

if mm_variavel
    N_MM = N_MM_MIN:N_MM_MAX;
else
    N_MM = nppc;
end

% N_MM_max = max(N_MM);
% N_MM_min = min(N_MM);
buffMM = zeros([1 N_MM_MAX]);

Lint(1) = nppc;

soma_N14 = 0;
soma_N15 = 0;
soma_N16 = 0;
soma_N17 = 0;

for l = 1:n_sinais
    for n = 2:tam
        freq_aux(l,n) = (60-Freq(l,n-1));
%         freq_aux(l,c) = (60-freq_filt(l,c-1));
        T_freq(l,n) = 1/freq_aux(l,n); % periodo de um ciclo da frequencia estimada
        N_f(l,n) = T_freq(l,n)/T;               % numero de amostras referente ao periodo
        
        if N_f(l,n) < N_MM_MIN
            N_f(l,n) = N_MM_MIN;
        elseif N_f(l,n) >= N_MM_MAX
            N_f(l,n) = N_MM_MAX*0.999;
        end
        
        Lint(l,n) = floor(N_f(l,n));           % arredonda para o inteiro mais proximo
        
        k0 = k0 + 1;
        if k0 > N_MM_MAX
            k0 = k0 - N_MM_MAX;
        end
        
        if janela_frac
            
            amostra = Freq(l,n);
            janela(l,n) = N_f(l,n);
            Nf = N_f(l,n);
            
            L = floor(Nf);
            Nfrac = Nf - L;
                
            k_L_1 = k0-L+1;
            if k_L_1 < 1
                k_L_1 = k_L_1 + N_MM_MAX;
            end

            k_L = k0-L;
            if k_L < 1
                k_L = k_L + N_MM_MAX;
            end

            amostra_interp = buffMM(k_L_1) - Nfrac*(buffMM(k_L_1) - buffMM(k_L));

            pos_sub_N14 = k0-14;
            if pos_sub_N14 < 1 
                pos_sub_N14 = pos_sub_N14 + N_MM_MAX;
            end
            
            pos_sub_N15 = k0-15;
            if pos_sub_N15 < 1 
                pos_sub_N15 = pos_sub_N15 + N_MM_MAX;
            end

            pos_sub_N16 = k0-16;
            if pos_sub_N16 < 1 
                pos_sub_N16 = pos_sub_N16 + N_MM_MAX;
            end

            pos_sub_N17 = k0-17;
            if pos_sub_N17 < 1 
                pos_sub_N17 = pos_sub_N17 + N_MM_MAX;
            end

            soma_N14 = soma_N14 + (amostra - buffMM(pos_sub_N14));
            soma_N15 = soma_N15 + (amostra - buffMM(pos_sub_N15));
            soma_N16 = soma_N16 + (amostra - buffMM(pos_sub_N16));
            soma_N17 = soma_N17 + (amostra - buffMM(pos_sub_N17));

            switch L
                case 14
                    saida = (soma_N14 + Nfrac*amostra_interp)/Nf;                                 
                case 15
                    saida = (soma_N15 + Nfrac*amostra_interp)/Nf;                        
                case 16
                    saida = (soma_N16 + Nfrac*amostra_interp)/Nf;
                case 17
                    saida = (soma_N17 + Nfrac*amostra_interp)/Nf;
            end
                
            if n <= L+1
                soma(1) = sum(Freq(l,1:n));
                x_Lf = 0;
            else
                soma(1) = sum(Freq(l,n-L+1:n));
                x_Lf = Freq(l,n-L+1) - Nfrac*(Freq(l,n-L+1) - Freq(l,n-L));
            end
            soma(1) = soma(1) + x_Lf*Nfrac;
            
            amostras_frac(l,n) = x_Lf;
            amostras_frac(l,n) = amostra_interp;
            tfrac(l,n) = n - Nf+1;
            
%             freq_filt(l,n) = saida;
            freq_filt(l,n) = soma(1)/Nf;
        else
            %N_int(l,c) = 8;
            
            for nmm = 1:length(N_MM)
                pos_sub(nmm) = k0 - N_MM(nmm) + 1;
                if pos_sub(nmm) < 1
                    pos_sub(nmm) = pos_sub(nmm) + N_MM_MAX;
                end
                soma(nmm) = soma(nmm) - buffMM(pos_sub(nmm));
                soma(nmm) = soma(nmm) + Freq(l,n);
                
%                 Freq_MM(nmm,c) = soma(nmm)/N_MM(nmm);
                Freq_MM(nmm,n) = Freq_MM(nmm,n-1) + (Freq(l,n) - buffMM(pos_sub(nmm)))/N_MM(nmm);
                
                if Lint(l,n) == N_MM(nmm)
                    freq_filt(l,n) = Freq_MM(nmm,n);
                end
                    
            end
            
            if mm_recursivo == true
                pos_sub_rec = k0 - Lint(l,n) + 1;
                if pos_sub_rec < 1
                    pos_sub_rec = pos_sub_rec + N_MM_MAX;
                end

                Freq_rec(l,n) = Freq_rec(l,n-1) + (Freq(l,n) - buffMM(pos_sub_rec))/Lint(l,n);

                freq_filt(l,n) = Freq_rec(l,n);
            end
            

            

            
            janela(l,n) = Lint(l,n);
%             if L(l,c) <= c
%                 freq_filt(l,c) = sum(Freq(l,c-L(l,c)+1:c))/L(l,c);
%             else
%                 freq_filt(l,c) = sum(Freq(l,1:c))/c;
%             end
        end

        buffMM(k0) = Freq(l,n);
    end
end

if janela_frac
    figure;
    plot(Freq(1,:)+60,'-o','LineWidth',1.5);
    hold on
    plot(tfrac(1,:),amostras_frac(1,:)+60,'o','LineWidth',1.5);
    title("Interpolação de amostras");
    xlabel("Amostra");
    ylabel("Frequência Estimada");
    legend("Frequência Estimada","Amostras interpoladas");
    xlim([1000 1200]);
    
end

end

