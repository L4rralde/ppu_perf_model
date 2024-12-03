#include <iostream>
#include <string>
#include <stdexcept>
#include "../include/nn/nn.h"
#include "../include/wquant/wquant.h"
#include "../include/binfiles/binfiles.h"

using namespace std;

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

int main(){
    char const* tmp = getenv("GIT_ROOT");
    if(tmp == NULL)
        throw runtime_error("$GIT_ROOT must be defined first");
    string s(tmp);
    string files_path = s + "/cpp/model/";
    string qmodel_path = s + "/cpp/qmodel/model.bin";
    vector<string> model_files = get_model_files(files_path);
    int num_files = model_files.size();

    vector<int8_t> all_ws;
    for(int i = 0; i < num_files; ++i){
        string src_path(model_files[i]);
        cout << "Starting conversion of " << src_path << endl;
        vector< vector<float> > ws = read_weights_vector(src_path);
        vector<float> flat = flatten(ws);
        Quantizer quanto(8, flat);
        vector<int> quantized = quanto.quantize(flat);
        int len = quantized.size();
        vector<int8_t> qbytes(len, 0.0);
        for(int i = 0; i < len; ++i)
            qbytes[i] = static_cast<int8_t>(quantized[i]);
        all_ws.insert(all_ws.end(), qbytes.begin(), qbytes.end());
        continue;
    }
    binfile::write<int8_t>(all_ws, qmodel_path);

    cout << "Correctly quantized model" << endl;
    return 0;
}