//
// Created by Liudmila Kornilova on 20.05.17.
//

#ifndef PARTIALLY_ORDERED_SET_ELEM_H
#define PARTIALLY_ORDERED_SET_ELEM_H

#include "NodeOfBiggerElemsList.h"

class Elem {
public:
    Elem *next = 0;

    Elem(int val) {
        Elem::val = val;
    }

    void addBiggerElem(Elem *biggerElem);

    int getVal() const;

    void incNumOfSmallerElems() {
        numOfSmallerElems++;
    }

    void decNumOfSmallerElems() {
        numOfSmallerElems--;
    }

    int getNumOfSmallerElems() const {
        return numOfSmallerElems;
    }

    void clearListOfBiggerElems();

private:
    int val;
    NodeOfBiggerElemsList *firstNode = 0;
    int numOfSmallerElems = 0;

    NodeOfBiggerElemsList *getLastNode_() const;

    void appendList_(Elem *pElem, NodeOfBiggerElemsList *lastNode);
};

void Elem::addBiggerElem(Elem *biggerElem) {
    if (firstNode == 0) {
        firstNode = new NodeOfBiggerElemsList(biggerElem);
        return;
    }
    NodeOfBiggerElemsList *lastNode = getLastNode_();
    appendList_(biggerElem, lastNode);
}

NodeOfBiggerElemsList *Elem::getLastNode_() const {
    NodeOfBiggerElemsList *prev = firstNode;
    NodeOfBiggerElemsList *next = firstNode->next;
    while (next != 0) {
        prev = next;
        next = next->next;
    }
    return prev;
}

void Elem::appendList_(Elem *biggerElem, NodeOfBiggerElemsList *lastNode) {
    lastNode->next = new NodeOfBiggerElemsList(biggerElem);
}

int Elem::getVal() const {
    return val;
}

/**
 * Clear list of bigger elements
 * for each node in list of bigger elements:
 * - decrease numOfSmaller in bigger element
 * - delete node
 * assign 0 to firstNode
 */
void Elem::clearListOfBiggerElems() {
    NodeOfBiggerElemsList *tempNode = firstNode;
    while (tempNode) {
        tempNode->getBiggerElem()->decNumOfSmallerElems();
        NodeOfBiggerElemsList *del = tempNode;
        tempNode = tempNode->next;
        delete del;
    }
    firstNode = 0;
}


#endif //PARTIALLY_ORDERED_SET_ELEM_H
