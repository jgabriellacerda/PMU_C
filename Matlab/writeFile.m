function writeFile(file_name,data,TEST)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

if TEST ~= HARMONIC & TEST ~= FUND
    file = sprintf('Signals Data %dHz/database_%s.mat',15360,sTest);
    data = load(file);
    data = data.PSD;
    fasor_sigtest = data(3,:);
    signal = real(fasor_sigtest);

    sFile = sprintf('SinaisTeste/sinal_%s.txt',sTest);
    fileID = fopen(sFile,'w');
    formatSpec = '%.12f;0;0;0;0;0;0;0;\n';
    for i = 1:length(signal)
    fprintf(fileID,formatSpec,signal(i)*1000);
    end
    fclose(fileID);

else
    t_sigtest = (0:15360*12-1)*(1/15360); % 10 seconds
    theta = 0;
    fasor_sigtest = exp(1i*(2*pi*60*t_sigtest + theta)); %fundamental
    signal = real(fasor_sigtest); 

    sFile = sprintf('SinaisTeste/sinal_%s.txt',sTest);
    fileID = fopen(sFile,'w');
    formatSpec = '%.12f;0;0;0;0;0;0;0;\n';
    for i = 1:length(signal)
    fprintf(fileID,formatSpec,signal(i)*1000);
    end
    fclose(fileID);
end

