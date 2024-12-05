#!/bin/bash

# Check if GIT_ROOT is set
if [[ -z "${GIT_ROOT}" ]]; then
    echo "Error: GIT_ROOT must be set"
    exit 1
fi

# Check if pgm directory already exists
if [[ -d "${GIT_ROOT}/data/pgm" ]]; then
    echo "Directory ${GIT_ROOT}/data/pgm already exists."
    exit 0
fi

# Create data directory if it doesn't exist
mkdir -p "${GIT_ROOT}/data"

# Download the zip file
ZIP_URL="http://personal.cimat.mx:8181/~ivan.cruz/Databases/Stenosis608.zip"
ZIP_FILE="${GIT_ROOT}/data/Stenosis608.zip"

if ! wget -O "$ZIP_FILE" "$ZIP_URL"; then
    echo "Error: Failed to download $ZIP_URL"
    exit 2
fi

# Extract the zip file
if ! unzip -q "$ZIP_FILE" -d "${GIT_ROOT}/data"; then
    echo "Error: Failed to unzip $ZIP_FILE"
    exit 3
fi

# Rename extracted folder to 'pgm'
if ! mv "${GIT_ROOT}/data/Stenosis608" "${GIT_ROOT}/data/pgm"; then
    echo "Error: Failed to rename Stenosis608 to pgm"
    exit 4
fi

# Cleanup: remove the zip file
rm -f "$ZIP_FILE"

echo "pgm directory created successfully in ${GIT_ROOT}/data"
exit 0
