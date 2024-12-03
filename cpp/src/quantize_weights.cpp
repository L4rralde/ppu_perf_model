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
    string qmodel_path = s + "/cpp/qmodel/";
    vector<string> model_files = get_model_files(files_path);
    int num_files = model_files.size();

    for(int i = 0; i < num_files; ++i){
        string src_path(model_files[i]);
        cout << "Starting conversion of " << src_path << endl;
        vector< vector<float> > ws = read_weights_vector(src_path);
        unsigned long rows = ws.size();
        unsigned long cols = ws[0].size();
        Quantizer quanto(8, ws);
        quanto.print();
        cout << rows << ", " << cols << endl;
        vector< vector<int> > quantized_ws = quanto.quantize(ws);
        vector<int> flat = flatten(quantized_ws);
        int len = flat.size();
        vector<int8_t> qbytes(flat.begin(), flat.end());
        string binfpath = qmodel_path + to_string(i) + ".txt";
        binfile::write<int8_t>(qbytes, binfpath);
        //Check
        vector<int8_t> read_qbytes = binfile::read<int8_t>(binfpath);
        vector<int> read_quantized(read_qbytes.begin(), read_qbytes.end());
        vector<vector<int>> read_rehasped = reshape(
            read_quantized, rows, cols
        );
        for(unsigned long i = 0; i < rows; ++i)
            for(unsigned long j = 0; j < cols; ++j)
                if(read_rehasped[i][j] != quantized_ws[i][j])
                    throw runtime_error("Mismatch.");

        vector<vector<float>> read_ws = quanto.dequantize(read_rehasped);
        cout << "Error: " << mse(ws, read_ws) << endl;
    }

    cout << "Correctly quantized model."  << endl;
    cout << "PASS" << endl;

    return 0;
}
