//
// File: filter.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 30-May-2017 11:03:55
//
#ifndef __FILTER_H__
#define __FILTER_H__

// Include Files
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <rt_nonfinite.h>
#include <rtwtypes.h>
#include <asl_P56_types.h>

// Function Declarations
extern void filter(double b, const double a[2], const emxArray_real_T *x,
                   emxArray_real_T *y);

#endif

//
// File trailer for filter.h
//
// [EOF]
//
