//
// Created by Liudmila Kornilova on 20.05.17.
//

#ifndef PARTIALLY_ORDERED_SET_NODEOFBIGGERELEMSLIST_H
#define PARTIALLY_ORDERED_SET_NODEOFBIGGERELEMSLIST_H

class Elem;


class NodeOfBiggerElemsList {
public:
    NodeOfBiggerElemsList *next = 0;

    NodeOfBiggerElemsList(Elem *elem) {
        biggerElem = elem;
    }

    Elem *getBiggerElem() const {
        return biggerElem;
    }

private:

    Elem *biggerElem;
};


#endif //PARTIALLY_ORDERED_SET_NODEOFBIGGERELEMSLIST_H
