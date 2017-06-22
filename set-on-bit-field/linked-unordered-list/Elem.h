#ifndef SET_ON_BIT_FIELD_ELEM_H
#define SET_ON_BIT_FIELD_ELEM_H

class Elem {
public:
    Elem() : val(0), next(0) {}
    Elem(int v) : val(v), next(0) {}
    Elem(int v, Elem *n) : val(v), next(n) {}

    int val;
    Elem *next;
};


#endif //SET_ON_BIT_FIELD_ELEM_H
