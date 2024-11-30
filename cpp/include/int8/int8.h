#ifndef INT_8
#define INT_8

#include "../quant/quant.h"
#include <string>

const int INT8_NUM_INT_BITS = 3;
const int INT8_NUM_DEC_BITS = 4;
const int MAX_INT8 = 0x7F;

class Int8: Dtype{
friend class Int8Acc;
private:
    int8_t _num;
public:
    Int8();
    Int8(float x);
    Int8 operator+(Int8&& other);
    Int8 operator+(Int8& other);
    Int8& operator+=(Int8&& other);
    Int8 operator*(Int8&& other);
    Int8 operator*(Int8& other);
    bool operator<(Int8& other);
    bool operator>(Int8& other);
    std::string str();
    void print();
    static Int8 quantisize(float x);
    static std::vector<Int8> quantisize(std::vector<float>& x);
};

typedef std::vector<Int8> int8_vec;

void print(Int8& num);
void print(Int8&& num);

class Int8Acc: Int8{
private:
    int _acc;
public:
    Int8Acc();
    Int8Acc& operator+=(Int8&& other);
    Int8 to_int8();
};

#endif