#include "float16.h"
#include <vector>
#include <limits.h>
#include <iostream>
#include <math.h>
#include <iomanip>

union float_bits{
    uint32_t bits;
    float d;
} converter;

std::vector<uint32_t> get_float_bits(float x){
    std::vector<uint32_t> fields (3, 0.0);
    converter.d = x;
    fields[0] = converter.bits >> 31;
    fields[1] = (converter.bits >> 23) & 0xFF;
    fields[2] = converter.bits & 0x7FFFFF;
    return fields;
}

Float16::Float16(): _sign(0), _exp(0), _mantissa(0) {}

Float16::Float16(float x): _sign(0), _exp(0), _mantissa(0){
    std::vector<uint32_t> fields = get_float_bits(x);
    _sign = fields[0];
    _exp = fields[1] - 127 + 15;
    if(_exp < 0)
        _exp = 0;
    if(_exp > 31)
        _exp = 31;
    
    _mantissa = fields[2] >> 13;
}

Float16::Float16(Float16& other){
    _sign = other._sign;
    _exp = other._exp;
    _mantissa = other._mantissa;
}

Float16::Float16(Float16&& other){
    _sign = other._sign;
    _exp = other._exp;
    _mantissa = other._mantissa;
}

int Float16::compare(Float16& a, Float16& b){
    if(a._sign && !b._sign)
        return -1;
    if(!a._sign && b._sign)
        return 1;
    //Same signs
    int32_t bits_a = (a._exp << 10) | a._mantissa;
    int32_t bits_b = (b._exp << 10) | b._mantissa;
    if(bits_a == bits_b)
        return 0; //Equals
    if(!a._sign){
        //Both positive numbers
        if(bits_a < bits_b)
            return -1;
        return 1;
    }
    //Both negative numbers
    if(bits_a < bits_b)
        return 1;
    return -1;
}

bool Float16::operator<(Float16& other){
    return compare(*this, other) == -1;
}

bool Float16::operator>(Float16& other){
    return compare(*this, other) == 1;
}

bool Float16::operator==(Float16& other){
    return compare(*this, other) == 0;
}

Float16 Float16::sum(Float16& a, Float16& b){
    float fa = a.stdfloat();
    float fb = b.stdfloat();

    float fs = fa + fb;
    Float16 s(fs);
    return s;
}

Float16 Float16::mult(Float16& a, Float16& b){
    float fa = a.stdfloat();
    float fb = b.stdfloat();

    float fm = fa * fb;
    Float16 m(fm);
    return m;
}

float Float16::stdfloat(){
    if(_exp == 0 && _mantissa == 0)
        return 0;
    if(_exp == 0x1F && _mantissa == 0x3FF){
        if(_sign)
            return -std::numeric_limits<float>::infinity();
        return std::numeric_limits<float>::infinity();
    }
    float normalized = 1.0 + static_cast<float>(_mantissa)/(1 << 10);
    float factor = pow(2, _exp - 15);
    return (1 - 2*_sign) * normalized * factor;
}

Float16 Float16::operator+(Float16& other){
    return Float16::sum(*this, other);
}

Float16 Float16::operator+(Float16&& other){
    return Float16::sum(*this, other);
}

Float16 Float16::operator*(Float16& other){
    return Float16::mult(*this, other);
}

Float16 Float16::operator*(Float16&& other){
    return Float16::mult(*this, other);
}

Float16& Float16::operator+=(Float16&& other){
    Float16 aux = sum(*this, other);
    _sign = aux._sign;
    _exp = aux._exp;
    _mantissa = aux._mantissa;

    return *this;
}

Float16& Float16::operator=(Float16& other){
    _sign = other._sign;
    _exp = other._exp;
    _mantissa = other._mantissa;
    return *this;
}

void Float16::print(){
    std::cout << std::setprecision(10) << stdfloat() << std::endl;
}

Float16 Float16::quantisize(float x){
    return Float16(x);
}

float16_vec Float16::quantisize(std::vector<float>& x){
    float16_vec vec;
    int len = x.size();
    for(int i = 0; i < len; ++i)
        vec.push_back(Float16(x[i]));
    return vec;
}