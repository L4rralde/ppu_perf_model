# Perceptron Processing Unit (PPU) Performance Model

TODO:
- [X] Build and train model
- [x] develop MLP in C++.
- [x] Quantization
- [ ] Testing

save quantized weights in binary file.
Analyze accuracy, time, and storage using different sizes

## How to use

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/L4rralde/ppu_perf_model/HEAD?labpath=main.ipynb)

I don't know how to build this project on Windows machines. If you don't have access to an unix-based system, I recommend to use binder and open
a terminal on it.


### Initial setup

```sh
source setup.sh #Only the first time
```

### Build

```sh
source build.sh
```

### Test

```sh
source test.sh
```

### Fast Int8 model

```sh
./cpp/output/int8_model.o data/pgm/*.pgm
```