import matplotlib.pyplot as plt
import numpy as np

IA =[]
IB =[]
IC =[]
IN =[]
VA =[]
VB =[]
VC =[]
VN =[]
file = open('sinais.txt', 'r')
for line in file:
    line.replace('\n',' ')
    aux = line.split(';')
    IA.append(float(aux[0])*0.001)
    IB.append(float(aux[1])*0.001)
    IC.append(float(aux[2])*0.001)
    IN.append(float(aux[3])*0.001)
    VA.append(float(aux[4])*0.01)
    VB.append(float(aux[5])*0.01)
    VC.append(float(aux[6])*0.01)
    VN.append(float(aux[7])*0.01)
file.close()

THDinst_IA =[]
THDinst_IB =[]
THDinst_IC =[]
THDinst_IN =[]
THDinst_VA =[]
THDinst_VB =[]
THDinst_VC =[]
THDinst_VN =[]
file = open('THDinsts.txt', 'r')
for line in file:
    line.replace('\n',' ')
    aux = line.split(';')
    THDinst_IA.append(float(aux[0])*100)
    THDinst_IB.append(float(aux[1])*100)
    THDinst_IC.append(float(aux[2])*100)
    THDinst_IN.append(float(aux[3])*100)
    THDinst_VA.append(float(aux[4])*100)
    THDinst_VB.append(float(aux[5])*100)
    THDinst_VC.append(float(aux[6])*100)
    THDinst_VN.append(float(aux[7])*100)
file.close()

F_IA =[]
F_IB =[]
F_IC =[]
F_IN =[]
F_VA =[]
F_VB =[]
F_VC =[]
F_VN =[]
file = open('Freqs.txt', 'r')
for line in file:
    line.replace('\n',' ')
    aux = line.split(';')
    F_IA.append(float(aux[0]))
    F_IB.append(float(aux[1]))
    F_IC.append(float(aux[2]))
    F_IN.append(float(aux[3]))
    F_VA.append(float(aux[4]))
    F_VB.append(float(aux[5]))
    F_VC.append(float(aux[6]))
    F_VN.append(float(aux[7]))
file.close()

ciclo_ini = 150
Nppc = 256

# Plot das Estimações de Frequência para as correntes
f1 = plt.figure()
plt.suptitle('Estimação Frequência - Correntes')
plt.subplot(211)
plt.plot(IA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(IB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(IC[ciclo_ini*Nppc:-1], label = 'Fase C')
plt.axis([0, len(IA[ciclo_ini*Nppc:-1]), 1.1 * np.min(IA), 1.1 * np.max(IA)])
plt.legend(loc='upper right')
plt.ylabel('Corrente (A)')
plt.xlabel('Amostras')
plt.subplot(212)
plt.plot(F_IA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(F_IB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(F_IC[ciclo_ini*Nppc:-1], label = 'Fase C')
#plt.axis([0, len(IA[ciclo_ini*Nppc:-1]), 55, 65])
plt.legend(loc='lower right')
plt.ylabel('Frequência (Hz)')
plt.xlabel('Amostras')


# Plot das Estimações de Frequência para as Tensões
f2 = plt.figure()
plt.suptitle('Estimação Frequência - Tensões')
plt.subplot(211)
plt.plot(VA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(VB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(VC[ciclo_ini*Nppc:-1], label = 'Fase C')
plt.axis([0, len(VA[ciclo_ini*Nppc:-1]), 1.1 * np.min(VA), 1.1 * np.max(VA)])
plt.legend(loc='upper right')
plt.ylabel('Tensão (V)')
plt.xlabel('Amostras')
plt.subplot(212)
plt.plot(F_VA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(F_VB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(F_VC[ciclo_ini*Nppc:-1], label = 'Fase C')
#plt.axis([0, len(IA[ciclo_ini*Nppc:-1]), 55, 65])
plt.legend(loc='lower right')
plt.ylabel('Frequência (Hz)')
plt.xlabel('Amostras')


# Plot das THDs Instantâneas para as correntes
f3 = plt.figure()
plt.suptitle('RMS Instantâneo - Correntes')
plt.subplot(211)
plt.plot(IA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(IB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(IC[ciclo_ini*Nppc:-1], label = 'Fase C')
#plt.axis([0, len(IA[ciclo_ini*Nppc:-1]), 1.1 * np.min(IA), 1.1 * np.max(IA)])
plt.legend(loc='upper right')
plt.ylabel('Corrente (A)')
plt.xlabel('Amostras')
plt.subplot(212)
plt.plot(THDinst_IA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(THDinst_IB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(THDinst_IC[ciclo_ini*Nppc:-1], label = 'Fase C')
#plt.axis([0, len(IA[ciclo_ini*Nppc:-1]), 0, 1.1 * np.max(THDinst_IA)])
plt.legend(loc='upper right')
plt.ylabel('RMS (V)')
plt.xlabel('Amostras')


# Plot das THDs Instantâneas para as Tensões
f4 = plt.figure()
plt.suptitle('RMS Instantâneo - Tensões')
plt.subplot(211)
plt.plot(VA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(VB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(VC[ciclo_ini*Nppc:-1], label = 'Fase C')
#plt.axis([0, len(VA[ciclo_ini*Nppc:-1]), 1.1 * np.min(VA), 1.1 * np.max(VA)])
plt.legend(loc='upper right')
plt.ylabel('Tensão (V)')
plt.xlabel('Amostras')
plt.subplot(212)
plt.plot(THDinst_VA[ciclo_ini*Nppc:-1], label = 'Fase A')
plt.plot(THDinst_VB[ciclo_ini*Nppc:-1], label = 'Fase B')
plt.plot(THDinst_VC[ciclo_ini*Nppc:-1], label = 'Fase C')
#plt.axis([0, len(IA[ciclo_ini*Nppc:-1]), 0, 1.1 * np.max(THDinst_VA)])
plt.legend(loc='lower right')
plt.ylabel('THD (%)')
plt.xlabel('Amostras')
plt.show()
