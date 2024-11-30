#include "int8.h"
#include <iostream>

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

std::string Int8::str(){
    float x = static_cast<float>(_num);
    x /= (1 << INT8_NUM_DEC_BITS);
    return std::to_string(x);
}

void Int8::print(){
    std::cout << str() << std::endl;
}

void print(Int8&& num){
    num.print();
}