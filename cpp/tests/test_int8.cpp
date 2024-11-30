#include <iostream>
#include "../include/int8/int8.h"
#include "../include/nn/nn.h"

using namespace std;

int main(int argc, char **argv){
    if(argc < 3)
        return 0;

    int8_vec vec;
    for(int i = 1; i < argc; ++i)
        vec.push_back(stof(argv[i]));

    int len = argc -1;
    for(int i = 1; i < len; ++i){
        Int8 a(vec[i - 1]);
        Int8 b(vec[i]);
        Int8 sum = a + b;
        Int8 mult = a * b;
        Int8 relu_a = ReLU(a);
        Int8 relu_b = ReLU(b);
        cout << "-----------" << endl;
        a.print();
        b.print();
        sum.print();
        mult.print();
        relu_a.print();
        relu_b.print();
    }

    return 0;
}