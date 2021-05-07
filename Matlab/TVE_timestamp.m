function [TVE] = TVE(fase, magnitude, fasor_ref, fs, N, f_in, timestamp)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here


    T = 1/fs;
    t = (0:length(fasor_ref)-1)*T;
    fasor_fund = 1*exp(1i*2*(60)*pi.*t);
    
    timestamp_ref = (0:length(fasor_ref)-1);

    delay = floor(N/2);

    re = cos(fase).*magnitude;
%     re = re(delay+1:end);
    im = sin(fase).*magnitude;
%     im = im(delay+1:end);
    
    tam = length(re);
    
    ang_ref = (angle(fasor_fund) - angle(fasor_ref));
    mag_ref = abs(fasor_ref)*sqrt(2)/2;
    Xr = cos(ang_ref).*mag_ref;
%     Xr = Xr(1:end-delay);
%     Xi = imag(fasor_ref);
    Xi = -sin(ang_ref).*mag_ref;
%     Xi = Xi(1:end-delay);
    
    if f_in == 65
%     figure;
%     plot(-unwrap(ang_ref),'-o');
%     hold on
%     plot(unwrap(fase(delay+1:end)),'-o');
%     
%     figure;
%     plot(mag_ref,'-o');
%     hold on
%     plot(magnitude(delay+1:end),'-o');
    
        figure;
        plot(timestamp,re,'-o'); hold on
        plot(timestamp_ref,Xr,'-o');
    %     plot(Xr' - re,'-o');
    %     plot(mag_ref'-magnitude,'-o');
        legend("Estimado","Referencia");
        title("Parte Real Fasores");

        figure;
        plot(timestamp,im,'-o'); hold on
        plot(timestamp_ref,Xi,'-o');
    %     plot(unwrap(ang_ref(1:end-delay))'+unwrap(fase(delay+1:end)),'-o');
        legend("Estimado","Referencia");
        title("Parte Imaginária Fasores");
    end
    
    TVE = zeros([1 length(Xr)]);
    for n = 1:tam
        if timestamp(n) >= 0
            n_ref = find(timestamp_ref == timestamp(n));
            TVE(n) = sqrt( ((re(n)-Xr(n_ref))^2 + (im(n)-Xi(n_ref))^2) / (Xr(n_ref)^2 + Xi(n_ref)^2) ) * 100;
        end
    end

end

