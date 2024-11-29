#include <iostream>
#include "../include/pgm/pgm.h"

using namespace std;

int main(int argc, char **argv){
    for(int i = 1; i < argc; ++i){
        string path(argv[i]);
        print(read_pgm(path));
    }
    return 0;
}
