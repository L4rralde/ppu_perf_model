#include "dtype.h"
#include <iostream>

Dtype::Dtype(): _num(0) {}

Dtype::Dtype(float num){
    _num = num;
}

Dtype::Dtype(const Dtype& other){
    _num = other._num;
}

Dtype Dtype::operator+(Dtype&& other){
    return Dtype(_num + other._num);
}

Dtype& Dtype::operator+=(Dtype&& other){
    _num += other._num;
    return *this;
}

Dtype  Dtype::operator*(Dtype& other){
    return Dtype(_num * other._num);
}

bool Dtype::operator<(Dtype& other){
    return _num < other._num;
}

bool Dtype::operator>(Dtype& other){
    return _num > other._num;
}

bool Dtype::operator==(Dtype& other){
    return _num == other._num;
}

Dtype& Dtype::operator=(Dtype&& other){
    // Guard self assignment
    if (this == &other)
        return *this;
    _num = other._num;
    return *this;
}

void Dtype::print(){
    std::cout << _num << std::endl;
}

void Dtype::print_inline(){
    std::cout << _num;
}

Dtype asdtype(float x){
    return Dtype(x);
}

vec asdtype(std::vector<float>& x){
    vec dtyped;
    int len = x.size();
    for(int i = 0; i < len; ++i)
        dtyped.push_back(Dtype(x[i]));
    return dtyped;
}

void print(Dtype&& num){
    num.print();
}

void print(vec& v){
    int len = v.size();
    for(int i = 0; i < len; ++i){
        v[i].print_inline();
        std::cout << " ";
    }
    std::cout << std::endl;
}
