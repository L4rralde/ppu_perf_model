// Class to implement special-purpose arithmetic.
// Author: Emmanuel A. Larralde Ortiz | ealarralde@cimat.mx

#ifndef DTYPE_H
#define DTYPE_H

#include <vector>

class Dtype{
private:
    float _num;
public:
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
};

typedef std::vector<Dtype> vec;


Dtype asdtype(float x);
vec asdtype(std::vector<float>& x);

void print(Dtype&& num);
void print(vec& v);

#endif