//
// Created by Liudmila Kornilova on 13.05.17.
//

#ifndef QUEUE_WITH_PRIORITIES_PRIORITIZEDQUEUE_H
#define QUEUE_WITH_PRIORITIES_PRIORITIZEDQUEUE_H

#include <iostream>

struct Elem {
    Elem();

    Elem(int value, int priority);

    friend std::ostream & operator <<(std::ostream & out, const Elem & elem);

    int val;
    int prior;
};


class PriorityQueue {
public:
    void insert(int newVal, int newPrior);
    void print() const;
    int isEmpty() const;
    void makeNull();
    int deleteMin();
    int isFull() const; // for test
    int checkCorrectness(); // for test
    int size() const; // for test
    int hasValue(int val) const; // for test

private:
    void insertToLast(int newVal, int newPrior);
    int getParentPos(int child) const;
    int getLeftChild(int parent) const;
    int getRightChild(int parent) const;
    void swap(int pos1, int pos2);
    int ifExists(int newVal) const;
    void moveDown();
    void moveUp();

    int last = -1; // position of last element
    const static int SIZE = 10;
    Elem arr[SIZE];
};


#endif //QUEUE_WITH_PRIORITIES_PRIORITIZEDQUEUE_H
