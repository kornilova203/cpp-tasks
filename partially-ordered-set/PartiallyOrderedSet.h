//
// Created by Liudmila Kornilova on 20.05.17.
//

#ifndef PARTIALLY_ORDERED_SET_PARTIALLYORDEREDSET_H
#define PARTIALLY_ORDERED_SET_PARTIALLYORDEREDSET_H

#include <fstream>
#include <iostream>
#include "Elem.h"


class PartiallyOrderedSet {
public:
    PartiallyOrderedSet(std::string fileName);

    std::string getOrder() const;

private:
    Elem *firstUnsortedElem = 0;

    Elem *lastSortedElem = 0;

    Elem *findOrCreateElem_(int val);

    void addRelation_(int smallerVal, int biggerVal);

    Elem *createElem_(int val);

    Elem *appendToList(int i, Elem *pElem);

    void sort_();

    Elem *getElemBeforeSmallest_() const;

    void removeFromUnsorted_(Elem *pElem);

    void removeFirstFromUnsorted_();

    void appendToSorted_(Elem *elem);

    void clearBothLists_();

    void clearSorted_();

    void clearUnsorted_();
};

PartiallyOrderedSet::PartiallyOrderedSet(std::string fileName) {
    std::fstream input(fileName);
    if (input) {
        int isEmpty = 1;
        int a;
        int b;
        while (input >> a && input >> b) {
            isEmpty = 0;
            addRelation_(a, b);
        }
        if (isEmpty) {
            throw std::runtime_error("File is empty");
        }
        sort_();
    } else {
        throw std::runtime_error("File not found");
    }
}

void PartiallyOrderedSet::addRelation_(int smallerVal, int biggerVal) {
    Elem *smaller = findOrCreateElem_(smallerVal);
    Elem *bigger = findOrCreateElem_(biggerVal);
    bigger->incNumOfSmallerElems();
    smaller->addBiggerElem(bigger);
}

/**
 * Return pointer to elem which contains val
 * if elem does not exists - create it
 * @param val value of elem
 * @return pointer to elem
 */
Elem *PartiallyOrderedSet::findOrCreateElem_(int val) {
    if (firstUnsortedElem == 0) { // if list of elems is empty
        return createElem_(val);
    }
    Elem *elem = firstUnsortedElem;
    Elem *prev = 0;
    while (elem != 0) { // for all existing elems
        if (elem->getVal() == val) { // elem was found in list
            return elem;
        }
        prev = elem;
        elem = elem->next;
    }
    return appendToList(val, prev); // if elem was not found
}

Elem *PartiallyOrderedSet::createElem_(int val) {
    return firstUnsortedElem = new Elem(val);
}

Elem *PartiallyOrderedSet::appendToList(int val, Elem *prev) {
    return prev->next = new Elem(val);
}

std::string PartiallyOrderedSet::getOrder() const {
    if (lastSortedElem == 0) {
        return "Order was not found";
    }
    std::string out = "";
    Elem *temp = lastSortedElem->next;
    while (temp != lastSortedElem) {
        out += std::to_string(temp->getVal()) + " ";
        temp = temp->next;
    }
    out += std::to_string(lastSortedElem->getVal());
    return out;
}

/**
 * Sort partially-ordered set
 * 1. find element with 0 smaller element
 * 2. go to list of bigger element and decrease number of smaller element
 * 3. delete element from list
 */
void PartiallyOrderedSet::sort_() {
    while (firstUnsortedElem != 0) { // while not all elements are sorted
        Elem *smallestElem;
        if (firstUnsortedElem->getNumOfSmallerElems() == 0) {
            smallestElem = firstUnsortedElem;
            removeFirstFromUnsorted_();
        } else {
            Elem *elemBeforeSmallest = getElemBeforeSmallest_();
            if (elemBeforeSmallest == 0) { // if there is no smallest elem
                clearBothLists_();
                return;
            }
            smallestElem = elemBeforeSmallest->next;
            removeFromUnsorted_(elemBeforeSmallest);
        }
        appendToSorted_(smallestElem);
    }
}

/**
 * Get element which goes before smallest element
 *
 * @return element which goes before smallest element
 *         0 if smallest elem was not found
 */
Elem *PartiallyOrderedSet::getElemBeforeSmallest_() const {
    Elem *prev = firstUnsortedElem;
    Elem *next = firstUnsortedElem->next;
    while (next) {
        if (next->getNumOfSmallerElems() == 0) { // if it is the smallest elem
            return prev;
        }
        prev = next;
        next = next->next;
    }
    return 0;
}

void PartiallyOrderedSet::removeFromUnsorted_(Elem *elemBeforeSmallest) {
    Elem *removingElem = elemBeforeSmallest->next;
    elemBeforeSmallest->next = removingElem->next;

    removingElem->next = 0;
    removingElem->clearListOfBiggerElems();
}

void PartiallyOrderedSet::removeFirstFromUnsorted_() {
    Elem *removingElem = firstUnsortedElem;
    firstUnsortedElem = firstUnsortedElem->next;

    removingElem->next = 0;
    removingElem->clearListOfBiggerElems();
}

void PartiallyOrderedSet::appendToSorted_(Elem *elem) {
    if (lastSortedElem == 0) {
        lastSortedElem = elem;
        lastSortedElem->next = lastSortedElem;
    } else {
        elem->next = lastSortedElem->next;
        lastSortedElem->next = elem;
        lastSortedElem = elem;
    }
}

void PartiallyOrderedSet::clearBothLists_() {
    if (lastSortedElem != 0) {
        clearSorted_();
    }
    clearUnsorted_();
}

void PartiallyOrderedSet::clearSorted_() {
    Elem *temp = lastSortedElem->next;
    while (temp != lastSortedElem) {
        Elem *del = temp;
        temp = temp->next;
        delete del;
    }
    delete lastSortedElem;
    lastSortedElem = 0;
}

void PartiallyOrderedSet::clearUnsorted_() {
    Elem *temp = firstUnsortedElem;
    while (temp) {
        Elem *del = temp;
        temp = temp->next;
        delete del;
    }
    firstUnsortedElem = 0;
}


#endif //PARTIALLY_ORDERED_SET_PARTIALLYORDEREDSET_H
