//
// Created by Liudmila Kornilova on 16.05.17.
//

#ifndef MULTIPLETOMULTIPLE_COURSE_H
#define MULTIPLETOMULTIPLE_COURSE_H

#include <iostream>
#include "Entry.h"

using namespace std;

class Course {
public:
    Entry *entry = 0;

    Course() {
        id = -1;
    }

    Course(int id_) {
        id = id_;
    }

    int operator==(const Course &c) const {
        return id == c.id;
    }

    friend ostream &operator<<(ostream &stream, Course s) {
        stream << s.id;
        return stream;
    }

    int getId() const {
        return id;
    }

private:
    int id;

};

namespace std {
    template<>
    class hash<Course> {
    public:
        size_t operator()(const Course &c) const {
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
