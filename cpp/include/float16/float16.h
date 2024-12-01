#ifndef FLOAT16_H
#define FLOAT16_H

#include "../quant/quant.h"
#include <string>

class Float16{
private:
    bool _sign;
    int _exp;
    int _mantissa;
public:
    Float16();
    Float16(float x);
    Float16(Float16& other);
    float stdfloat();

    void print();
};

#endif