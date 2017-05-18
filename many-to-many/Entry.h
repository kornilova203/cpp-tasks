//
// Created by Liudmila Kornilova on 16.05.17.
//

#ifndef MULTIPLETOMULTIPLE_ENTRY_H
#define MULTIPLETOMULTIPLE_ENTRY_H

//#include "Course.h"
//#include "Student.h"

class Course;

class Student;

class Entry {
public:
    Entry(Course *course, Student *student) {
        nextCourse = course;
        nextStudent = student;
    }

    Student *getNextStudent() const {
        return nextStudent;
    }

    Entry *getNextStudentEntry() const {
        return nextStudentEntry;
    }

    Course *getNextCourse() const {
        return nextCourse;
    }

    Entry *getNextCourseEntry() const {
        return nextCourseEntry;
    }

    void setNextStudent(Student *nextStudent) {
        nextStudentEntry = 0;
        Entry::nextStudent = nextStudent;
    }

    void setNextCourse(Course *nextCourse) {
        nextCourseEntry = 0;
        Entry::nextCourse = nextCourse;
    }

    void setNextCourseEntry(Entry *nextCourseEntry) {
        nextCourse = 0;
        Entry::nextCourseEntry = nextCourseEntry;
    }

    void setNextStudentEntry(Entry *nextStudentEntry) {
        nextStudent = 0;
        Entry::nextStudentEntry = nextStudentEntry;
    }

private:
    Student *nextStudent = 0;
    Course *nextCourse = 0;

    Entry *nextCourseEntry = 0;
    Entry *nextStudentEntry = 0;
};

#endif //MULTIPLETOMULTIPLE_ENTRY_H
