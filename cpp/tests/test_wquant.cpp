#include <iostream>
#include <vector>
#include <string>
#include "../include/wquant/wquant.h"
#include "../include/nn/nn.h"

using namespace std;

float mse(vector< vector<float> >& x, vector< vector<float> >& y){
    int rows = x.size();
    int cols = x[0].size();
    float acc_err = 0;
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            float err = x[i][j] - y[i][j];
            acc_err += err * err;
        }
    }
    return acc_err/(rows * cols);
}

int main(int argc, char **argv){
    if(argc < 2)
        return 0;
    for(int i = 1; i < argc; ++i){
        string fpath(argv[i]);
        vector< vector<float>> input = read_weights_vector(fpath);
        Quantizer quanto(8, input);
        vector< vector<int> > quantized = quanto.quantize(input);
        vector< vector<float> > dequantized = quanto.dequantize(quantized);
        cout << fpath << ". " << quanto.str() << endl;
        cout << "Error: " << mse(input, dequantized) << endl;
    }
    return 0;
}