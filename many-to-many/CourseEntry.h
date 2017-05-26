//
// Created by Liudmila Kornilova on 16.05.17.
//

#ifndef MULTIPLETOMULTIPLE_COURSE_H
#define MULTIPLETOMULTIPLE_COURSE_H

#include <iostream>
#include "BaseEntry.h"

using namespace std;

class CourseEntry : BaseEntry {
public:
    CourseEntry() {
        id = -1;
    }

    CourseEntry(int id_) {
        id = id_;
    }

    int operator==(const CourseEntry &c) const {
        return id == c.id;
    }

    friend ostream &operator<<(ostream &stream, CourseEntry s) {
        stream << s.id;
        return stream;
    }

    int getId() const {
        return id;
    }

    ConnectionEntry *entry = 0;

private:
    int id;
};

// hash code is for adding course to hash-table
namespace std {
    template<>
    class hash<CourseEntry> {
    public:
        size_t operator()(const CourseEntry &c) const {
            size_t key = 0;
            int tempId = c.getId();
            while (tempId > 0) {
                key += tempId % 10;
                tempId /= 10;
            }
            return key;
        }
    };
}

#endif //MULTIPLETOMULTIPLE_COURSE_H
