#!/bin/bash

# Check if GIT_ROOT is set
if [[ -z "${GIT_ROOT}" ]]; then
    echo "Error: GIT_ROOT must be set"
    exit 1
fi

# Check if model already exists
if [[ -f "${GIT_ROOT}/models/model.pth" ]]; then
    echo "Model already exists."
    exit 0
fi

# Download the model
MODEL_URL="https://l4rralde.github.io/stenosis/model_pytorch/model.pth"
MODEL_FILE="${GIT_ROOT}/models/model.pth"

if ! wget -O "$MODEL_FILE" "$MODEL_URL"; then
    echo "Error: Failed to download $MODEL_URL"
    exit 2
fi
