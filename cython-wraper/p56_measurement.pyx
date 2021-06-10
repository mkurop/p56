import numpy as np
cimport numpy as np

cdef extern from "P56.h" namespace "t2r":

    cdef cppclass P56:

        double samplingRateInHz;
        double nBits;
        double af;
        double lev0;
        double c0;
        P56(double samplingRateInHz, double nBits)
        void compute(float *speechSamples, int FileLenInSamples)
        double getLev()
        double getAf()

cdef class myP56:
    cdef P56 *pclass
    def __cinit__(self, double sampling_rate, double n_bits):
        self.pclass = new P56(sampling_rate, n_bits)

    def __dealloc__(self):
        if self.pclass != NULL:
            del self.pclass

    cdef double getLev(self):
        return self.pclass.getLev()

    cdef double getAf(self):
        return self.pclass.getAf()

    cdef void compute(self, float *speechSamples, int fileLenInSamples):
        self.pclass.compute(speechSamples, fileLenInSamples)

def get(np.ndarray[np.float32_t, ndim=1] speech_signal, double sampling_rate = 16000, double n_bits = 16):

    speech_signal = np.ascontiguousarray(speech_signal)

    p56_ = myP56(sampling_rate, n_bits)

    p56_.compute(&speech_signal[0], speech_signal.shape[0])

    return p56_.getLev(), p56_.getAf()
