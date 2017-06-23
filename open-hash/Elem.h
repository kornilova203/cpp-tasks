
#ifndef DICTIONARY_ELEM_H
#define DICTIONARY_ELEM_H


#include <cstring>

struct Elem {  // element of hash table
    Elem() {
        name = 0;
        next = 0;
    }
    Elem(const char *name_) {
        name = new char[15];
        strcpy(name, name_);
        next = 0;
    }
    ~Elem() {
        if (name != 0) {
            delete[] name;
        }
    }

    char *name;
    Elem *next;
};


#endif //DICTIONARY_ELEM_H
