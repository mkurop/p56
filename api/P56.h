/*
 * P56.h
 *
 *  Created on: 30 maj 2017
 *      Author: marcin
 */

#ifndef P56_H_
#define P56_H_

#define BOOST_LOG_DYN_LINK 1

#include <asl_P56.h>
#include <iostream>

using namespace std;
//! Interface for computation of P56 activ factor and active RMS energy
namespace t2r {
class P56 {

  double samplingRateInHz; ///< sampling rate in [Hz]
  double nBits; /*< number of bits per sample */
  double af = 0; /*< active speech factor 0..1 (fraction of speech file containing active speech) */
  double lev = 0; /*< active speech RMS energy */
  double c0 = 0;

  emxArray_real_T *createEMXArray(float *speechSamples, int fileLenInSamples);

 public:
  /**
   * Constructor of the P56 class
   * @param [in] samplingRateInHz sampling rate of the input file (defaults to 8kHz)
   * @param [in] nBits number of bits per sample
   */
  P56(double samplingRateInHz = 8000.0, double nBits = 16.0) : samplingRateInHz(samplingRateInHz), nBits(nBits) {};
  virtual ~P56();
  /**
   * Computes and stores active level and factor
   * @param [in] speechSamples speech samples pointer (raw float)
   * @param [in] fileLenInSamples number of samples pointed by speechSamples
   */
  void compute(float *speechSamples, int fileLenInSamples);

  /**
   * \brief get active RMS level (liner scale not dB)
   * @return RMS level
   */
  double getLev() { return lev; };

  /**
   * \brief get active factor
   * @return percentage of active speech in the file (0..1)
   */
  double getAf() { return af; };

};
}

#endif /* P56_H_ */
