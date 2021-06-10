//
// File: asl_P56_emxutil.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 30-May-2017 11:03:55
//

// Include Files
#include <rt_nonfinite.h>
#include <asl_P56.h>
#include <asl_P56_emxutil.h>

#include <memory>

// Function Definitions

//
// Arguments    : emxArray_real_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void b_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions) {
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *) malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *) NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *) malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray__common *emxArray
//                int oldNumel
//                int elementSize
// Return Type  : void
//
void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int elementSize) {
  int newNumel;
  int i;
  void *newData;
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i <<= 1;
    }

    newData = calloc((unsigned int) i, (unsigned int) elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, (unsigned int) (elementSize * oldNumel));
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
// Return Type  : void
//
void emxFree_int32_T(emxArray_int32_T **pEmxArray) {
  if (*pEmxArray != (emxArray_int32_T *) NULL) {
    if (((*pEmxArray)->data != (int *) NULL) && (*pEmxArray)->canFreeData) {
      free((void *) (*pEmxArray)->data);
    }

    free((void *) (*pEmxArray)->size);
    free((void *) *pEmxArray);
    *pEmxArray = (emxArray_int32_T *) NULL;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
// Return Type  : void
//
void emxFree_real_T(emxArray_real_T **pEmxArray) {
  if (*pEmxArray != (emxArray_real_T *) NULL) {
    if (((*pEmxArray)->data != (double *) NULL) && (*pEmxArray)->canFreeData) {
      free((void *) (*pEmxArray)->data);
    }

    free((*pEmxArray)->size);
    free(*pEmxArray);
    *pEmxArray = (emxArray_real_T *) NULL;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions) {
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *) malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *) NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions) {
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *) malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *) NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// File trailer for asl_P56_emxutil.cpp
//
// [EOF]
//
