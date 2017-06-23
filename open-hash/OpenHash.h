
#ifndef DICTIONARY_OPENHASH_H
#define DICTIONARY_OPENHASH_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "Elem.h"

class OpenHash {
public:
    OpenHash(const std::string fileName);
    void insert(const char *name);
    void del(const char *name);  // delete name from hash table
    int member(const char *name) const;
    std::string toString() const;
    void makeNull();
private:
    int getHash_(const char *name_) const;
    int countKey_(const char *name_) const;
    void insertAfterElem_(Elem *prev, const char *name);
    void createAndAssignName_(Elem &elem, const char *name);
    void delTableElem_(Elem * elem);
    void delNextElem_(Elem *prev);
    void clearList_(Elem &elem);

    static const int B = 10;
    Elem hashTable[B];
};

OpenHash::OpenHash(const std::string fileName){
    std::fstream input(fileName);
    if (input) {  // if file was open
        char line[15];
        while (input >> line) {  // read line by line
            size_t len = strlen(line) - 1;
            if (line[len] == '\n') {
                line[len] = '\0';  // delete \n
            }
            insert(line);
        }
    } else
        std::cout << "file was not open";
}

int OpenHash::countKey_(const char *name) const {
    int key = 0;
    for (int i = 0; name[i] != 0; i++) {  // sum codes of all characters
        key += name[i];
    }
    return key;
}

// count hash for string
int OpenHash::getHash_(const char *name) const {
    return countKey_(name) % B;
}

// insert data to hash table
// count hash
// if there is no such element in hashTable
//      insert new element
void OpenHash::insert(const char *name) {
    int hash = getHash_(name);
    if (hashTable[hash].name == 0) {  // if this element of hash table is empty
        createAndAssignName_(hashTable[hash], name);
        return;
    }
    Elem *temp = &hashTable[hash];
    Elem *next = temp->next;
    // check elem in table:
    if (strcmp(temp->name, name) == 0) {  // if name is already in list
        return;
    }
    while(next != 0) {  // for all elements in this sequence
        if (strcmp(next->name, name) == 0) {  // if name is already in list
            return;
        }
        temp = temp->next;
        next = next->next;
    }
    // now temp is last element in list (temp->next == 0)
    insertAfterElem_(temp, name);
}

// create char array for element
// copy name there
void OpenHash::createAndAssignName_(Elem &elem, const char *name) {
    elem.name = new char[15];
    strcpy(elem.name, name);  // copy new name there
}

// create new Elem after existing Elem
void OpenHash::insertAfterElem_(Elem *prev, const char *name) {
    Elem *newElem = new Elem(name);
    prev->next = newElem;
}

// print all elements in hash table
// for all elements in hash table
//      if name is not empty
//          print name
//          while next is not empty
//              move to next
//              print name
std::string OpenHash::toString() const {
    std::stringstream ss;
    int isEmpty = 1;
    for (int i = 0; i < B; i++) {  // for all elements in hash table
        if (hashTable[i].name != 0) {  // if name is not empty
            isEmpty = 0;
            const Elem *temp = &hashTable[i];
            ss << temp->name << "\n";
            while (temp->next != 0) {
                temp = temp->next;
                ss << temp->name << "\n";
            }
        }
    }
    if (isEmpty == 1)
        return "";
    return ss.str();
}

// delete hash from table
void OpenHash::del(const char *name) {
    int hash = getHash_(name);
    if (hashTable[hash].name == 0) {  // if there is no elements in table with such hash
        return;
    }
    Elem *temp = &hashTable[hash];
    if (strcmp(temp->name, name) == 0) {  // if name is in array
        delTableElem_(temp);
        return;
    }
    Elem * prev = temp;
    temp = temp->next;
    while(temp != 0) {  // for all elements in this sequence
        if (strcmp(temp->name, name) == 0) {  // if name is in list
            delNextElem_(prev);
            return;
        }
        temp = temp->next;
        prev = prev->next;
    }
}

// delete hashTable elem
// if there is no other elems with this hash
//      delete name
// else
//      copy name and next from next list elem
//      delete next list elem
void OpenHash::delTableElem_(Elem *elem) {
    if (elem->next == 0) {  // if there is no elements with equal hash
        delete[] elem->name;
        elem->name = 0;
        return;
    }
    Elem *next = elem->next;
    strcpy(elem->name, next->name);  // copy name to table elem
    delNextElem_(elem);  // delete first elem in list (it's data was copied to hashtable elem)
}

// delete element in list of elements
void OpenHash::delNextElem_(Elem *prev) {
    Elem *delElem = prev->next;
    prev->next = delElem->next;
    delete delElem;  // finally delete element
}

// if name is in hash table
int OpenHash::member(const char *name) const {
    int hash = getHash_(name);
    if (hashTable[hash].name == 0) {  // if there is no elements in table with such hash
        return 0;
    }
    const Elem *temp = &hashTable[hash];
    while(temp != 0) {  // for all elements in this sequence
        if (strcmp(temp->name, name) == 0) {  // if name is in list
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// clear hash table
// for all elements in table
//      clear list
//      delete name
void OpenHash::makeNull() {
    for (int i = 0; i < B; i++) {  // for all elements in hash table
        if (hashTable[i].next != 0) {
            clearList_(hashTable[i]);
        }
        if (hashTable[i].name != 0) {  // if name exists
            delete[] hashTable[i].name;
            hashTable[i].name = 0;
        }
    }
}

void OpenHash::clearList_(Elem &elem) {
    Elem *temp = elem.next;
    while (temp) {  // for all elements in list
        Elem *next = temp->next;
        delete temp;
        temp = next;
    }
    elem.next = 0;
}


#endif //DICTIONARY_OPENHASH_H
