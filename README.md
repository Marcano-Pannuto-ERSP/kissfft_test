# kissfft_test

- test.c: test getting output from FFT functions
- fft-with-file.c: open out.raw, process data with FFT, save output to amplitudes file
- graph.py: open amplitudes file, convert data back to floats, and graph the data
- fft-testing.c and fft-find-highest.c: open out.raw, process data with FFT, find frequency with greatest amplitude and print it out

To compile and run fft-with-file.c:
- Make sure out.raw is in this folder
- Check what the size of out.raw is (`du -b out.raw`) and use that to change this define: `#define N (<<size>>/2)`
- `gcc $(pkgconf --cflags kissfft-float) fft-with-file.c $(pkgconf --libs kissfft-float) -lm` (add -g after fft-with-file.c for debug)
- `./a.out` (or whatever the name of your executable is)

To run graph.py:
- Change these lines to include the sizes of out.raw and amplitudes:
  - `N = <<size of out.raw>> / 2`
  - `num_doubles = int(<<size of amplitudes>> / 8)`
- `python3 graph.py`
- (make sure to `ssh -Y` if not running it locally)

Note that if you want to change the sampling rate from 7813 Hz, you'll need to change that in both fft-with-file.c and graph.py.

To compile and run fft-testing.c or fft-find-highest.c:
- Same commands as fft-with-file.c
- Change N and S if needed:
  - fft-find-highest.c: Change the defines at the top of the file
  - fft-testing.c: Use the fft_N and fft_S functions to change the fft struct's fields

## Dependencies
- kissfft