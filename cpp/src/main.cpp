#include <iostream>
#include <vector>
#include "../include/pgm/pgm.h"
#include "../include/quant/quant.h"
#include "../include/nn/nn.h"

using namespace std;

int main(int argc, char **argv){
    if(argc < 2)
        return 0;
    //Load model
    char const* tmp = getenv("GIT_ROOT");
    if(tmp == NULL)
        throw runtime_error("$GIT_ROOT must be defined first");
    string s(tmp);
    string files_path = s + "/cpp/model/";
    Perceptron model(files_path);

    //Predict
    for(int i = 1; i < argc; ++i){
        string fpath(argv[i]);
        Pgm img(fpath);

        vector<float> transformed = img.get_transformed();
        vec quantisized = quantisize(transformed);

        vec prediction = model.forward(quantisized);
        bool stenosis = prediction[1] > prediction[0];
        cout << static_cast<int>(stenosis) << endl;
    }
    return 0;
}
