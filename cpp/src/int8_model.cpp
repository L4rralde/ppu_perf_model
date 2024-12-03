#include <iostream>
#include <string>
#include <stdexcept>
#include "../include/nn/nn.h"
#include "../include/wquant/wquant.h"
#include "../include/binfiles/binfiles.h"
#include "../include/pgm/pgm.h"

using namespace std;

vector<Quantizer> qs{
    Quantizer(8, -0.21828389167785644531, 0.22750344872474670410),
    Quantizer(8, -0.28965741395950317383, 0.37081623077392578125),
    Quantizer(8, -0.25820058584213256836, 0.42827829718589782715),
    Quantizer(8, -0.28323006629943847656, 0.25655370950698852539)
};

vector<vector<unsigned int>> shapes{
    {1024, 4097}, {256, 1025}, {64, 257}, {2, 65}
};

template <typename T>
vector<T> flatten(vector<vector<T>>& x){
    unsigned long rows = x.size();
    unsigned long cols = x[0].size();
    vector<T> flat (rows * cols, 0);
    for(unsigned long i = 0; i < rows; ++i)
        for(unsigned long j = 0; j < cols; ++j)
            flat[i*cols + j] = x[i][j];
    return flat;
}

template <typename T>
vector<vector<T>> reshape(
    vector<T>& x, unsigned long rows, unsigned long cols
){
    if(rows * cols != x.size())
        throw invalid_argument("Size mismatch");
    vector<vector<T>> data (rows, vector<T> (cols, 0.0));
    for(unsigned long i = 0; i < rows; ++i)
        for(unsigned long j = 0; j < cols; ++j)
            data[i][j] = x[i*cols + j];
    return data;
}

int main(int argc, char **argv){
    if(argc < 2)
        return 0;

    char const* tmp = getenv("GIT_ROOT");
    if(tmp == NULL)
        throw runtime_error("$GIT_ROOT must be defined first");
    //Load quantized weights from file
    string s(tmp);
    string files_path = s + "/cpp/qmodel/";
    vector<string> files = get_model_files(files_path);
    int nlayers = files.size();
    if(nlayers != static_cast<int>(qs.size()))
        throw runtime_error("ERROR: Model depth mismatch.");

    vector<vector<vector<float>>> weights;
    cout << "Loading model..." << endl;
    for(int layer = 0; layer < nlayers; ++layer){
        vector<int8_t> layer_int8_qweights = binfile::read<int8_t>(files[layer]);
        vector<int> layer_qweights(
            layer_int8_qweights.begin(),
            layer_int8_qweights.end()
        );
        vector<float> flat_layer_weights = qs[layer].dequantize(layer_qweights);
        vector<vector<float>> layer_weights = reshape(
            flat_layer_weights,
            shapes[layer][0],
            shapes[layer][1]
        );
        weights.push_back(layer_weights);
    }
    Perceptron model(weights);

    //Predict
    int hits = 0;
    for(int i = 1; i < argc; ++i){
        string fpath(argv[i]);
        Pgm img(fpath);

        vector<float> transformed = img.get_transformed();
        vec dtyped = asdtype(transformed);

        vec prediction = model.forward(dtyped);
        int stenosis_hat = argmax(prediction);
        int stenosis;
        if(fpath.find("Positive") != std::string::npos){
            stenosis = 1;
        }else if(fpath.find("Negative") != std::string::npos){
            stenosis = 0;
        }else{
            throw runtime_error("Invalid file");
        }
        hits += stenosis == stenosis_hat;
        cout << stenosis_hat << endl;
    }
    float accuracy = hits/(argc - 1.0);
    cout << "Accuracy: " << accuracy << endl;

    return 0;
}