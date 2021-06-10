//
// File: filter.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 30-May-2017 11:03:55
//

// Include Files
#include <rt_nonfinite.h>
#include <asl_P56.h>
#include <filter.h>
#include <asl_P56_emxutil.h>

// Function Definitions

//
// Arguments    : double b
//                const double a[2]
//                const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
void filter(double b, const double a[2], const emxArray_real_T *x,
            emxArray_real_T *y) {
  unsigned int unnamed_idx_0;
  int j;
  double dbuffer_idx_1;
  double dbuffer_idx_0;
  unnamed_idx_0 = (unsigned int) x->size[0];
  j = y->size[0];
  y->size[0] = (int) unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *) y, j, (int) sizeof(double));
  dbuffer_idx_1 = 0.0;
  for (j = 0; j + 1 <= x->size[0]; j++) {
    dbuffer_idx_0 = dbuffer_idx_1 + x->data[j] * b;
    dbuffer_idx_1 = 0.0 - dbuffer_idx_0 * a[1];
    y->data[j] = dbuffer_idx_0;
  }
}

//
// File trailer for filter.cpp
//
// [EOF]
//
