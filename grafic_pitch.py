import numpy as np
import matplotlib.pyplot as plt
file_in_1='pitch_db/train/rl002.f0ref'
file_in_2='pitch_db/train/rl002.f0' 

wavesurfer = np.loadtxt(file_in_1,skiprows=0)
estimacion = np.loadtxt(file_in_2,skiprows=0)

dm = 0.015
#Time vector
samples = []
for i in range(0,len(estimacion)):
    samples.append(i*dm)


plt.plot(samples,estimacion,'b',linewidth=1,label='Pitch detector')
plt.plot(samples,wavesurfer,'r',linewidth=1.5,label='Wavesurfer pitch detector')
plt.title('Pitch Estimation')
plt.xlabel('Time[s]')
plt.ylabel('Frequency[Hz]')
plt.xlim(0,1.24)
plt.legend(loc='upper right')
plt.show(block=True)