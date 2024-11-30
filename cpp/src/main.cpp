#include <iostream>
#include <vector>
#include "../include/pgm/pgm.h"
#include "../include/quant/quant.h"
#include "../include/nn/nn.h"

using namespace std;

int main(int argc, char **argv){
    if(argc != 2)
        return 0;
    string fpath(argv[1]);
    Pgm img(fpath);

    vector<float> transformed = img.get_transformed();
    vec quantisized = quantisize(transformed);

    char const* tmp = getenv("GIT_ROOT");
    if(tmp == NULL)
        throw runtime_error("$GIT_ROOT must be defined first");
    string s(tmp);
    string files_path = s + "/cpp/model/";
    Perceptron model(files_path);

    vec prediction = model.forward(quantisized);


    return 0;
}