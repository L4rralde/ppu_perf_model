// Code for build Multilayer Perceptrons
// Author: Emmanuel A. Larralde Ortiz | ealarralde.gmail.com

#ifndef NN_H
#define NN_H

#include <vector>
#include <string>
#include "../dtype/dtype.h"


Dtype ReLU(Dtype&& num);


class Neuron{
private:
    vec _ws;
    int _len;
public:
    Neuron(std::vector<float>& ws);
    Dtype forward(vec& x);
};

class Layer{
private:
    std::vector<Neuron> _neurons;
    int _len;
    bool _is_output_layer;
public:
    Layer(std::vector<std::vector<float>>& ws);
    vec forward(vec &x);
    void as_output_layer();
};

class Perceptron{
private:
    std::vector<Layer> _layers;
    int _depth;
public:
    Perceptron(std::string& fpath);
    Perceptron(std::string& fpath, int bits);
    Perceptron(std::vector<std::vector<std::vector<float>>>& weights);
    vec forward(vec& x);
};

std::vector< std::vector<float> > read_weights_vector(std::string& filename);

int argmax(vec& output);

std::vector<std::string> get_model_files(std::string& fpath);

float mse(
    std::vector< std::vector<float> >& x,
    std::vector< std::vector<float> >& y
);
#endif