import numpy as np
import soundfile as sf
import matplotlib.pyplot as plt
import scipy.signal as sig
file_in='pitch_db/train/rl002.wav'
x,fm=sf.read(file_in)

samples = []
for i in range(0,len(x)):
    samples.append(i/fm)

autocorrelation=np.correlate(x,x,"same")
m = np.arange(len(autocorrelation))
peaks = sig.find_peaks(autocorrelation)
[a1,a2]=np.split(autocorrelation,2)

plt.subplot(2,1,1)
plt.plot(samples,x,linewidth=0.5)
plt.title('Voiced frame')
plt.grid(True)
plt.xlabel('Time[s]')
plt.ylabel('Waveform')
plt.xlim(0.35,0.38)
plt.subplot(2,1,2)
plt.plot(a2,linewidth=0.5)
plt.xlabel('Samples')
plt.ylabel('Autocorrelation')
plt.xlim(0,200)
plt.grid(True)
plt.show(block=True)