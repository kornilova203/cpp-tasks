//
// Created by Liudmila Kornilova on 12.05.17.
//

#ifndef MULTIPLETOMULTIPLE_MULTIPLETOMULTIPLE_H
#define MULTIPLETOMULTIPLE_MULTIPLETOMULTIPLE_H


#include <ClosedHash.h>
#include "StudentEntry.h"
#include "CourseEntry.h"
//#include "ConnectionEntry.h"

/**
 * Many-to-many data-model
 */
class Database {
public:
    Database(char *studFileName, char *coursesFileName);

    string studentsToString() const;

    string coursesToString() const;

    string listCourses(string studentName) const;

    string listStudents(int courseId) const;

    void add(int courseId, string studentName);

    void remove(int courseId, const char *studentName);

    void remove(const char *studentName);

    void remove(int courseId);

private:
    ClosedHash<CourseEntry> courses = ClosedHash<CourseEntry>();
    ClosedHash<StudentEntry> students = ClosedHash<StudentEntry>();

    void readStud_(char *studFileName);

    void readCourses_(char *coursesFileName);

    StudentEntry *getStudent_(const string studentName) const;

    CourseEntry *getCourse_(int courseId) const;

    CourseEntry *getCourse_(const ConnectionEntry *entry) const;

    StudentEntry *getStudent_(const ConnectionEntry *entry) const;

    ConnectionEntry *getLastStudentEntry_(const StudentEntry *student) const;

    ConnectionEntry *getLastCourseEntry_(const CourseEntry *course) const;

    string listStudents_(const CourseEntry *course) const;

    ConnectionEntry *findCommonEntry_(const CourseEntry *pCourse, const StudentEntry *pStudent) const;

    ConnectionEntry *findPrevEntry_(const ConnectionEntry *nextEntry, const StudentEntry *pStudent) const;

    ConnectionEntry *findPrevEntry_(const ConnectionEntry *nextEntry, const CourseEntry *course) const;

    void excludeEntry_(const ConnectionEntry *pEntry, StudentEntry *pStudent);

    void excludeEntry_(const ConnectionEntry *entry, CourseEntry *course);
};


#endif //MULTIPLETOMULTIPLE_MULTIPLETOMULTIPLE_H
