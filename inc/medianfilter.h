//   medianfilter.h - declarations for
//   1D and 2D median filter routines
//
//   The code is property of LIBROW
//   You can use it on your own
//   When utilizing credit LIBROW site

#ifndef _MEDIANFILTER_H_
#define _MEDIANFILTER_H_

//   Signal/image element type
typedef int element;

//   1D MEDIAN FILTER, window size 5
//     signal - input signal
//     result - output signal, NULL for inplace processing
//     N      - length of the signal
void medianfilter(element* signal, element* result, int N);

#endif
