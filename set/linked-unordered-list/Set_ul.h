
#ifndef SET_ON_BIT_FIELD_SET_H
#define SET_ON_BIT_FIELD_SET_H

#include <iostream>
#include "Elem.h"

class Set_ul {
public:
    Set_ul() { tail = 0; }

    Set_ul(int x) {
        tail = new Elem(x);
        tail->next = tail;
    }

    Set_ul &insert(int);

    Set_ul &del(int);

    Set_ul &assign(Set_ul const &);

    Set_ul &setUnion(Set_ul const &, Set_ul const &);

    Set_ul &intersection(Set_ul const &, Set_ul const &);

    Set_ul &difference(Set_ul const &, Set_ul const &);

    Set_ul &merge(Set_ul const &, Set_ul const &);

    Set_ul *find(Set_ul &, int);

    int member(int) const;

    int maxVal() const;

    int minVal() const;

    int equal(Set_ul const &a) const;

    void makeNull();

    std::string toString() const;

protected:
    static Elem *setUnion_(const Elem *t1, const Elem *t2);

    static Elem *intersection_(const Elem *t1, const Elem *t2);

    static Elem *difference_(const Elem *t1, const Elem *t2);

    Elem *findPrev_(Elem *, int) const;

    Elem *merge_(const Elem *t1, const Elem *t2) const;

    Set_ul *find_(Set_ul &a, Set_ul &b, int x) const;

    int maxVal_(const Elem *t) const;

    int minVal_(const Elem *t) const;

    int equal_(const Elem *t1, const Elem *t2) const;

    static int member_(const Elem *, int);

    static int isDisjoint_(const Elem *, const Elem *);

    static Elem *createListOfOneElem_(int x);

    void del_(Elem *prev) const;

    Elem *del_(Elem *t, int x);

    void makeNull_(Elem *);

    static Elem *copy_(Elem const *t);

    Elem *deleteElem_(Elem *t, Elem *prev);

    static Elem *insertAfterElem_(Elem *, int);

    Elem *tail;

    static void checkOther_(const Elem *pElem, const Elem *t2, Elem *temp, Elem *tail);
};


#endif //SET_ON_BIT_FIELD_SET_H
