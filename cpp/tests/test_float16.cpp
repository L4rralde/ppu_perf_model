#include "../include/float16/float16.h"

using namespace std;

int main(int argc, char **argv){
    if(argc < 2)
        return 0;

    for(int i = 1; i < argc; ++i){
        Float16 num(stof(argv[i]));
        num.print();
    }

    return 0;
}