import sys
sys.path.append("/home/src/p56/p56/")
import p56.p56_measurement
#  from p56.p56_measurement  import p56
import numpy as np
from scipy.io import wavfile
from typing import Tuple
import os

def read_wav_and_normalize(file_ : str) -> Tuple[np.ndarray,int]:

    if not os.path.exists(file_):
        raise ValueError(f"The file {file_} does not exist.")

    sr, s = wavfile.read(file_)

    s = s/2.**15
    

    np.random.seed(1000) # causes the dither is same on each run

    s += np.random.randn(*s.shape)*1.e-6 # add dither to improve numerical behaviour

    return np.float32(s), int(sr)

if __name__ == "__main__":

    clean_speech, clean_speech_sampling_frequency = read_wav_and_normalize("../data/speech.wav")

    lev, af = p56.p56_measurement.get(clean_speech, sampling_rate = clean_speech_sampling_frequency, n_bits = 16)
    print(f"{lev}, {af}")
