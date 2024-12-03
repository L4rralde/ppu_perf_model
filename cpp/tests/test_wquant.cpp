#include <iostream>
#include <vector>
#include <string>
#include "../include/wquant/wquant.h"
#include "../include/nn/nn.h"

using namespace std;

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
