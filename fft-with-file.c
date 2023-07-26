#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kiss_fftr.h"
#include <stdint.h>

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif

#define N (40960/2)    // total number of samples (size of file in bytes / 2)
#define S 7813    // sampling frequency
#define f 440     // Hz of sine wave

void TestFftReal(const char* title, const kiss_fft_scalar in[N], kiss_fft_cpx out[N / 2 + 1], FILE * fp)
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
        double num = sqrt(out[i].r * out[i].r + out[i].i * out[i].i);
        // printf("%+f, ", num);
        int retVal = fwrite(&num, sizeof(num), 1, fp);
        printf("retVal: %d\n", retVal);
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
    // open audio file
    FILE * fp;
    fp = fopen("out.raw", "r");

    FILE * fp2;
    fp2 = fopen("amplitudes", "w");

    // save contents of out.raw to a buffer
    uint16_t buffer[N];
    fread(buffer, 2, N, fp);
    // printf("%s\n", buffer);


    
    // FFT transform
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

    // for (i = 0; i < N; i++)
    //     in[i] = sin(2 * M_PI * f * i / S);

    // for (i = 0; i < N; i++)
    //     in[i] += sin(2 * M_PI * 880 * i / S);

    for (i = 0; i < N; i++)
        in[i] = buffer[i];
    TestFftReal("SineWave (real)", in, out, fp2);

    return 0;
    
}