# kissfft_test

- test.c: test getting output from FFT functions
- fft-with-file.c: open out.raw, process data with FFT, save output to amplitudes file
- graph.py: open amplitudes file, convert data back to floats, and graph the data

To compile and run fft-with-file.c:
- Make sure out.raw is in this folder
- `gcc $(pkgconf --cflags kissfft-float) fft-with-file.c $(pkgconf --libs kissfft-float) -lm` (add -g after fft-with-file.c for debug)
- `./a.out` (or whatever the name of your executable is)

To run graph.py:
- `python3 graph.py`
- (make sure to `ssh -Y` if not running it locally)