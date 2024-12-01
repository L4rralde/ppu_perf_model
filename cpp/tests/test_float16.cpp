#include "../include/quant/quant.h"
#include "../include/float16/float16.h"
#include <iostream>

using namespace std;

float Dtype::min = 0;
float Dtype::max = 0;

int main(int argc, char **argv){
    if(argc < 3)
        return 0;

    for(int i = 1; i < argc; ++i){
        Float16 num(stof(argv[i]));
        num.print();
    }

    Float16 a(stof(argv[1]));
    Float16 b(stof(argv[2]));

    if(a < b){
        cout << "-1" << endl;
    }else if(a > b){
        cout << "1" << endl;
    }else{
        cout << "0" << endl;
    }

    Float16 sum = a + b;
    Float16 mult = a * b;

    sum.print();
    mult.print();

    return 0;
}