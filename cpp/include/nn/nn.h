#ifndef NN_H
#define NN_H

#include <vector>
#include <string>
#include "../quant/quant.h"
#include "../float16/float16.h"

Float16 ReLU(Float16&& num);


class Neuron{
private:
    float16_vec _ws;
    int _len;
public:
    Neuron(std::vector<float>& ws);
    Float16 forward(float16_vec& x);
};


class Layer{
private:
    std::vector<Neuron> _neurons;
    int _len;
    bool _is_output_layer;
public:
    Layer(std::vector<std::vector<float>>& ws);
    float16_vec forward(float16_vec &x);
    void as_output_layer();
};

class Perceptron{
private:
    std::vector<Layer> _layers;
    int _depth;
public:
    Perceptron(std::string& fpath);
    float16_vec forward(float16_vec& x);
};

std::vector< std::vector<float> > read_weights_vector(std::string& filename);

int argmax(float16_vec& output);

#endif