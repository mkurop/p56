//
// File: asl_P56_emxAPI.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 30-May-2017 11:03:55
//
#ifndef __ASL_P56_EMXAPI_H__
#define __ASL_P56_EMXAPI_H__

// Include Files
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <rt_nonfinite.h>
#include <rtwtypes.h>
#include <asl_P56_types.h>

// Function Declarations
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for asl_P56_emxAPI.h
//
// [EOF]
//
