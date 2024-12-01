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

void Float16::print(){
    std::cout << std::setprecision(10) << stdfloat() << std::endl;
}