//   medianfilter.cpp - impelementation of
//   1D and 2D median filter routines
//
//   The code is property of LIBROW
//   You can use it on your own
//   When utilizing credit LIBROW site

#include <memory.h>
#include "medianfilter.h"

//   1D MEDIAN FILTER implementation
//     signal - input signal
//     result - output signal
//     N      - length of the signal
void _medianfilter(const element* signal, element* result, int N) {
  //   Move window through all elements of the signal
  for (int i = 1; i < N - 1; ++i) {
    //   Pick up window elements
    element window[3];
    for (int j = 0; j < 3; ++j) window[j] = signal[i - 1 + j];
    //   Order elements (only half of them)
    for (int j = 0; j < 3; ++j) {
      //   Find position of minimum element
      int min = j;
      for (int k = j + 1; k < 3; ++k)
        if (window[k] < window[min]) min = k;
      //   Put found minimum element in its place
      const element temp = window[j];
      window[j] = window[min];
      window[min] = temp;
    }
    //   Get result - the middle element
    result[i - 1] = window[1];
  }
}

//   1D MEDIAN FILTER wrapper
//     signal - input signal
//     result - output signal
//     N      - length of the signal
void medianfilter(element* signal, element* result, int N) {
  //   Check arguments
  if (!signal || N < 1) return;
  //   Treat special case N = 1
  if (N == 1) {
    if (result) result[0] = signal[0];
    return;
  }
  //   Allocate memory for signal extension
  element* extension = new element[N + 2];
  //   Check memory allocation
  if (!extension) return;
  //   Create signal extension
  memcpy(extension + 1, signal, N * sizeof(element));

  extension[0] = 64;
  extension[N + 1] = 0;

  //   Call median filter implementation
  _medianfilter(extension, result ? result : signal, N + 2);
  //   Free memory
  delete[] extension;
}
