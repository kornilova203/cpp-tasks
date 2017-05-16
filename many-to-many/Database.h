//
// Created by Liudmila Kornilova on 12.05.17.
//

#ifndef MULTIPLETOMULTIPLE_MULTIPLETOMULTIPLE_H
#define MULTIPLETOMULTIPLE_MULTIPLETOMULTIPLE_H


#include <ClosedHash.h>
#include "Student.h"
#include "Course.h"

class Database {
public:
    Database(char *studFileName, char *coursesFileName);

    string studentsToString() const;
    string coursesToString() const;

    void printCourses(char *student) const;

    void printStudents(int course) const;

    void add(int course, const char *student);

    void del(int course, const char *student);

    void del(const char *student);

    void del(int course);

private:
    ClosedHash<Course> courses = ClosedHash<Course>();
    ClosedHash<Student> students = ClosedHash<Student>();

    void readStud_(char *studFileName);

    void readCourses_(char *coursesFileName);
};


#endif //MULTIPLETOMULTIPLE_MULTIPLETOMULTIPLE_H
