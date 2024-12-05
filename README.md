# Perceptron Processing Unit (PPU) Performance Model

TODO:
- [X] Build and train model
- [x] develop MLP in C++.
- [x] Quantization

save quantized weights in binary file.
Analyze accuracy, time, and storage using different sizes

## How to use

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/L4rralde/ppu_perf_model/HEAD?labpath=main.ipynb)

I don't know how to build this project on Windows machines. If you don't have access to an unix-based system, I recommend to use binder and open
a terminal on it.

### Build from terminal

#### No quantization

```sh
g++ --std=c++11 cpp/include/*/*.cpp cpp/src/main.cpp -o cpp/output/main.o
```

#### 8 bits quantization

```sh
g++ --std=c++11 cpp/include/*/*.cpp cpp/src/int8_model.cpp -o cpp/output/int8_model.o
```


### Run from terminal

```sh
./cpp/output/main.o data/pgm/001_Positive.pgm
```

```sh
./cpp/output/int8_model.o data/pgm/001_Positive.pgm
```