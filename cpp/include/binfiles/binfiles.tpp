#ifndef BINFILES_TPP
#define BINFILES_TPP

#include "binfiles.h"
#include <fstream>


std::vector<uint8_t> binfile::read_bytes(std::string& fpath){
    std::ifstream file;
    file.open(fpath, std::ios::in|std::ios::binary);
    std::vector<uint8_t> bytes;
    char c;
    while(file.read(&c, sizeof(char))){
        bytes.push_back(c);
    }
    file.close();

    return bytes;
}

void binfile::write_bytes(std::vector<uint8_t>& bytes, std::string& fpath){
    std::ofstream file(fpath, std::ios::out | std::ios::binary);
    int len = bytes.size();
    for(int i = 0; i < len; ++i)
        file.write((char *) &bytes[i], sizeof(uint8_t));
    file.close();
}

template <typename T>
std::vector<T> read(std::string& fpath){
    std::vector<T> data;
    std::vector<T> bytes = binfile::read_bytes(fpath);
    std::copy(bytes.begin(), bytes.end(), data.begin());
    return data;
}

template <typename T>
void write(std::vector<T>& data, std::string& fpath){
    std::vector<T> bytes;
    std::copy(data.begin(), data.end(), bytes.begin());
    binfile::write_bytes(bytes, fpath);
}

#endif