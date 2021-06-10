/*
 * P56.cpp
 *
 *  Created on: 30 maj 2017
 *      Author: marcin
 */

#include <asl_P56_emxAPI.h>
#include <P56.h>

using namespace std;

t2r::P56::~P56() {
  // TODO Auto-generated destructor stub
}

emxArray_real_T *t2r::P56::createEMXArray(float *speechSamples, int fileLenInSamples) {

  emxArray_real_T *x;

  int size[] = {1, fileLenInSamples};

  x = emxCreateND_real_T(2, size);

  x->canFreeData = true;

  // convert locally to double
  for (int i = 0; i < fileLenInSamples; i++) {
    x->data[i] = (double) speechSamples[i];
  }

  x->numDimensions = 2;
  x->allocatedSize = fileLenInSamples;

  x->size = new int[2];
  x->size[0] = 1;
  x->size[1] = fileLenInSamples;

  return x;

}

void t2r::P56::compute(float *speechSamples, int fileLenInSamples) {

  emxArray_real_T *speech;

  speech = createEMXArray(speechSamples, fileLenInSamples);

  asl_P56(speech, (double) samplingRateInHz, (double) nBits, &lev, &af, &c0);

  //LOG(trace) << "P56::Compute: " << lev << " " << getLev();

  emxDestroyArray_real_T(speech);

}

