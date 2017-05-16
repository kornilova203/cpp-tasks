//
// Created by Liudmila Kornilova on 16.05.17.
//

#ifndef MULTIPLETOMULTIPLE_STUDENT_H
#define MULTIPLETOMULTIPLE_STUDENT_H

#include <iostream>
#include "Entry.h"

using namespace std;

struct Student {
    string name;
    Entry * entry;

    Student() {
        name = "";
    }

    Student(const string name_) {
        name = name_;
    }

    int operator==(const Student &s) const {
        return name == s.name;
    }

    friend ostream& operator<<(ostream& stream, Student s) {
        stream << s.name;
        return stream;
    }
};

namespace std {
    template<>
    class hash<Student> {
    public:
        size_t operator()(const Student &s) const {
            size_t key = 0;
            for (const char &c : s.name) {
                key += c;
            }
            return key;
        }
    };
}

#endif //MULTIPLETOMULTIPLE_STUDENT_H
