//
// Created by Liudmila Kornilova on 16.05.17.
//

#ifndef MULTIPLETOMULTIPLE_STUDENT_H
#define MULTIPLETOMULTIPLE_STUDENT_H

#include <iostream>
#include "ConnectionEntry.h"
#include "BaseEntry.h"

using namespace std;

class StudentEntry : BaseEntry {
public:
    StudentEntry() {
        name = "";
    }

    StudentEntry(const string name_) {
        name = name_;
    }

    int operator==(const StudentEntry &s) const {
        return name == s.name;
    }

    friend ostream &operator<<(ostream &stream, StudentEntry s) {
        stream << s.name;
        return stream;
    }

    const string &getName() const {
        return name;
    }

    ConnectionEntry *entry = 0;

private:
    string name;

};

// hash code is for adding student to hash-table
namespace std {
    template<>
    class hash<StudentEntry> {
    public:
        size_t operator()(const StudentEntry &s) const {
            size_t key = 0;
            for (const char &c : s.getName()) {
                key += c;
            }
            return key;
        }
    };
}

#endif //MULTIPLETOMULTIPLE_STUDENT_H
