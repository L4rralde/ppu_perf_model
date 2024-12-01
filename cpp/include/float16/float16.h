#ifndef FLOAT16_H
#define FLOAT16_H

#include "../quant/quant.h"
#include <string>

class Float16: Dtype{
private:
    bool _sign;
    int _exp;
    int _mantissa;
    static int compare(Float16& a, Float16& b);
    static Float16 sum(Float16& a, Float16& b);
    static Float16 mult(Float16& a, Float16& b);
public:
    Float16();
    Float16(float x);
    Float16(Float16& other);
    Float16(Float16&& other);
    bool operator<(Float16& other);
    bool operator>(Float16& other);
    bool operator==(Float16& other);
    Float16 operator+(Float16& other);
    Float16 operator+(Float16&& other);
    Float16 operator*(Float16& other);
    Float16 operator*(Float16&& other);
    Float16& operator+=(Float16&& other);
    Float16& operator=(Float16& other);

    float stdfloat();
    void print();
    static Float16 quantisize(float x);
    static std::vector<Float16> quantisize(std::vector<float>& x);
};

typedef std::vector<Float16> float16_vec;

#endif