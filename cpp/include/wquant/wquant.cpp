#include "wquant.h"
#include <algorithm>
#include <iostream>
#include <sstream>

template <typename T>
std::string to_string2(const T a_value, const int n = 20){
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

void get_constants(
    float fmin, float fmax, int qmin, int qmax, float *s, float *z
){
    *s = (fmax - fmin)/(qmax - qmin);
    *z = (fmax*qmin - fmin*qmax)/(fmax - fmin);
}

Quantizer::Quantizer(){ //[-2, 2];
    _default = true;
    _size = 1;
    _qmin = -127;
    _qmax = 127;
    _fmin = -2;
    _fmax = 2;
    get_constants(_fmin, _fmax, _qmin, _qmax, &_s, &_z);
}

Quantizer::Quantizer(int nbits, float fmin, float fmax){
    _default = false;
    _size = nbits;
    _qmax = (1 << (nbits - 1)) - 1;
    _qmin = -_qmax;
    _fmin = fmin;
    _fmax = fmax;
    get_constants(_fmin, _fmax, _qmin, _qmax, &_s, &_z);
}

Quantizer::Quantizer(int nbits, std::vector<float>& x){
    _default = false;
    _size = nbits;
    _qmax = (1 << (nbits - 1)) - 1;
    _qmin = -_qmax;
    _fmax = *std::max_element(x.begin(), x.end());
    _fmin = *std::min_element(x.begin(), x.end());
    get_constants(_fmin, _fmax, _qmin, _qmax, &_s, &_z);
}

Quantizer::Quantizer(int nbits, std::vector< std::vector<float> >& x){
    _default = false;
    _size = nbits;
    _qmax = (1 << (nbits - 1)) - 1;
    _qmin = -_qmax;
    int nrows = x.size();

    _fmax = *std::max_element(x[0].begin(), x[0].end());
    _fmin = *std::min_element(x[0].begin(), x[0].end());
    for(int i = 1; i < nrows; ++i){
        float tmp_max = *std::max_element(x[i].begin(), x[i].end());
        float tmp_min = *std::min_element(x[i].begin(), x[i].end());
        if(tmp_max > _fmax)
            _fmax = tmp_max;
        if(tmp_min < _fmin)
            _fmin = tmp_min;
    }
    get_constants(_fmin, _fmax, _qmin, _qmax, &_s, &_z);
}

int Quantizer::quantize(float x){
    int xq = x/_s + _z;
    if(xq < _qmin)
        xq = _qmin;
    if(xq > _qmax)
        xq = _qmax;

    return xq;
}

std::vector<int> Quantizer::quantize(std::vector<float>& x){
    int len = x.size();
    std::vector<int> xq(len, 0);
    for(int i = 0; i < len; ++i)
        xq[i] = quantize(x[i]);
    return xq;
}

std::vector< std::vector<int> > Quantizer::quantize(
        std::vector< std::vector<float> >& x
){
    int rows = x.size();
    int cols = x[0].size();
    std::vector< std::vector<int> > xq(
        rows, std::vector<int>(cols, 0)
    );
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            xq[i][j] = quantize(x[i][j]);
    return xq;
}


float Quantizer::dequantize(int xq){
    return _s * (xq - _z);
}

std::vector<float> Quantizer::dequantize(std::vector<int>& xq){
    int len = xq.size();
    std::vector<float> x(len, 0.0);
    for(int i = 0; i < len; ++i)
        x[i] = dequantize(xq[i]);
    return x;
}

std::vector< std::vector<float> > Quantizer::dequantize(
        std::vector< std::vector<int> >& xq
){
    int rows = xq.size();
    int cols = xq[0].size();
    std::vector< std::vector<float> > x(
        rows, std::vector<float> (cols, 0.0)
    );
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            x[i][j] = dequantize(xq[i][j]);
    return x;
}

std::string Quantizer::str(){
    return "Quantizer(" + to_string2(_size) +
            ", " + to_string2(_fmin) +
            ", " + to_string2(_fmax) + ")";
}

void Quantizer::print(){
    std::cout << str() << std::endl;
}
