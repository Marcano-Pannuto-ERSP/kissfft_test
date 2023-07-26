#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kiss_fftr.h"
#include <stdint.h>

// Structure representing the information of the samples
struct fft
{
	uint32_t N; // total number of samples (size of file in bytes / 2)
    uint32_t S; // sampling frequency
};

// Initialize FFT structure
void fft_init(struct fft *fft)
{
    fft->N = (40960/2);
    fft->S = 7813;
}

// Change N
void fft_N(struct fft *fft, uint32_t number)
{
    fft->N = number;
}

// Change S
void fft_S(struct fft *fft, uint32_t sampling)
{
    fft->S = sampling;
}

// helper function for getting the highest frequency
void TestFftReal(struct fft *fft, const kiss_fft_scalar in[], kiss_fft_cpx out[])
{
  kiss_fftr_cfg cfg;

  if ((cfg = kiss_fftr_alloc(fft->N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
  {
    size_t i;

    kiss_fftr(cfg, in, out);
    free(cfg);

    double data[(fft->N/2)+1];
    for (i = 0; i < fft->N/2 + 1; i++)
    {
        double num = sqrt(out[i].r * out[i].r + out[i].i * out[i].i);
        data[i] = num;
    }
    int max = 0;
    int bucket = 0;
    for (int j = 1; j < fft->N/2 + 1; j++){
      if(data[j] > max){
        max = data[j];
        bucket = j;
      }
    }
    int freq = (bucket * fft->S)/fft->N;
    printf("Frequency: %d\r\n", freq);
  }
  else
  {
    printf("not enough memory?\n");
    exit(-1);
  }
}

// read the audio file and get the highest frequency
void fft_read(struct fft *fft, FILE * fp, uint16_t buffer[])
{
  // save contents of out.raw to a buffer
  fread(buffer, 2, fft->N, fp);
  
  // FFT transform
  kiss_fft_scalar in[fft->N];
  kiss_fft_cpx out[fft->N / 2 + 1];
  size_t i;

  for (i = 0; i < fft->N; i++){
    in[i] = buffer[i];
  }
  TestFftReal(fft, in, out);
}

struct fft fft;

int main(void)
{
    fft_init(&fft);
     
    // open audio file
    FILE * fp;
    fp = fopen("out.raw", "r");
    uint16_t buffer[fft.N];

    fft_read(&fft, fp, buffer);

    return 0;
    
}