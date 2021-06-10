//
// File: asl_P56.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 30-May-2017 11:03:55
//

// Include Files
#include <rt_nonfinite.h>
#include <asl_P56.h>
#include <asl_P56_emxutil.h>
#include <filter.h>
#include <P56.h>
#include <iostream>

using namespace std;

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1) {
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// this implements ITU P.56 method B.
//  'speechfile' is the speech file to calculate active speech level for,
//  'asl' is the active speech level (between 0 and 1),
//  'asl_rms' is the active speech level mean square energy.
// Arguments    : const emxArray_real_T *x
//                double fs
//                double nbits
//                double *asl_ms
//                double *asl
//                double *c0
// Return Type  : void
//
void asl_P56(const emxArray_real_T *x, double fs, double nbits, double *asl_ms,
             double *asl, double *c0) {
  emxArray_real_T *c;
  double I;
  double g;
  int k;
  int nm1d2;
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absb;
  emxArray_real_T *y;
  unsigned int uv0[2];
  emxArray_real_T *r0;
  emxArray_real_T *a;
  emxArray_int32_T *r1;
  emxArray_real_T *hang;
  boolean_T guard1 = false;
  double tol;
  double sq;
  emxArray_real_T *x_abs;
  int32_T exitg4;
  emxArray_real_T *p;
  double dv0[2];
  double dv1[2];
  boolean_T exitg3;
  boolean_T guard2 = false;
  double AdB1;
  double CdB1;
  boolean_T exitg1;
  boolean_T b_guard1 = false;
  double iterno;
  double asl_ms_log;
  double cl0;
  double midcount;
  double midthr;
  int32_T exitg2;
  double diff;
  emxInit_real_T(&c, 1);

  //  x is the column vector of floating point speech data
  //  make sure x is column vector
  //  time constant of smoothing, in seconds
  //  hangover time in seconds
  //  margin in dB of the difference between threshold and active speech level
  //  number of thresholds, for 16 bit, it's 15
  I = ceil(fs * 0.2);

  //  hangover in samples
  g = exp(-1.0 / (fs * 0.03));

  //  smoothing factor in envelop detection
  k = c->size[0];
  c->size[0] = (int) (nbits - 1.0);
  emxEnsureCapacity((emxArray__common *) c, k, (int) sizeof(double));
  nm1d2 = (int) (nbits - 1.0);
  for (k = 0; k < nm1d2; k++) {
    c->data[k] = 0.0;
  }

  if ((nbits - 1.0) - 16.0 < -15.0) {
    n = -1;
    anew = -15.0;
    apnd = -16.0;
  } else if (rtIsInf((nbits - 1.0) - 16.0)) {
    n = 0;
    anew = rtNaN;
    apnd = (nbits - 1.0) - 16.0;
  } else {
    anew = -15.0;
    ndbl = floor((((nbits - 1.0) - 16.0) - -15.0) + 0.5);
    apnd = -15.0 + ndbl;
    cdiff = (-15.0 + ndbl) - ((nbits - 1.0) - 16.0);
    absb = fabs((nbits - 1.0) - 16.0);
    if ((15.0 >= absb) || rtIsNaN(absb)) {
      absb = 15.0;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = (nbits - 1.0) - 16.0;
    } else if (cdiff > 0.0) {
      apnd = -15.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n = (int) ndbl - 1;
  }

  b_emxInit_real_T(&y, 2);
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *) y, k, (int) sizeof(double));
  if (n + 1 > 0) {
    y->data[0] = anew;
    if (n + 1 > 1) {
      y->data[n] = apnd;
      nm1d2 = (n + (n < 0)) >> 1;
      for (k = 1; k < nm1d2; k++) {
        y->data[k] = anew + (double) k;
        y->data[n - k] = apnd - (double) k;
      }

      if (nm1d2 << 1 == n) {
        y->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        y->data[nm1d2] = anew + (double) nm1d2;
        y->data[nm1d2 + 1] = apnd - (double) nm1d2;
      }
    }
  }

  for (k = 0; k < 2; k++) {
    uv0[k] = (unsigned int) y->size[k];
  }

  b_emxInit_real_T(&r0, 2);
  k = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = (int) uv0[1];
  emxEnsureCapacity((emxArray__common *) r0, k, (int) sizeof(double));
  for (k = 0; k < (int) uv0[1]; k++) {
    r0->data[k] = rt_powd_snf(2.0, y->data[k]);
  }

  nm1d2 = r0->size[1];
  for (k = 0; k < nm1d2; k++) {
    c->data[k] = r0->data[r0->size[0] * k];
  }

  emxFree_real_T(&r0);
  emxInit_real_T(&a, 1);

  //  vector with thresholds from one quantizing level up to half the maximum
  //  code, at a step of 2, in the case of 16bit samples, from 2^-15 to 0.5;
  k = a->size[0];
  a->size[0] = (int) (nbits - 1.0);
  emxEnsureCapacity((emxArray__common *) a, k, (int) sizeof(double));
  nm1d2 = (int) (nbits - 1.0);
  for (k = 0; k < nm1d2; k++) {
    a->data[k] = 0.0;
  }

  if (1.0 > nbits - 1.0) {
    nm1d2 = 0;
  } else {
    nm1d2 = (int) (nbits - 1.0);
  }

  emxInit_int32_T(&r1, 2);
  k = r1->size[0] * r1->size[1];
  r1->size[0] = 1;
  r1->size[1] = nm1d2;
  emxEnsureCapacity((emxArray__common *) r1, k, (int) sizeof(int));
  for (k = 0; k < nm1d2; k++) {
    r1->data[r1->size[0] * k] = k;
  }

  nm1d2 = r1->size[0] * r1->size[1];
  for (k = 0; k < nm1d2; k++) {
    a->data[r1->data[k]] = 0.0;
  }

  emxInit_real_T(&hang, 1);

  //  activity counter for each level threshold
  k = hang->size[0];
  hang->size[0] = (int) (nbits - 1.0);
  emxEnsureCapacity((emxArray__common *) hang, k, (int) sizeof(double));
  nm1d2 = (int) (nbits - 1.0);
  for (k = 0; k < nm1d2; k++) {
    hang->data[k] = 0.0;
  }

  if (1.0 > nbits - 1.0) {
    nm1d2 = 0;
  } else {
    nm1d2 = (int) (nbits - 1.0);
  }

  k = r1->size[0] * r1->size[1];
  r1->size[0] = 1;
  r1->size[1] = nm1d2;
  emxEnsureCapacity((emxArray__common *) r1, k, (int) sizeof(int));
  for (k = 0; k < nm1d2; k++) {
    r1->data[r1->size[0] * k] = k;
  }

  nm1d2 = r1->size[0] * r1->size[1];
  for (k = 0; k < nm1d2; k++) {
    hang->data[r1->data[k]] = I;
  }

  emxFree_int32_T(&r1);

  //  hangover counter for each level threshold
  n = x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity((emxArray__common *) y, k, (int) sizeof(double));
  for (k = 0; k < n; k++) {
    y->data[y->size[0] * k] = x->data[k];
  }

  guard1 = false;
  if (y->size[1] == 1) {
    guard1 = true;
  } else {
    n = x->size[1];
    if (n == 1) {
      guard1 = true;
    } else {
      tol = 0.0;
      for (k = 0; k < y->size[1]; k++) {
        tol += y->data[y->size[0] * k] * x->data[k];

      }

      sq = tol;
    }
  }

  if (guard1) {
    tol = 0.0;
    for (k = 0; k < y->size[1]; k++) {
      tol += y->data[y->size[0] * k] * x->data[k];
    }

    sq = tol;
  }

  emxFree_real_T(&y);
  emxInit_real_T(&x_abs, 1);

  //  long-term level square energy of x
  n = x->size[1];

  //  length of x
  //  use a 2nd order IIR filter to detect the envelope q
  nm1d2 = x->size[1];
  k = x_abs->size[0];
  x_abs->size[0] = nm1d2;
  emxEnsureCapacity((emxArray__common *) x_abs, k, (int) sizeof(double));
  k = 0;
  do {
    exitg4 = 0;
    nm1d2 = x->size[1];
    if (k <= nm1d2 - 1) {
      x_abs->data[k] = fabs(x->data[k]);
      k++;
    } else {
      exitg4 = 1;
    }
  } while (exitg4 == 0);

  emxInit_real_T(&p, 1);
  dv0[0] = 1.0;
  dv0[1] = -g;
  filter(1.0 - g, dv0, x_abs, p);
  dv1[0] = 1.0;
  dv1[1] = -g;
  filter(1.0 - g, dv1, p, x_abs);
  for (k = 0; k < n; k++) {
    nm1d2 = 0;
    exitg3 = false;
    while ((!exitg3) && (nm1d2 <= (int) (nbits - 1.0) - 1)) {
      guard2 = false;
      if (x_abs->data[k] >= c->data[nm1d2]) {
        a->data[nm1d2]++;
        hang->data[nm1d2] = 0.0;
        guard2 = true;
      } else if (hang->data[nm1d2] < I) {
        a->data[nm1d2]++;
        hang->data[nm1d2]++;
        guard2 = true;
      } else {
        exitg3 = true;
      }

      if (guard2) {
        nm1d2++;
      }
    }
  }

  *asl = 0.0;
  *asl_ms = 0.0;
  *c0 = 0.0;

  if (a->data[0] == 0.0) { //
    std::cout << "a->data[0] == 0.0 condition";
  } else {
    AdB1 = 10.0 * log10(sq / a->data[0] + 2.2204460492503131E-16);
    CdB1 = 20.0 * log10(c->data[0] + 2.2204460492503131E-16);

    if (AdB1 - CdB1 < 15.9) {
      std::cout << "AdB1 - CdB1 < 15.9 condition";
    } else {
      k = x_abs->size[0];
      x_abs->size[0] = (int) (nbits - 1.0);
      emxEnsureCapacity((emxArray__common *) x_abs, k, (int) sizeof(double));
      nm1d2 = (int) (nbits - 1.0);
      for (k = 0; k < nm1d2; k++) {
        x_abs->data[k] = 0.0;
      }

      k = hang->size[0];
      hang->size[0] = (int) (nbits - 1.0);
      emxEnsureCapacity((emxArray__common *) hang, k, (int) sizeof(double));
      nm1d2 = (int) (nbits - 1.0);
      for (k = 0; k < nm1d2; k++) {
        hang->data[k] = 0.0;
      }

      k = p->size[0];
      p->size[0] = (int) (nbits - 1.0);
      emxEnsureCapacity((emxArray__common *) p, k, (int) sizeof(double));
      nm1d2 = (int) (nbits - 1.0);
      for (k = 0; k < nm1d2; k++) {
        p->data[k] = 0.0;
      }

      x_abs->data[0] = AdB1;
      hang->data[0] = CdB1;
      p->data[0] = AdB1 - CdB1;
      for (nm1d2 = 1; nm1d2 - 1 < (int) ((nbits - 1.0) + -1.0); nm1d2++) {
        x_abs->data[nm1d2] = 10.0 * log10(sq / (a->data[nm1d2] +
            2.2204460492503131E-16) + 2.2204460492503131E-16);
        hang->data[nm1d2] = 20.0 * log10(c->data[nm1d2] + 2.2204460492503131E-16);
      }

      nm1d2 = 1;
      exitg1 = false;
      while ((!exitg1) && (nm1d2 - 1 <= (int) ((nbits - 1.0) + -1.0) - 1)) {
        b_guard1 = false;
        if (a->data[nm1d2] != 0.0) {
          p->data[nm1d2] = x_abs->data[nm1d2] - hang->data[nm1d2];
          if (p->data[nm1d2] <= 15.9) {
            //  interpolate to find the asl
            tol = 0.5;

            //  Check if extreme counts are not already the true active value
            iterno = 1.0;
            if (fabs((x_abs->data[nm1d2] - hang->data[nm1d2]) - 15.9) < 0.5) {
              asl_ms_log = x_abs->data[nm1d2];
              cl0 = hang->data[nm1d2];
            } else if (fabs((x_abs->data[(int) ((2.0 + (double) (nm1d2 - 1)) - 1.0)
                - 1] - hang->data[(int) ((2.0 + (double) (nm1d2 - 1))
                - 1.0) - 1]) - 15.9) < 0.5) {
              asl_ms_log = x_abs->data[(int) ((2.0 + (double) (nm1d2 - 1)) - 1.0)
                  - 1];
              cl0 = hang->data[(int) ((2.0 + (double) (nm1d2 - 1)) - 1.0) - 1];
            } else {
              //  Initialize first middle for given (initial) bounds
              midcount = (x_abs->data[nm1d2] + x_abs->data[(int) ((2.0 + (double)
                  (nm1d2 - 1)) - 1.0) - 1]) / 2.0;
              midthr = (hang->data[nm1d2] + hang->data[(int) ((2.0 + (double)
                  (nm1d2 - 1)) - 1.0) - 1]) / 2.0;

              //  Repeats loop until `diff' falls inside the tolerance (-tol<=diff<=tol)
              do {
                exitg2 = 0;
                diff = (midcount - midthr) - 15.9;
                if (fabs(diff) <= tol) {
                  exitg2 = 1;
                } else {
                  //  if tolerance is not met up to 20 iteractions, then relax the
                  //  tolerance by 10%
                  iterno++;
                  if (iterno > 20.0) {
                    tol *= 1.1;
                  }

                  if (diff > tol) {
                    //  then new bounds are ...
                    midcount = (x_abs->data[nm1d2] + midcount) / 2.0;

                    //  upper and middle activities
                    midthr = (hang->data[nm1d2] + midthr) / 2.0;

                    //  ... and thresholds
                  } else {
                    if (diff < -tol) {
                      //  then new bounds are ...
                      midcount = (midcount + x_abs->data[(int) ((2.0 + (double)
                          (nm1d2 - 1)) - 1.0) - 1]) / 2.0;

                      //  middle and lower activities
                      midthr = (midthr + hang->data[(int) ((2.0 + (double) (nm1d2
                          - 1)) - 1.0) - 1]) / 2.0;

                      //  ... and thresholds
                    }
                  }
                }
              } while (exitg2 == 0);

              //    Since the tolerance has been satisfied, midcount is selected
              //    as the interpolated value with a tol [dB] tolerance.
              asl_ms_log = midcount;
              cl0 = midthr;
            }

            *asl_ms = rt_powd_snf(10.0, asl_ms_log / 10.0);

            *asl = sq / (double) n / *asl_ms;


            *c0 = rt_powd_snf(10.0, cl0 / 20.0);
            exitg1 = true;
          } else {
            b_guard1 = true;
          }
        } else {
          b_guard1 = true;
        }

        if (b_guard1) {
          nm1d2++;
        }
      }
    }
  }

  emxFree_real_T(&p);
  emxFree_real_T(&x_abs);
  emxFree_real_T(&hang);
  emxFree_real_T(&a);
  emxFree_real_T(&c);
}

//
// File trailer for asl_P56.cpp
//
// [EOF]
//
