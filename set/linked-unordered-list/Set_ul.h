
#ifndef SET_ON_BIT_FIELD_SET_H
#define SET_ON_BIT_FIELD_SET_H

#include <iostream>
#include "Elem.h"

using namespace std;

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

    string toString() const;

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

private:
    Set_ul(Elem *tail) {
        this->tail = tail;
    }

    static void checkOther_(const Elem *pElem, const Elem *t2, Elem *temp, Elem *tail);
};

void Set_ul::makeNull() {
    if (tail != 0) {
        makeNull_(tail);
        tail = 0;
    }
}

void Set_ul::makeNull_(Elem *t) {
    if (t == 0) {
        return;
    }
    Elem *temp = t->next;  // start with head
    while (temp != t) {  // until last elem
        Elem *remember = temp;
        temp = temp->next;
        delete remember;
    }
    delete t;
}

Set_ul &Set_ul::insert(int x) {
    if (tail == 0) {  // if list is empty
        tail = new Elem(x);
        tail->next = tail;
    } else
        tail = insertAfterElem_(tail, x);
    return *this;
}

// insert new elem
// return pointer to new elem
Elem *Set_ul::insertAfterElem_(Elem *prev, int x) {
    Elem *newElem = new Elem(x);
    newElem->next = prev->next;
    prev->next = newElem;
    return newElem;
}

// find element which is before x
// list must have at least 2 elems
Elem *Set_ul::findPrev_(Elem *t, int x) const {
    Elem *prev = t;
    Elem *next = t->next;
    while (next != t) {
        if (next->val == x) {  // if needed elem is found
            return prev;
        }
        prev = prev->next;
        next = next->next;
    }
    if (next->val == x)  // check last elem
        return prev;
    return 0;
}

// delete element of set
Set_ul &Set_ul::del(int x) {
    if (tail != 0)  // if it has at least one elem
        tail = del_(tail, x);
    return *this;
}

// delete element in linked list
// list must be not empty
// return new tail
Elem *Set_ul::del_(Elem *t, int x) {
    if (t == t->next) { // if it is last elem
        if (t->val == x) {
            delete t;
            return 0;
        }
        return t;
    }
    Elem *prev = findPrev_(t, x);  // find previous elem
    if (prev != 0)
        return deleteElem_(t, prev);
    return t;
}

// union of 2 sets
// create new set which is union of this 2 sets
// delete this set
// assign new tail to tail of this set
Set_ul &Set_ul::setUnion(Set_ul const &a, Set_ul const &b) {
    makeNull_(tail);
    if (a.tail == 0) {  // if second set is empty
        tail = copy_(b.tail);
    } else if (b.tail == 0) { // if this set is empty
        tail = copy_(a.tail);
    } else {
        tail = setUnion_(a.tail, b.tail);
    }
    return *this;
}

// create new set
// copy first set
// go through elems in second set
//      if it is not found in new set
//          add it to new set
Elem *Set_ul::setUnion_(const Elem *t1, const Elem *t2) {
    Elem *newTail = copy_(t1);  // copy first set
    Elem *temp = t2->next;
    while (temp != t2) {  // for all elements in new set (except tail)
        if (!member_(newTail, temp->val)) {  // if elem is NOT is new set
            insertAfterElem_(newTail, temp->val);  // insert it to new set
            newTail = newTail->next;
        }
        temp = temp->next;
    }
    if (!member_(newTail, t2->val)) {  // check tail
        insertAfterElem_(newTail, t2->val);  // insert elem
        newTail = newTail->next;
    }
    return newTail;
}

Set_ul &Set_ul::intersection(Set_ul const &a, Set_ul const &b) {
    makeNull_(tail);
    if (!(a.tail == 0 || b.tail == 0)) {
        tail = intersection_(a.tail, b.tail);
    }
    return *this;
}

// create new list
// go through first list
//      if element is found in second list
//          push it to new list
Elem *Set_ul::intersection_(const Elem *t1, const Elem *t2) {
    Elem *newTail = 0;
    Elem *temp = t1->next;
    const Elem *prev = t1;
    int ifFirstFound = 0;
    // find first element
    while (temp != t1 && !ifFirstFound) {  // for all elements in this set (except tail)
        if (member_(t2, temp->val)) {  // if elem is NOT is set A
            ifFirstFound = 1;
            newTail = new Elem(temp->val);
            newTail->next = newTail;
        }
        prev = prev->next;
        temp = temp->next;
    }
    // find other elements
    while (temp != t1) {  // for all elements in this set (except tail)
        if (member_(t2, temp->val)) {  // if elem is NOT is set A
            insertAfterElem_(newTail, temp->val);
        }
        prev = prev->next;
        temp = temp->next;
    }
    // check tail
    if (member_(t2, t1->val)) {  // if tail is not in set A
        insertAfterElem_(newTail, t1->val);
    }
    return newTail;
}


Set_ul &Set_ul::difference(Set_ul const &a, Set_ul const &b) {
    makeNull_(tail);
    if (a.tail != 0) {
        if (b.tail == 0) {
            tail = copy_(a.tail);
        } else {
            tail = difference_(a.tail, b.tail);
        }
    }
    return *this;
}

// create new list
// go through list t1
//      if elem not in t2
//          insert it to new list
Elem *Set_ul::difference_(const Elem *t1, const Elem *t2) {
    Elem *newTail = 0;
    Elem *temp = t1->next;
    int ifFirstFound = 0;
    // find first elem for newTail
    while (temp != t1 && !ifFirstFound) {  // for all elements in t1 (except tail)
        if (!member_(t2, temp->val)) {  // if elem is NOT is set A
            ifFirstFound = 1;  // insert first elem
            newTail = createListOfOneElem_(temp->val);
        }
        temp = temp->next;
    }

    if (!ifFirstFound) {
        if (!member_(t2, t1->val)) { // check tail
            return createListOfOneElem_(t1->val);
        }
        return 0;
    }

    checkOther_(t1, t2, temp, newTail);
    // check tail
    if (!member_(t2, t1->val)) {  // if elem is NOT is set A
        insertAfterElem_(newTail, t1->val);
    }
    return newTail;
}

// delete elem from list.
Elem *Set_ul::deleteElem_(Elem *t, Elem *prev) {
    if (t == t->next) {  // if it is last elem
        delete t;
        return 0;
    }
    if (prev->next == t) {  // if delete tail (but it is not last elem)
        prev->next = prev->next->next;
        delete tail;
        return prev;
    }
    Elem *remember = prev->next;  // remember which elem will be deleted
    prev->next = prev->next->next;
    delete remember;
    return t;
}

// assign set a to *this
Set_ul &Set_ul::assign(Set_ul const &a) {
    makeNull_(tail);
    if (a.tail == 0)  // if a is empty
        tail = 0;
    else
        tail = copy_(a.tail);
    return *this;
}

// return copy of list
// list must be not empty
Elem *Set_ul::copy_(const Elem *t) {
    if (t == 0) {
        return 0;
    }
    Elem *originElem = t->next;
    Elem *newTail = new Elem(t->val);
    Elem *prev = newTail;
    while (originElem != t) {
        Elem *newElem = new Elem(originElem->val);
        prev->next = newElem;
        prev = newElem;
        originElem = originElem->next;
    }
    prev->next = newTail;
    return newTail;
}

int Set_ul::member(int x) const {
    if (tail == 0)  // if list is empty
        return 0;
    return member_(tail, x);
}

int Set_ul::member_(const Elem *t, int x) {
    if (t == t->next) {  // if there is only one elem
        if (x == t->val)
            return 1;
        return 0;
    }

    if (t->val == x)  // check tail
        return 1;
    // check all elements (except tail)
    const Elem *temp = t->next;
    while (temp != t) {
        if (temp->val == x)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// print set
string Set_ul::toString() const {
    stringstream ss;
    if (tail == 0) {
        return "[]";
    }
    ss << "[";
    Elem *temp = tail->next;
    while (temp != tail) {  // for all elements in set except tail
        ss << temp->val << ", ";
        temp = temp->next;
    }
    ss << tail->val;  // print tail
    ss << "]";
    return ss.str();
}

Set_ul &Set_ul::merge(Set_ul const &a, Set_ul const &b) {
    makeNull_(tail);
    if (a.tail == 0) {
        tail = copy_(b.tail);
    } else if (b.tail == 0) {
        tail = copy_(a.tail);
    } else {
        tail = merge_(a.tail, b.tail);
    }
    return *this;
}

Elem *Set_ul::merge_(const Elem *t1, const Elem *t2) const {
    if (isDisjoint_(t1, t2)) {
        return setUnion_(t1, t2);
    }
    return 0;
}

// find max val in set
int Set_ul::maxVal() const {
    if (tail == 0)
        return 0;
    return maxVal_(tail);
}

// find max val in list
// list must be not empty
// go through all elements
//      if elem is bigger than max
//          reassign max
int Set_ul::maxVal_(const Elem *t) const {
    int max = t->val;
    Elem *temp = t->next;
    while (temp !=
           t) {  // for all elements except tail (value of tail is assigned to max, so it's not necessary to check tail)
        if (temp->val > max) {
            max = temp->val;
        }
        temp = temp->next;
    }
    return max;
}

int Set_ul::minVal() const {
    if (tail == 0)
        return 0;
    return minVal_(tail);
}

int Set_ul::minVal_(const Elem *t) const {
    int min = t->val;
    Elem *temp = t->next;
    while (temp !=
           t) {  // for all elements except tail (value of tail is assigned to max, so it's not necessary to check tail)
        if (temp->val < min) {
            min = temp->val;
        }
        temp = temp->next;
    }
    return min;
}

// if two sets are equal
int Set_ul::equal(Set_ul const &a) const {
    if (tail == 0 && a.tail == 0) {
        return 1;
    }
    if (tail == 0 || a.tail == 0)
        return 0;
    return equal_(tail, a.tail);
}

// if two lists are equal
// copy second set
// go through first set
//      if element is found in copy set
//          delete it from copy set
//      else
//          return 0
// if copy set is empty
//      return 1
int Set_ul::equal_(const Elem *t1, const Elem *t2) const {
    Elem *copyTail = copy_(t2);
    Elem *temp = t1->next;
    while (temp != t1) {  // for all elements except tail
        if (copyTail == copyTail->next) {  // if it is last elem in copy
            return 0;  // because there is at least 1 more element (tail) in t1. So lists are not equal
        }
        Elem *prev = findPrev_(copyTail, temp->val);
        if (prev)
            del_(prev);
        else
            return 0;
        temp = temp->next;
    }
    // check tail
    if (copyTail == copyTail->next && copyTail->val == t1->val)  // if copy has only 1 elem and it is equal to t1 tail
        return 1;
    return 0;
}

void Set_ul::del_(Elem *prev) const {
    Elem *delElem = prev->next;
    prev->next = prev->next->next;
    delete delElem;
}

// find in which set there is x
//
Set_ul *Set_ul::find(Set_ul &a, int x) {
    if (tail == 0 && a.tail == 0)
        return 0;
    return find_(*this, a, x);
}

Set_ul *Set_ul::find_(Set_ul &a, Set_ul &b, int x) const {
    if (a.tail != 0 && member_(a.tail, x)) {
        return &a;
    }
    if (b.tail != 0 && member_(b.tail, x)) {
        return &b;
    }
    return 0;
}

int Set_ul::isDisjoint_(const Elem *t1, const Elem *t2) {
    Elem *temp = t1->next;
    while(temp != t1) {
        if (member_(t2, temp->val)) {
            return 0;
        }
        temp = temp->next;
    }
    return !member_(t2, t1->val); // check tail
}

Elem *Set_ul::createListOfOneElem_(int x) {
    Elem *t = new Elem(x);
    t->next = t;
    return t;
}

void Set_ul::checkOther_(const Elem *t1, const Elem *t2, Elem *temp, Elem *newTail) {
    while (temp != t1) {  // for all elements in t1 (except tail)
        if (!member_(t2, temp->val)) {  // if elem is NOT is set A
            insertAfterElem_(newTail, temp->val);
        }
        temp = temp->next;
    }
}


#endif //SET_ON_BIT_FIELD_SET_H
