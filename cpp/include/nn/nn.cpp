#include "nn.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <regex>
#include <dirent.h>

Float16 ReLU(Float16&& num){
    Float16 zero(0);
    if(num < zero)
        return Float16(0);
    return Float16(num);
}

Neuron::Neuron(std::vector<float>& ws){
    _len = ws.size();
    for(int i = 0; i < _len; ++i)
        _ws.push_back(Float16(ws[i]));
}

Float16 Neuron::forward(float16_vec& x){
    int len = x.size();
    if(len + 1 != _len)
        throw std::invalid_argument("Len mismatch");
    Float16 acc(0);
    for(int i = 0; i < len; ++i)
        acc += _ws[i] * x[i];
    return acc + Float16(_ws[len]);
}

Layer::Layer(std::vector<std::vector<float>>& ws){
    _is_output_layer = false;
    _len = ws.size();
    for(int i = 0; i < _len; ++i)
        _neurons.push_back(Neuron(ws[i]));
}

float16_vec Layer::forward(float16_vec& x){
    float16_vec output;
    for(int i = 0; i < _len; ++i){
        if(_is_output_layer){
            output.push_back(_neurons[i].forward(x));
        }else{
            output.push_back(ReLU(_neurons[i].forward(x)));
        }
    }
    return output;
}

void Layer::as_output_layer(){
    _is_output_layer = true;
}

std::vector<std::string> get_model_files(std::string& fpath){
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(fpath.c_str())) == NULL)
        throw std::runtime_error("Couldn't find weights");

    std::vector<std::string> files;
    std::regex pattern(".*\\.txt");
    while((ent = readdir (dir)) != NULL){
        if(std::regex_match(ent->d_name, pattern)){
            std::string tmp(ent->d_name);
            files.push_back(fpath + tmp);
        }
    }
    closedir (dir);

    std::sort(files.begin(), files.end());
    return files;
}

Perceptron::Perceptron(std::string& fpath): _depth(0){
    std::cout << "Loading weights for inferecne." << std::endl;
    std::vector<std::vector<std::vector<float>>> weights;
    
    std::vector<std::string> model_files = get_model_files(fpath);
    int nlayers = model_files.size();
    for(int i = 0; i < nlayers; ++i){
        std::vector<std::vector<float>> layer_ws = read_weights_vector(model_files[i]);
        _layers.push_back(Layer(layer_ws));
        _depth++;
    }
    _layers[nlayers - 1].as_output_layer();
}

float16_vec Perceptron::forward(float16_vec& x){
    for(int i = 0; i < _depth; ++i)
        x = _layers[i].forward(x);
    return x;
}


std::vector<std::vector<float>> read_weights_vector(std::string& filename){
    std::vector<std::vector<float>> data;
    std::ifstream file(filename);

    if(!file.is_open())
        throw std::invalid_argument("Can't open file");

    std::string line;
    while(std::getline(file, line)){  // Read each line from the file
        std::istringstream lineStream(line);
        std::vector<float> row;
        float number;

        while(lineStream >> number)// Extract numbers from the line
            row.push_back(number);

        if(!row.empty())
            data.push_back(row);  // Add the row to the outer vector
    }

    file.close();
    return data;
}

int argmax(float16_vec& output){
    Float16 max(output[0]);
    int max_i = 0;
    int len = output.size();
    for(int i = 1; i < len; ++i){
        if(output[i] > max){
            max_i = i;
            max = Float16(output[i]);
        }
    }
    return max_i;
}
