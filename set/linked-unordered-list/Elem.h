#ifndef CPP_TASKS_ELEM_H
#define CPP_TASKS_ELEM_H

class Elem {
public:
    Elem() : val(0), next(0) {}
    Elem(int v) : val(v), next(0) {}
    Elem(int v, Elem *n) : val(v), next(n) {}

    int val;
    Elem *next;
};

#endif //CPP_TASKS_ELEM_H
