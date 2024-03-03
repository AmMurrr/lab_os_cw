#ifndef CONSTS_H
#define CONSTS_H
const unsigned int SIZE = 1010000; //2^12
#endif // CONSTS_H

#ifndef POT_H
#define POT_H
#include <vector>
#include <map>
#include <stdexcept>
#include <math.h>
#include <iostream>



struct buffer{
    char* ptr;
    bool taken = false;
    buffer(char* p):  ptr{p} {}
};

class pot{
    char* memory_ptr;
    std::map<int,std::vector<buffer>> memory;
public:
    pot();
    unsigned int get_order(unsigned int);
    char* malloc(unsigned int);
    void free(char* ptr);

    inline char* search(int key);

    ~pot();
};

#endif // POT_H