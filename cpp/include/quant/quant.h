#ifndef QUANT_H
#define QUANT_H

#include <vector>

class Dtype{
private:
    float _num;
public:
    static float min, max;
    Dtype();
    Dtype(float x);
    Dtype(const Dtype& other);
    Dtype operator+(Dtype&& other);
    Dtype& operator+=(Dtype&& other);
    Dtype operator*(Dtype& other);
    bool operator<(Dtype& other);
    bool operator>(Dtype& other);
    bool operator==(Dtype& other);
    Dtype& operator=(Dtype&& other);
    void print();
    void print_inline();
    std::string str();
};

typedef std::vector<Dtype> vec;


Dtype quantisize(float x);
vec quantisize(std::vector<float>& x);

void print(Dtype&& num);
void print(vec& v);

#endif