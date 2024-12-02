#ifndef BINFILES_H
#define BINFILES_H

#include <vector>
#include <string>
#include <fstream>

class binfile{
public:
    binfile() = delete; // Prevent instantiation
    ~binfile() = delete;
    static std::vector<uint8_t> read_bytes(std::string& fpath);
    static void write_bytes(
        std::vector<uint8_t>& data, std::string& fpath
    );

    template <typename T>
    static std::vector<T> read(std::string& fpath);
    
    template <typename T>
    static void write(std::vector<T>& data, std::string& fpath);

};

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
std::vector<T> binfile::read(std::string& fpath){
    std::vector<uint8_t> bytes = binfile::read_bytes(fpath);
    std::vector<T> data(bytes.size() / sizeof(T));
    std::copy(
        reinterpret_cast<T*>(bytes.data()),
        reinterpret_cast<T*>(bytes.data() + bytes.size()),
        data.begin()
    );
    return data;
}

template <typename T>
void binfile::write(std::vector<T>& data, std::string& fpath){
    std::vector<uint8_t> bytes(data.size() * sizeof(T));
    std::copy(
        reinterpret_cast<uint8_t*>(data.data()),
        reinterpret_cast<uint8_t*>(data.data() + data.size() * sizeof(T)),
        bytes.begin()
    );
    binfile::write_bytes(bytes, fpath);
}


#endif