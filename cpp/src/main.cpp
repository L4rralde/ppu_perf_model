#include <iostream>
#include <vector>
#include "../include/pgm/pgm.h"
#include "../include/quant/quant.h"


using namespace std;

int main(int argc, char **argv){
    if(argc != 2)
        return 0;
    string fpath(argv[1]);
    Pgm img(fpath);

    vector<float> transformed = img.get_transformed();
    vec quantisized = quantisize(transformed);
    int len = quantisized.size();
    for(int i = 0; i < len; ++i)
        quantisized[i].print();
    

    return 0;
}