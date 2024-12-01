#include <iostream>
#include <vector>
#include "../include/pgm/pgm.h"
#include "../include/dtype/dtype.h"
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
        vec dtyped = asdtype(transformed);

        vec prediction = model.forward(dtyped);
        cout << argmax(prediction) << endl;
    }
    return 0;
}
