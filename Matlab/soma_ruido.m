function [y] = soma_ruido(v,a,SNRdb)
    
    rng(1);
    
    % Geraçao do ruido 
    Ps=(a^2)/2;                             %a = amplitude da fundamental
    Pr=Ps/(10^(SNRdb/10));                 % Pr =  potencia do ruido 
    desvio=sqrt(Pr);
    R = normrnd(0,desvio,1,length(v));        %ruido
    R=R-mean(R);
    y=v+R;

end