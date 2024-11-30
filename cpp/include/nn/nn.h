#ifndef NN_H
#define NN_H

#include <vector>
#include <string>
#include "../quant/quant.h"
#include "../int8/int8.h"


Int8 ReLU(Int8&& num);


class Neuron{
private:
    int8_vec _ws;
    int _len;
public:
    Neuron(std::vector<float>& ws);
    Int8 forward(int8_vec& x);
};


class Layer{
private:
    std::vector<Neuron> _neurons;
    int _len;
    bool _is_output_layer;
public:
    Layer(std::vector<std::vector<float>>& ws);
    int8_vec forward(int8_vec &x);
    void as_output_layer();
};

class Perceptron{
private:
    std::vector<Layer> _layers;
    int _depth;
public:
    Perceptron(std::string& fpath);
    int8_vec forward(int8_vec& x);
};

std::vector< std::vector<float> > read_weights_vector(std::string& filename);

int argmax(int8_vec& output);

#endif