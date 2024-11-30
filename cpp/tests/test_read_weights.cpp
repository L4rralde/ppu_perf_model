#include <iostream>
#include <vector>
#include <string>
#include "../include/nn/nn.h"


using namespace std;

int main(int argc, char **argv){
    if(argc != 2)
        return 0;
    
    string fpath(argv[1]);
    vector< vector<float> > ws = read_weights_vector(argv[1]);
    
    cout << ws.size() << ", " << ws[0].size() << endl;

    return 0;
}