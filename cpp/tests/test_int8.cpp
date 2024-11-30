#include <iostream>
#include "../include/int8/int8.h"

using namespace std;

int main(int argc, char **argv){
    if(argc != 3)
        return 0;

    Int8 a(stof(argv[1]));
    Int8 b(stof(argv[2]));

    Int8 sum = a + b;
    sum.print();

    Int8 mult = a * b;
    mult.print();

    return 0;
}