#ifndef WQUANT_H
#define WQUANT_H

#include <string>
#include <vector>

class Quantizer{
private:
    int _size; //Number of bytes
    float _s, _z;
    float _fmin, _fmax;
    int _qmin, _qmax;
    int clip(int x);
    bool _default;
public:
    Quantizer();
    Quantizer(int size, float min, float max);
    Quantizer(int size, std::vector<float>& x);
    Quantizer(int size, std::vector< std::vector<float> >& x);
    int quantize(float x);
    std::vector<int> quantize(std::vector<float>& x);
    std::vector< std::vector<int> > quantize(
        std::vector< std::vector<float> >& x
    );
    float dequantize(int xq);
    std::vector<float> dequantize(std::vector<int>& xq);
    std::vector< std::vector<float> > dequantize(
        std::vector< std::vector<int> >& xq
    );
    std::string str();
    void print();
};

#endif