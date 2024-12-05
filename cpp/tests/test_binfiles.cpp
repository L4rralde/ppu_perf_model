// Checks if the binary files library works correctly
// Author: Emmanuel A. Larralde Ortiz | ealarralde@gmail.com
#include <iostream>
#include <vector>
#include "../include/binfiles/binfiles.h"

using namespace std;

int main(int argc, char **argv){
    if(argc < 3)
        return 0;
    string fname(argv[1]); //Temp file to store binary data
    int len = argc - 2;
    vector<int8_t> vec(argc - 2, 0); //Data to binarize
    for(int i = 0; i < len; ++i)
        vec[i] = stoi(argv[i + 2]);

    //Write binary data into file
    binfile::write<int8_t>(vec, fname);
    
    //Read binary file
    vector<int8_t> invec = binfile::read<int8_t>(fname);
    
    //Check if the content matches the original one.
    if(invec.size() != vec.size())
        throw runtime_error("Error. Length mismatch.");
    for(int i = 0; i < len; ++i){
        cout << static_cast<int>(invec[i]) << " ";
        if(vec[i] != invec[i])
            throw runtime_error("Error. Content mismatch.");
    }

    cout << endl;
    cout << "PASS." << endl;
    
    return 0;
}