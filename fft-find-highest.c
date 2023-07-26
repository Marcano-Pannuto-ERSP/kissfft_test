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

void TestFftReal(const kiss_fft_scalar in[N], kiss_fft_cpx out[N / 2 + 1], FILE * fp)
{
  kiss_fftr_cfg cfg;

  if ((cfg = kiss_fftr_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
  {
    size_t i;

    kiss_fftr(cfg, in, out);
    free(cfg);

    double data[(N/2)+1];
    for (i = 0; i < N/2 + 1; i++)
    {
        double num = sqrt(out[i].r * out[i].r + out[i].i * out[i].i);
        data[i] = num;
    }
    int max = 0;
    int bucket = 0;
    for (int j = 1; j < N/2 + 1; j++){
      if(data[j] > max){
        max = data[j];
        bucket = j;
      }
    }
    int freq = (bucket * S)/N;
    printf("Frequency: %d\r\n", freq);
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

    // save contents of out.raw to a buffer
    uint16_t buffer[N];
    fread(buffer, 2, N, fp);
    
    // FFT transform
    kiss_fft_scalar in[N];
    kiss_fft_cpx out[N / 2 + 1];
    size_t i;

    for (i = 0; i < N; i++)
        in[i] = buffer[i];
    TestFftReal(in, out, fp2);

    return 0;
    
}