echo Building model
g++ --std=c++11 $GIT_ROOT/cpp/include/*/*.cpp $GIT_ROOT/cpp/tests/test_main.cpp -o $GIT_ROOT/cpp/output/test_main.o -lm -Wall -Wextra
echo Build done
$GIT_ROOT/cpp/output/test_main.o $GIT_ROOT/data/pgm/*.pgm