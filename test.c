#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kiss_fftr.h"

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif

#define N 1024    // total number of samples
#define S 7813    // sampling frequency
#define f 440     // Hz of sine wave

void TestFftReal(const char* title, const kiss_fft_scalar in[N], kiss_fft_cpx out[N / 2 + 1])
{
  kiss_fftr_cfg cfg;

  printf("%s\n", title);

  if ((cfg = kiss_fftr_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
  {
    size_t i;

    kiss_fftr(cfg, in, out);
    free(cfg);

    // for (i = 0; i < N; i++)
    // {
    //   printf(" in[%2zu] = %+f    ", i, in[i]);
    //   if (i < N / 2 + 1)
    //     printf("out[%2zu] = %+f , %+f , %+f", i, out[i].r, out[i].i, sqrt(out[i].r * out[i].r + out[i].i * out[i].i));
    //   printf("\n");
    // }

    for (i = 0; i < N/2 + 1; i++)
    {
        printf("%+f, ", sqrt(out[i].r * out[i].r + out[i].i * out[i].i));
    }
    printf("\n");
  }
  else
  {
    printf("not enough memory?\n");
    exit(-1);
  }
}

int main(void)
{
  kiss_fft_scalar in[N];
  kiss_fft_cpx out[N / 2 + 1];
  size_t i;

  /*
  for (i = 0; i < N; i++)
    in[i] = 0;
  TestFftReal("Zeroes (real)", in, out);

  for (i = 0; i < N; i++)
    in[i] = 1;
  TestFftReal("Ones (real)", in, out);
  */

  // add 2 sine waves
  for (i = 0; i < N; i++)
    in[i] = sin(2 * M_PI * f * i / S);

  for (i = 0; i < N; i++)
    in[i] += sin(2 * M_PI * 880 * i / S);
  TestFftReal("SineWave (real)", in, out);

  return 0;
}