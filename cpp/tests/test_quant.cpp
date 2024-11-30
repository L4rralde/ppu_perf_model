#include <iostream>
#include <string>
#include <vector>

#include "../include/pgm/pgm.h"
#include "../include/quant/quant.h"


using namespace std;


int main(int argc, char **argv){
    for(int i = 1; i < argc; ++i){
        string path(argv[i]);
        Pgm img(path);
        vector<float> transformed = img.get_transformed();
        vec quantisized = quantisize(transformed);
        print(quantisized);
    }
    return 0;
}