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
    int hits = 0;
    for(int i = 1; i < argc; ++i){
        cout << i << "/" << argc - 1 << endl;
        string fpath(argv[i]);
        Pgm img(fpath);

        vector<float> transformed = img.get_transformed();
        vec quantisized = quantisize(transformed);

        vec prediction = model.forward(quantisized);
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
    }

    float accuracy = hits/(argc - 1.0);
    cout << "Accuracy:" << accuracy << endl;
    if(accuracy < 0.95)
        throw runtime_error("ERROR. Drop of accuracy");

    return 0;
}
