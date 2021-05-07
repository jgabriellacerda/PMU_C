function [TVE] = TVE(fase, magnitude, fasor_ref, fs, N)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    
    T = 1/fs;
    t = (0:length(fase)-1)*T;
    fasor_fund = 1*exp(1i*2*(60)*pi.*t);
    fasor_fund = fasor_fund(1:length(fase));
    fasor_ref = fasor_ref(1:length(fase));

    delay = floor(N/2);

    re = cos(fase).*magnitude;
    re = re(delay+1:end);
    im = sin(fase).*magnitude;
    im = im(delay+1:end);
    
    ang_ref = (angle(fasor_fund) - angle(fasor_ref));
    mag_ref = abs(fasor_ref)*sqrt(2)/2;
    Xr = cos(ang_ref).*mag_ref;
    Xr = Xr(1:end-delay);
%     Xi = imag(fasor_ref);
    Xi = -sin(ang_ref).*mag_ref;
    Xi = Xi(1:end-delay);
    
     figure;
     plot(re,'-o'); hold on
     plot(Xr,'-o');
     legend("Estimado","Referencia");
     title("Parte Real Fasores");
     
     figure;
     plot(im,'-o'); hold on
     plot(Xi,'-o');
     legend("Estimado","Referencia");
     title("Parte Imagin�ria Fasores");
    
    TVE = zeros([1 length(Xr)]);
    for n = 1:length(Xr)
        TVE(n) = sqrt( ((re(n)-Xr(n))^2 + (im(n)-Xi(n))^2) / (Xr(n)^2 + Xi(n)^2) ) * 100;
    end

end

