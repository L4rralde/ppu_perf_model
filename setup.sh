#!/bin/bash
export GIT_ROOT=$(git root)
$GIT_ROOT/data/get_data.sh
$GIT_ROOT/cpp/get_model_files.sh
echo Environment ready