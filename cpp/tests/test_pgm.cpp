#include <iostream>
#include "../include/pgm/pgm.h"

using namespace std;

int main(int argc, char **argv){
    for(int i = 1; i < argc; ++i){
        string path(argv[i]);
        Pgm temp(path);
        print(temp);
    }
    return 0;
}
