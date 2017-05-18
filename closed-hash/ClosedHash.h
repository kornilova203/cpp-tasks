//
// Created by Liudmila Kornilova on 12.05.17.
//

#ifndef DICTIONARY_CLOSEDHASH_H
#define DICTIONARY_CLOSEDHASH_H

#include <iostream>
//#include <string>

//using namespace std;


template<class T>
class ClosedHash {
public:
    void insert(const T val) {

        int hash = hashCode_(val);

        if (hashTable[hash] == 0) {  // if this element of hash table is empty
            insertToPos_(hash, val);
            return;
        }
        int pos = findPosForNew_(hash, val);
        if (pos != -1) {  // if place was found
            insertToPos_(pos, val);
        }
    }

    /**
     * Delete element from table
     * @param val
     */
    void del(const T val) {
        int pos = find_(val);
        if (pos != -1) {
            /*
             * if assign 0 to hashTable[val] it will be impossible to understand
             * if it was deleted or never assinged
             */
            hashTable[pos] = EMPTY_ELEM;
        }
    }

    int member(const T val) const {
        if (find_(val) != -1) {  // if name is in table
            return 1;
        }
        return 0;
    }

    /**
     * Clear hash-table
     */
    void makeNull() {
        for (int i = 0; i < B; i++) {  // for all elements in hash table
            if (hashTable[i] != 0) {  // if value exists
                delete[] hashTable[i];
                hashTable[i] = 0;
            }
        }
    }

    int size() {
        int size = 0;
        for (int i = 0; i < B; i++) {
            if (hashTable[i] != 0 && hashTable[i] != EMPTY_ELEM) {
                size++;
            }
        }
        return size;
    }

    friend std::ostream& operator<<(std::ostream& stream, ClosedHash closedHash) {
        int isEmpty = 1;
        for (int i = 0; i < B; i++) {  // for all elements in hash table
            if (closedHash.hashTable[i] != 0 && closedHash.hashTable[i] != closedHash.EMPTY_ELEM) {  // if name is not empty
                isEmpty = 0;
                stream << *(closedHash.hashTable[i]) << std::endl;
            }
        }
        if (isEmpty == 1)
            stream << "dict is empty";
        return stream;
    }

    T* get(const T key) const {
        int pos = find_(key);
        if (pos == -1) {
            throw std::runtime_error("There is no such value in table");
        }
        return hashTable[pos];
    }

private:

    static const int B = 100;
    T *hashTable[B];
    T * const EMPTY_ELEM = new T();

//    int countKey_(const char *name) const;

    int getNext_(int pos) const {
        return (pos + 1) % B;
    }

    int find_(const T val) const {
        int hash = hashCode_(val);
        // check first:
        if (hashTable[hash] == 0) {  // if there is no names with such hash
            return -1;
        }
        if (isEqual_(*hashTable[hash], val)) {  // if name was found
            return hash;
        }
        // check all
        int pos = getNext_(hash);
        while (pos != hash) {  // for all elements
            if (hashTable[pos] == 0) {  // if there is no more names with this hash
                return -1;
            }
            if (isEqual_(*hashTable[pos], val)) {  // if name was found
                return pos;
            }
            pos = getNext_(pos);
        }
        // now hash table does not have gaps and name was not found
        return -1;
    }

    int hashCode_(const T val) const {
        std::hash<T> hashCode;
        return (int) (hashCode(val) % B);
    }

    void insertToPos_(int hash, const T val) {
        hashTable[hash] = new T(val);
    }

//    void insertToPos_(int hash, const string val) {
//        hashTable[hash] = new string(val);
//    }

    int findPosForNew_(int hash, const T val) {
        int firstUsedAndEmpty = -1;  // element which was used but now empty
        int pos = getNext_(hash);
        // check first element (it cannot be checked in loop)
        if (isEqual_(*hashTable[hash], val)) {  // if name is already in list
            return -1;
        }
        if (hashTable[hash] == EMPTY_ELEM) {  // find first elem which was used but now empty
            firstUsedAndEmpty = hash;
        }
        while (pos != hash) {  // for all elements in hash table
            if (hashTable[pos] == 0) {  // if first empty elem is found
                if (firstUsedAndEmpty == -1) {  // if there was no used elements
                    return pos;
                }
                return firstUsedAndEmpty;
            }
            if (hashTable[pos] == EMPTY_ELEM &&
                firstUsedAndEmpty == -1) {  // find first elem which was used but now empty
                firstUsedAndEmpty = pos;
            }
            if (isEqual_(*hashTable[pos], val)) {  // if name is already in list
                return -1;
            }
            pos = getNext_(pos);
        }
        // in this situation all elements were at least ones assigned, but equal name was not found
        if (firstUsedAndEmpty == -1) {  // if there is no empty elements
            return -1;
        }
        return firstUsedAndEmpty;
    }

    int isEqual_(const T val1, const T val2) const {
        return val1 == val2;
    }
};


#endif //DICTIONARY_CLOSEDHASH_H
