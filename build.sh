#!/bin/
$GIT_ROOT/data/get_data.sh
$GIT_ROOT/cpp/get_model_files.sh

# Mkdir output dir if does not exist.
if [[ ! -d "${GIT_ROOT}/cpp/output" ]]; then
    mkdir ${GIT_ROOT}/cpp/output
fi

g++ --std=c++11 $GIT_ROOT/cpp/include/*/*.cpp $GIT_ROOT/cpp/src/main.cpp -o $GIT_ROOT/cpp/output/main.o -lm -Wall -Wextra
g++ --std=c++11 $GIT_ROOT/cpp/include/*/*.cpp $GIT_ROOT/cpp/tests/test_main.cpp -o $GIT_ROOT/cpp/output/test_main.o -lm -Wall -Wextra
g++ --std=c++11 $GIT_ROOT/cpp/include/*/*.cpp $GIT_ROOT/cpp/src/int8_model.cpp -o $GIT_ROOT/cpp/output/int8_model.o -lm -Wall -Wextra
echo Build done