/**
 * Test of ClosedHash
 */

// HASH TABLE
// B - amount of classes
// x - value from set
// h(x) -> int from 0 to B - 1
// this classes are called segments
// collision - several values of set has same hash
// THIS is open hashing

// there is also closed hashing
// collision is solved with repeated hashing
// hi(x) = (h(x) + i) % B) linear hashing
// if there is no such value in table you will go down the table untill you see empty elem
// but it is important to deffer elements which were deleted and elements which were always empty

// list of bad and list of good people
// good    |     bad
//-------------------
// ab      |     bab
// ba      |     abb
// aa      |     bba
// aba     |     bb

// CLOSED hashing

// 0 |  X
// 1 |  X
// 2 |  aba
// 3 |  bab
// 4 |  aa
// 5 |  ab
// 6 |  ba
// 7 |  abb
// 8 |  X

// to differ deleted and not used:
//      paste \0 to value

#include "ClosedHash.h"
#include <stdexcept>
#include <iostream>
#include <string.h>

using namespace std;


void readList(ClosedHash<string> &dict, const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (f) {  // if file was open
        char line[15];
        while (fgets(line, 15, f) != NULL) {  // read all lines
            size_t len = strlen(line) - 1;
            line[len] = '\0';  // delete \n
            dict.insert(line);
        }
    } else {
        throw runtime_error("Could not open file");
    }
}

void move(ClosedHash<string> &to, ClosedHash<string> &from, char *name) {
    if (from.member(name)) {
        from.del(name);
        to.insert(name);
        cout << "success" << endl;
    } else {
        cout << "person is not in list" << endl;
    }
}

void printBoth(ClosedHash<string> &good, ClosedHash<string> &bad) {
    cout << "Good:" << endl;
    good.print();
    cout << "Bad:" << endl;
    bad.print();
    cout << endl;
}

int whichDict(ClosedHash<string> &good, ClosedHash<string> &bad, char *name) {
    if (good.member(name)) {
        cout << "Good" << endl;
        return 1;
    }
    if (bad.member(name)) {
        cout << "Bad" << endl;
        return 0;
    }
    cout << "person was not found in both lists" << endl;
    return -1;
}

// detect which command is it
// f(person) make person good
// u(person) make person bad
// ?(person) to which list does he/she belong
// print()  print both list
void processCommand(ClosedHash<string> &good, ClosedHash<string> &bad, char *command) {
    size_t len = strlen(command);
    char name[20];
    if (strcmp(command, "print()") == 0) {  // print lists
        printBoth(good, bad);
        return;
    }
    if (strcmp(command, "e()") == 0) {  // print lists
        return;
    }
    // get name from command
    if (command[1] == '(' && command[len - 1] == ')') {
        int i;
        for (i = 2; i < len - 1; i++) {
            name[i - 2] = command[i];
        }
        name[i - 2] = '\0';
    } else {
        cout << "wrong format" << endl;
        return;
    }
    if (command[0] == '?') {  // to which list does person belong
        whichDict(good, bad, name);
        return;
    }
    if (command[0] == 'f') {  // make person good
        move(good, bad, name);
        return;
    }
    if (command[0] == 'u') {  // make person bad
        move(bad, good, name);
        return;
    }
    cout << "command was not found" << endl;
}


int main() {
    ClosedHash<string> good = ClosedHash<string>();
    ClosedHash<string> bad = ClosedHash<string>();
    readList(good, "/home/lk/Dropbox/ITMO/programming/cpp-tasks/closed-hash/names.txt");
    printBoth(good, bad);

    char command[20];
    command[0] = 0;
    while (strcmp(command, "e()") != 0) {
        cout << "f(name) make person good" << endl;
        cout << "u(name) make person bad" << endl;
        cout << "?(name) to which list does he/she belong" << endl;
        cout << "print()  print both list" << endl;
        cout << "e() end" << endl;
        cin >> command;
        processCommand(good, bad, command);
    }

    return 0;
}