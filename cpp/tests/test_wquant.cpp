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
        Quantizer quanto(1, input);
        //vector<int> quantized = quanto.quantize(input);
        //vector<float> dequantized = quanto.dequantize(quantized);
        cout << fpath << ". " << quanto.str() << endl;
    }
    return 0;
}