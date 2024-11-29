#include "quant.h"
#include <iostream>

Dtype::Dtype(float num){
    _num = num;
}

Dtype::Dtype(const Dtype& other){
    _num = other._num;
}

Dtype Dtype::operator+(Dtype& other){
    return Dtype(_num + other._num);
}

Dtype& Dtype::operator+=(Dtype&& other){
    _num += other._num;
    return *this;
}

Dtype  Dtype::operator*(Dtype& other){
    return Dtype(_num * other._num);
}

bool Dtype::operator<(Dtype&& other){
    return _num < other._num;
}

bool Dtype::operator==(Dtype&& other){
    return _num == other._num;
}

void Dtype::print(){
    std::cout << _num << std::endl;
}

Dtype quantisize(float x){
    return Dtype(x);
}

vec quantisize(std::vector<float>& x){
    vec quantisized;
    int len = x.size();
    for(int i = 0; i < len; ++i)
        quantisized.push_back(Dtype(x[i]));
    return quantisized;
}

void print(Dtype&& num){
    num.print();
}
