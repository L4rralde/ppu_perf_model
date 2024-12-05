#!/bin/bash

# Check if GIT_ROOT is set
if [[ -z "${GIT_ROOT}" ]]; then
    echo "Error: GIT_ROOT must be set"
    exit 1
fi

# Check if model already exists
if [[ -d "${GIT_ROOT}/cpp/model" ]]; then
    echo "Model already exists."
    exit 0
fi

# Create data directory if it doesn't exist
mkdir -p "${GIT_ROOT}/cpp/model"

# Download the model
ZIP_URL="https://l4rralde.github.io/stenosis/model_txt/model.zip"
ZIP_FILE="${GIT_ROOT}/cpp/model.zip"

if ! wget -O "$ZIP_FILE" "$ZIP_URL"; then
    echo "Error: Failed to download $ZIP_URLS"
    exit 2
fi

# Extract the zip file
if ! unzip -q "$ZIP_FILE" -d "${GIT_ROOT}/cpp/"; then
    echo "Error: Failed to unzip $ZIP_FILE"
    exit 3
fi

# Cleanup: remove the zip file
rm -f "$ZIP_FILE"

