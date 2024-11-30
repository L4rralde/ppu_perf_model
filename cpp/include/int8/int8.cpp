#include "int8.h"
#include <iostream>

Int8::Int8(): _num(0) {}

Int8::Int8(float x){
    x *= 1 << INT8_NUM_DEC_BITS;
    if(x > MAX_INT8)
        x = MAX_INT8;
    if(x < -MAX_INT8)
        x = -MAX_INT8;
    _num = static_cast<int8_t>(x);
}

int sum(int8_t a, int8_t b){
    int a_int = static_cast<int>(a);
    int b_int = static_cast<int>(b);
    int result = a_int + b_int;

    if(result > MAX_INT8)
        result = MAX_INT8;
    if(result < -MAX_INT8)
        result = -MAX_INT8;
    
    return result;
}

Int8 Int8::operator+(Int8&& other){
    int result = sum(_num, other._num);
    Int8 quant_result(0);
    quant_result._num = static_cast<int8_t>(result);
    return Int8(quant_result);
}

Int8 Int8::operator+(Int8& other){
    int result = sum(_num, other._num);
    Int8 quant_result(0);
    quant_result._num = static_cast<int8_t>(result);
    return Int8(quant_result);
}


int mult(int8_t a, int8_t b){
    int a_int = abs(static_cast<int>(a));
    int b_int = abs(static_cast<int>(b));

    int result = a_int * b_int;
    result >>= INT8_NUM_DEC_BITS;
    if(result > MAX_INT8)
        result = MAX_INT8;

    int pos = (a < 0) == (b < 0);

    return (-1 + 2*pos) * result;
}

Int8 Int8::operator*(Int8& other){
    int result = mult(_num, other._num);
    Int8 quant(0);
    quant._num = static_cast<int8_t>(result);

    return quant;
}

Int8 Int8::operator*(Int8&& other){
    int result = mult(_num, other._num);
    Int8 quant(0);
    quant._num = static_cast<int8_t>(result);

    return quant;
}

Int8& Int8::operator+=(Int8&& other){
    _num = static_cast<int8_t>(sum(_num, other._num));
    return *this;
}

bool Int8::operator<(Int8& other){
    return _num < other._num;
}

bool Int8::operator>(Int8& other){
    return _num > other._num;
}

std::string Int8::str(){
    float x = static_cast<float>(_num);
    x /= (1 << INT8_NUM_DEC_BITS);
    return std::to_string(x);
}

void Int8::print(){
    std::cout << str() << std::endl;
}

Int8 Int8::quantisize(float x){
    return Int8(x);
}

int8_vec Int8::quantisize(std::vector<float>& x){
    int8_vec quantisized;
    int len = x.size();
    for(int i = 0; i < len; ++i)
        quantisized.push_back(Int8(x[i]));
    return quantisized;
}

void print(Int8& num){
    num.print();
}

void print(Int8&& num){
    num.print();
}

Int8Acc::Int8Acc(): _acc(0) {}

Int8Acc& Int8Acc::operator+=(Int8&& other){
    _acc = _acc + static_cast<int>(other._num);
    return *this;
}

Int8 Int8Acc::to_int8(){
    return Int8(static_cast<float>(_acc));
}
