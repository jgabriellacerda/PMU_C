function [fase,magnitude,re,im,N,W] = DFT(sinal, fs, N, Fr)
    %UNTITLED Summary of this function goes here
    %   Detailed explanation goes here

    dt = 1/fs; %intervalo de tempo entre as amostras
    w0 = 2*pi*60;   
    
    W = [];
    [W,N] = gera_coef_w(N,fs,Fr);
    Gain = sqrt(2)/sum(W);   
%     W = W*Gain;



    for pp = 1:length(sinal(1,:))

        x = sinal(:,pp);

        jj=1;

        bufS = zeros((N+1),1);
        bufC = zeros((N+1),1);
        k=1;

        l = length(x);
        for ii=1:l

            bufC(k) = x(ii)*cos((ii-1)*w0*dt);
            bufS(k) = x(ii)*sin((ii-1)*w0*dt);
            

            re(ii,pp)=0;
            im(ii,pp)=0;
           
            
            for jj=1:(N+1)

                re(ii,pp) = re(ii,pp) + bufC(k)*W(jj);
                im(ii,pp) = im(ii,pp) + bufS(k)*W(jj);

                k=k-1;
                if k < 1
                    k = k + (N+1);
                end
            end  
            re(ii,pp)=re(ii,pp)*Gain;
            im(ii,pp)=-im(ii,pp)*Gain;

            k = mod(k,N+1)+1;
%             k = mod(k+1,N+1)
    %         k=k+1;
    %         if k > (N+1)
    %             k = k - (N+1);
    %         end

            magnitude(ii,pp) = sqrt(re(ii,pp)*re(ii,pp)+im(ii,pp)*im(ii,pp));
            fase(ii,pp) = atan2(im(ii,pp),re(ii,pp));%*180/pi;

        end
    end
    
end

