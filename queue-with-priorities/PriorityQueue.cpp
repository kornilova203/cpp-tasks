//
// Created by Liudmila Kornilova on 13.05.17.
//

#include "PriorityQueue.h"
#include <math.h>

using namespace std;

// Insert
// 1. insert element on most left position on bottom layer. If bottom layer is full. Add new layer.
// 2. Swap element if son has smaller priority
void PriorityQueue::insert(int newVal, int newPrior) {
    if (last + 1 == SIZE) { // if queue is full
        cout << "Queue is full" << endl;
        return;
    }
    if (ifExists(newVal)) { // if element of set is on list
        return;
    }
    insertToLast(newVal, newPrior);
    moveUp();
}

void PriorityQueue::makeNull() {
    last = -1;
}

int PriorityQueue::isEmpty() const {
    return last == -1;
}

int PriorityQueue::isFull() const { // for test
    return last == SIZE - 1;
}

int PriorityQueue::size() const { // for test
    return last + 1;
}

int PriorityQueue::hasValue(int val) const { // for test
    return ifExists(val);
}

void PriorityQueue::moveUp() {
    int posOfNew = last;
    int parent = getParentPos(posOfNew);
    while (arr[posOfNew].prior < arr[parent].prior) {
        swap(posOfNew, parent);
        posOfNew = parent;
        parent = getParentPos(posOfNew);
    }
}

void PriorityQueue::insertToLast(int newVal, int newPrior) {
    last++;
    arr[last].val = newVal;
    arr[last].prior = newPrior;
}

// get position of parent
int PriorityQueue::getParentPos(int child) const {
    if (child == 0) { // parent of root is root
        return 0;
    }
    return (child - 1) / 2;
}

// swap two elements in array
void PriorityQueue::swap(int pos1, int pos2) {
    Elem temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

// if value is already in set
int PriorityQueue::ifExists(int newVal) const {
    for (int i = 0; i <= last; i++) { // for all elements in array
        if (arr[i].val == newVal) { // if value was found
            return 1;
        }
    }
    return 0;
}

void PriorityQueue::print() const {
    int print_pos[last + 1];
    int i, j, k, pos, x = 1, level = 0;
    int LINE_WIDTH = 70;

    print_pos[0] = 0;
    for (i = 0, j = 1; i < last + 1; i++, j++) {
        pos = (int) (print_pos[(i - 1) / 2] + (i % 2 ? -1 : 1) * (LINE_WIDTH / (pow(2, level + 1)) + 1));

        for (k = 0; k < pos - x - 2; k++) {
            printf("%c", i == 0 || i % 2 ? ' ' : '-');
        }

        cout << arr[i];

        if ((i % 2) && (i + 1) == last + 1) {  // if it is last elemet and it is on left
            for (k = 0; k < pos - x - 2; k++) {
                cout << '-';
            }
        }

        print_pos[i] = x = pos + 1;

        if (j == pow(2, level)) {
            printf("\n");
            level++;
            x = 1;
            j = 0;
        }
    }
    cout << endl << endl;

}

// 1. Search most right element on bottom level
// 2. Copy it to root
// 3. Swap nodes till algorithm finds new position for this node. (compare to left nodes. If it is smaller - swap)
// 4. Return deleted root
int PriorityQueue::deleteMin() {
    int value = arr[0].val;
    arr[0] = arr[last--]; // copy most right element to root
    moveDown();

    return value;
}
void PriorityQueue::moveDown() {
    int parent = 0;
    int leftChild = getLeftChild(parent);
    int rightChild = getRightChild(parent);
    while (arr[parent].prior > arr[leftChild].prior ||
           arr[parent].prior > arr[rightChild].prior) {
        if (arr[leftChild].prior < arr[rightChild].prior) {
            swap(parent, leftChild);
            parent = leftChild;
        }
        else {
            swap(parent, rightChild);
            parent = rightChild;
        }
        leftChild = getLeftChild(parent);
        rightChild = getRightChild(parent);
    }
}


int PriorityQueue::getLeftChild(int parent) const {
    int child = parent * 2 + 1;
    if (child > last) { // if it is out of range
        return parent;
    }
    return child;
}

int PriorityQueue::getRightChild(int parent) const {
    int child = parent * 2 + 2;
    if (child > last) { // if it is out of range
        return parent;
    }
    return child;
}

// check if all parents have priority which is less than children's priority
// 1 - ok
// 0 - fail
int PriorityQueue::checkCorrectness() {
    for (int i = 0; i < last; i++) {
        int leftChild = getLeftChild(i);

        if (leftChild != i) {
            if (leftChild <= last) {
                if (arr[i].prior > arr[leftChild].prior) {
                    return 0;
                }
            }
            int rightChild = leftChild + 1;
            if (rightChild <= last) {
                if (arr[i].prior > arr[rightChild].prior) {
                    return 0;
                }
            }
        }

    }
    return 1;
}

std::ostream &operator<<(std::ostream &out, const Elem &elem) {
    out << elem.prior << "(" << elem.val << ")";
    return out;
}

Elem::Elem() {
        val = 0;
        prior = 0;
}

Elem::Elem(int value, int priority) {
        val = value;
        prior = priority;
}
