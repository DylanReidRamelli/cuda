#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "convolution.h"
#include "fourier_filter.h"

int main(int argc, char *argv[]) {
  if (2 != argc) {
    fprintf(stderr, "usage: %s <shift-value>\n", argv[0]);

    return EXIT_FAILURE;
  }

  enum { FILTER_SUPPORT = _N_ };

  const float SHIFT = atof(argv[1]);
  const int INT_SHIFT = (int)SHIFT;

  // TODO define a way to choose which M based on the amount of fractional
  // shift.

  float M = 2;
  int n = 100;
  int n_extended = n + FILTER_SUPPORT;

  // Create simple signal, half 1's, half 0's.
  float *x = calloc(n_extended, sizeof(float));
  for (int i = floor(n / 4) + (FILTER_SUPPORT / 2);
       i < floor(n / 2) + (FILTER_SUPPORT / 2); i++) {
    x[i] = 1;
  }
  // for (int i = floor(n / 2); i < floor(n / ); i++) {
  //   x[i] = 1;
  // }

  // Pad original signal left and right by pad_n
  // const int pad_n = 20;

  // Create filter
  float complex *H = calloc(FILTER_SUPPORT, sizeof(float complex));
  create_filter(H, FILTER_SUPPORT, M);

  float complex *L = calloc(FILTER_SUPPORT, sizeof(float complex));
  create_phase_shift(L, FILTER_SUPPORT, SHIFT - INT_SHIFT);

  float complex *z = calloc(FILTER_SUPPORT, sizeof(float complex));
  shift_filter(H, L, z, FILTER_SUPPORT, M);

  float output[n];
  float output_int_shift[n];

  if (SHIFT - INT_SHIFT != 0) {
    dconv(x, n, z, output);
    for (int i = 0; i < n; i++) {
      int n_idx = (i + INT_SHIFT) % n;
      output_int_shift[n_idx] = output[i];
    }
  } else {
    for (int i = 0; i < n; i++) {
      int n_idx = (i + INT_SHIFT) % n;
      output_int_shift[n_idx] = x[i];
    }
  }

  // Shift by the integera part

  FILE *fp = fopen("original_signal.raw", "wb");
  if (fp) {
    size_t r = fwrite(x, sizeof(x[0]), n_extended, fp);
    printf("wrote %zu elements out of %d requested\n", r, n_extended);
  }

  FILE *fp1 = fopen("shifted_signal.raw", "wb");
  if (fp1) {
    size_t r = fwrite(output_int_shift, sizeof(output_int_shift[0]), n, fp1);
    printf("wrote %zu elements out of %d requested\n", r, n);
  }

  FILE *fp2 = fopen("filter.raw", "wb");
  if (fp2) {
    size_t r = fwrite(z, sizeof(z[0]), FILTER_SUPPORT, fp2);
    printf("wrote %zu elements out of %d requested\n", r, FILTER_SUPPORT);
  }

  free(H);
  free(L);
  free(z);
}
