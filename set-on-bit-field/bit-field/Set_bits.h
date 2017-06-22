#ifndef SET_BITFIELD_LISTS_SET_H
#define SET_BITFIELD_LISTS_SET_H

#include <iostream>

using namespace std;

#define bitsInInt (sizeof(int)*8)

/**
 * Set which is implemented using bit field data structure
 */
class Set_bits {
public:
    Set_bits(int size = 1);

    ~Set_bits() {
        if (arr) {
            delete[] arr;
        }
    }

    Set_bits &insert(int);

    Set_bits &del(int);

    Set_bits &setUnion(Set_bits const &, Set_bits const &);

    Set_bits &intersection(Set_bits const &, Set_bits const &);

    Set_bits &difference(Set_bits const &, Set_bits const &);

    Set_bits &merge(Set_bits const &, Set_bits const &);

    Set_bits &assign(Set_bits const &);

    Set_bits * find(Set_bits &, int);

    int maxVal() const;

    int minVal() const;

    int equal(Set_bits const &) const;

    int member(int) const;

    int isDisjoint(Set_bits const &a) const;

    void makeNull();

    string toString() const;

private:
    void makeArrNull_(unsigned *, int);

    unsigned int *setUnion_(Set_bits const &, Set_bits const &);

    unsigned int *intersection_(Set_bits const &, Set_bits const &);

    unsigned int *difference_(Set_bits const &, Set_bits const &);

    int isDisjoint_(Set_bits const &, Set_bits const &) const;

    void del_(unsigned int *, int);

    void insert_(unsigned int *, int);

    void copyTail_(unsigned int *to, Set_bits const &from, int start);

    int find_(unsigned int *, int) const;

    int ifArraysEqual(unsigned *, unsigned *, int, int) const;

    int ifArrayHasValue(unsigned *, int, int) const;

    int isArrayEmpty_(unsigned *array, int sz) const;

    int isEmpty() const;

    int countArrSize(int size) const { return size / bitsInInt + 1; }

    void changeSize(int);

    static const unsigned mask = (unsigned int) 1 << (bitsInInt - 1); // 10000000
    unsigned int *arr = 0;
    int size;
    int arrSize;
};

// parameters:
//		size - maximum value in array (minimum is always 1)
Set_bits::Set_bits(int sz) {
    if (sz < 1) {
        cout << "size must be > 1. Set_bits will be created with default size = 1" << endl;
        sz = 1;
    }
    size = sz;
    arrSize = countArrSize(size);
    arr = new unsigned int[arrSize];
    makeNull();
}

// assign zero to all elements of array
void Set_bits::makeNull() {
    makeArrNull_(arr, arrSize);
}

// make all elements equal to 0
void Set_bits::makeArrNull_(unsigned *array, int sz) {
    for (int i = 0; i < sz; i++)
        array[i] = 0;
}

// check if there is any elements in set
int Set_bits::isArrayEmpty_(unsigned *array, int sz) const {
    for (int i = 0; i < sz; i++) {  // for all elements
        if (array[i] != 0)
            return 0;
    }
    return 1;
}

// insert element to set
Set_bits &Set_bits::insert(int x) {
    if (x > 0 && x <= size) {  // if x in array range
        insert_(arr, x);
    }
    return *this;
}

// insert elem to array
void Set_bits::insert_(unsigned int *array, int x) {
    x--;
    unsigned mask = Set_bits::mask; // 100000...
    int arrIndex = x / bitsInInt;  // count which element of array is responsible for this number
    int shift = x % bitsInInt;
    mask = mask >> shift;  // 00010000.....
    array[arrIndex] = array[arrIndex] | mask;  // insert number to set
}

// delete element from set
Set_bits &Set_bits::del(int x) {
    if (x > 0 && x <= size) {  // if x in array range
        del_(arr, x);
    }
    return *this;
}

// delete element from array
// x must be in range
void Set_bits::del_(unsigned int *array, int x) {
    x--;
    unsigned mask = Set_bits::mask; // 100000...
    int arrIndex = x / bitsInInt;  // count which element of array is responsible for this number
    int shift = x % bitsInInt;
    mask = mask >> shift;  // 00010000.....
    mask = ~mask;  // 11101111.... for & operation
    array[arrIndex] = array[arrIndex] & mask;  // delete number from set
}

int Set_bits::isEmpty() const {
    for (int i = 0; i < arrSize; i++)  // find if array is empty
        if (arr[i] != 0)
            return 0;
    return 1;
}

/**
 * @return string representation of set
 */
string Set_bits::toString() const {
    if (isEmpty()) {
        return "[]";
    }

    stringstream ss;
    ss << "[";

    int isFirst = 1;
    unsigned mask = Set_bits::mask;  // 100000...
    for (int i = 0; i < arrSize - 1; i++) {  // for all elements in array (except last)
        for (int j = 0; j < bitsInInt; j++) {
            if (arr[i] & (mask >> j)) {
                if (!isFirst) {
                    ss << ", ";
                }
                ss << i * bitsInInt + j + 1;
                isFirst = 0;
            }
        }
    }
    int i = arrSize - 1;  // for last element in array
    for (int j = 0; j < bitsInInt; j++) {
        int num = i * bitsInInt + j + 1;
        if (num <= size && arr[i] & (mask >> j)) { // check if num < size
            ss << ", ";
            ss << num;
        }
    }
    ss << "]";
    return ss.str();
}

// ! this function does not make all elements = 0
void Set_bits::changeSize(int newSize) {
    delete[] arr;  // delete existing array
    arr = 0;
    size = newSize;
    arrSize = countArrSize(size);
}

// union of two sets
// assign result to *this
Set_bits &Set_bits::setUnion(Set_bits const &a, Set_bits const &b) {
    changeSize(max(a.size, b.size));  // delete existing data and make new size array
    arr = setUnion_(a, b);
    return *this;
}

unsigned int *Set_bits::setUnion_(Set_bits const &a, Set_bits const &b) {
    int newArrSize = max(a.arrSize, b.arrSize);
    unsigned int *newArr = new unsigned int[newArrSize];

    int minArrSize = min(a.arrSize, b.arrSize);  // size for loop
    for (int i = 0; i < minArrSize; i++) {
        newArr[i] = a.arr[i] | b.arr[i];
    }
    if (a.arrSize > b.arrSize)  // copy tail from bigger set
        copyTail_(newArr, a, minArrSize);
    else
        copyTail_(newArr, b, minArrSize);

    return newArr;
}

void Set_bits::copyTail_(unsigned int *to, Set_bits const &from, int start) {
    for (int i = start; i < from.arrSize; i++) {  // for last arr-elements in bigger set
        to[i] = from.arr[i];
    }
}

// union of two sets
// assign result to *this
Set_bits &Set_bits::intersection(Set_bits const &a, Set_bits const &b) {
    changeSize(max(a.size, b.size));  // delete existing data in *this and make new size array
    arr = intersection_(a, b);
    return *this;
}

// union of two sets
// create new array
unsigned int *Set_bits::intersection_(Set_bits const &a, Set_bits const &b) {
    int newArrSize = max(a.arrSize, b.arrSize);
    unsigned int *newArr = new unsigned int[newArrSize];
    makeArrNull_(newArr, newArrSize);  // not all elements of array will get new values, so makeNull is necessary

    int minArrSize = min(a.arrSize, b.arrSize);  // size for loop
    for (int i = 0; i < minArrSize; i++) {
        newArr[i] = a.arr[i] & b.arr[i];
    }
    return newArr;
}


Set_bits &Set_bits::difference(Set_bits const &a, Set_bits const &b) {
    changeSize(max(a.size, b.size));  // delete existing data and make new size array
    arr = difference_(a, b);
    return *this;
}

unsigned int *Set_bits::difference_(Set_bits const &a, Set_bits const &b) {
    int newArrSize = max(a.arrSize, b.arrSize);
    unsigned int *newArr = new unsigned int[newArrSize];
    makeArrNull_(newArr, newArrSize);  // not all elements of array will get new values, so makeNull is necessary

    int minArrSize = min(a.arrSize, b.arrSize);  // size for loop
    for (int i = 0; i < minArrSize; i++) {
        newArr[i] = (a.arr[i] | b.arr[i]) & ~b.arr[i];
    }
    if (a.arrSize > b.arrSize)  // if any elements was left
        for (int i = b.arrSize; i < a.arrSize; i++)
            newArr[i] = a.arr[i];
    return newArr;
}


Set_bits &Set_bits::merge(Set_bits const &a, Set_bits const &b) {
    changeSize(max(a.size, b.size));  // delete existing data and make new size array
    arr = setUnion_(a, b);
    return *this;
}


int Set_bits::isDisjoint(Set_bits const &a) const {
    return isDisjoint_(*this, a);
}

/**
 * Find in which set element is found.
 * First set is 'this'
 * Sets must be disjoint
 * @param a second set
 * @param x wanted element
 * @return pointer to set where element was found (0 if not found)
 */
Set_bits * Set_bits::find(Set_bits &a, int x) {
    if (x > 0 && x <= size && find_(arr, x))
        return this;
    if (x > 0 && x <= a.size && find_(a.arr, x))
        return &a;
    return 0;
}

// if value is in array
int Set_bits::find_(unsigned int *array, int x) const {
    x--;
    unsigned mask = Set_bits::mask;  // 10000...
    int arrIndex = x / bitsInInt;  // count which element of array is responsible for this number
    int shift = x % bitsInInt;
    mask = mask >> shift;  // 00010000.....
    if ((array[arrIndex] & mask) != 0) { // if this number exist
        return 1;
    }
    return 0;
}

// assign one set to another
Set_bits &Set_bits::assign(Set_bits const &a) {
    if (arrSize != a.arrSize) {  // if array sizes are different
        arrSize = a.arrSize;  // copy info about size
        delete[] arr;  // delete previous arr
        arr = new unsigned[arrSize];  // create new arr
    }
    size = a.size;
    for (int i = 0; i < arrSize; i++) {  // copy all data from another array
        arr[i] = a.arr[i];
    }
    return *this;
}

/**
 * Get max value in set
 * @return max value in set. 0 if set is empty
 */
int Set_bits::maxVal() const {
    unsigned mask = Set_bits::mask;  // 10000...
    int initShift = size - (arrSize - 1) * bitsInInt - 1;
    for (int shift = initShift; shift >= 0; shift--) {  // for last elem in array
        if ((arr[arrSize - 1] & mask >> shift) != 0)
            return (arrSize - 1) * bitsInInt + shift + 1;
    }
    for (int i = arrSize - 2; i >= 0; i--) {
        for (int shift = bitsInInt - 1; shift >= 0; shift--) {  // for other elems in array
            if ((arr[i] & mask >> shift) != 0)
                return i * bitsInInt + shift + 1;
        }
    }
    return 0;
}

/**
 * Get minimal value in set
 * @return minimal value in set. 0 if set is empty
 */
int Set_bits::minVal() const {
    unsigned mask = Set_bits::mask;  // 10000...
    for (int i = 0; i < arrSize - 1; i++) {  // for all array elements except last one
        for (int shift = 0; shift < bitsInInt - 1; shift++) {  // for other elems in array
            if ((arr[i] & mask >> shift) != 0)
                return i * bitsInInt + shift + 1;
        }
    }
    int lastShift = size - (arrSize - 1) * bitsInInt;
    for (int shift = 0; shift < lastShift; shift++) {  // for last elem in array
        if ((arr[arrSize - 1] & mask >> shift) != 0)
            return (arrSize - 1) * bitsInInt + shift;
    }

    return 0;
}

// return 1 if sets are equal
//      0 if not
// find minimum arrSize and size
// check everything between 0 and minArrSize
// check that there is no elements after minArraySize in bigger set
int Set_bits::equal(Set_bits const &a) const {
    int minArrSize = min(arrSize, a.arrSize);
    if (ifArraysEqual(arr, a.arr, 0, minArrSize) == 0)  // if first part is not equal
        return 0;
    unsigned *biggerArr;
    int biggerArrSize;
    if (arrSize == a.arrSize)
        return 1;
    if (arrSize > a.arrSize) {  // if *this array is bigger
        biggerArr = arr;
        biggerArrSize = arrSize;
    } else {
        biggerArr = a.arr;
        biggerArrSize = a.arrSize;
    }
    if (ifArrayHasValue(biggerArr, minArrSize, biggerArrSize))  // if it has any value (which other array does not have)
        return 0;
    return 1;
}

int Set_bits::ifArraysEqual(unsigned *arr1, unsigned *arr2, int from, int to) const {
    for (int i = from; i < to; i++) {
        if (arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}

// check if there is any numbers in array in particular range
int Set_bits::ifArrayHasValue(unsigned *array, int from, int to) const {
    for (int i = from; i < to; i++) {
        if (array[i] != 0)
            return 0;
    }
    return 1;
}

// if x in set
int Set_bits::member(int x) const {
    if (x <= 0 || x > size)
        return 0;
    return find_(arr, x);
}

/**
 * is two sets disjoint
 * Implementation:
 * check if two sets have intersection from 0 to min(size-of-first-set, size-of-second-set)
 * @return 1 if two sets are disjoint, otherwise 0
 */
int Set_bits::isDisjoint_(Set_bits const &a, Set_bits const &b) const {
    int minArraySize = min(a.arrSize, b.arrSize);
    for (int i = 0; i < minArraySize; i++) { // all meaningless bits (which are bigger than size) are equal to 0
        if (a.arr[i] & b.arr[i] != 0) { // if two sets have any common elements
            return 0;
        }
    }
    return 1;
}


#endif //SET_BITFIELD_LISTS_SET_H
