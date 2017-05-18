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

    string listCourses(string studentName) const;

    string listStudents(int courseId) const;

    void add(int courseId, string studentName);

    void del(int course, const char *student);

    void del(const char *student);

    void del(int course);

private:
    ClosedHash<Course> courses = ClosedHash<Course>();
    ClosedHash<Student> students = ClosedHash<Student>();

    void readStud_(char *studFileName);

    void readCourses_(char *coursesFileName);

    Student *getStudent_(const string studentName) const;

    Course *getCourse_(int courseId) const;

    Course *getCourse_(const Entry *entry) const;

    Student *getStudent_(const Entry *entry) const;

    Entry *getLastStudentEntry_(const Student *student) const;

    Entry *getLastCourseEntry_(const Course *course) const;

    string listStudents_(const Course *course) const;

    Entry *findCommonEntry_(const Course *pCourse, const Student *pStudent) const;

    Entry *findPrevEntry_(const Entry *nextEntry, const Student *pStudent) const;

    Entry *findPrevEntry_(const Entry *nextEntry, const Course *course) const;

    void excludeEntry_(const Entry *pEntry, Student *pStudent);

    void excludeEntry_(const Entry *entry, Course *course);
};


#endif //MULTIPLETOMULTIPLE_MULTIPLETOMULTIPLE_H
