//
// Created by Liudmila Kornilova on 12.05.17.
//

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Database.h"

/**
 * Constructor.
 * Creates database with students and courses from file
 * @param studFileName file with student names
 * @param coursesFileName file with courses ids
 */
Database::Database(char *studFileName, char *coursesFileName) {
    readStud_(studFileName);
    readCourses_(coursesFileName);
}

/**
 * Load data from file
 * @param studFileName file with student names
 */
void Database::readStud_(char *studFileName) {
    std::fstream input(studFileName);
    if (input) {  // if file was open
        string name;
        while (getline(input, name)) {  // read all lines
            students.insert(StudentEntry(name));
        }
    } else {
        throw runtime_error("Could not open file with students names");
    }
}

/**
 * Load data from file
 * @param coursesFileName file with courses ids
 */
void Database::readCourses_(char *coursesFileName) {
    std::fstream input(coursesFileName);

    if (input) {
        int courseId;
        while (input >> courseId) {
            courses.insert(CourseEntry(courseId));
        }
    } else {
        throw runtime_error("Could not open file with courses");
    }
}

/**
 * Get string with all students
 * @return string with all students
 */
string Database::studentsToString() const {
    ostringstream ss;
    ss << "Students:\n";
    ss << students;
    return ss.str();
}

string Database::coursesToString() const {
    ostringstream ss;
    ss << "Courses:\n";
    ss << courses;
    return ss.str();
}

/**
 * Add connection between course and student
 * create new entry, which points to this student and course
 * find last entry in student and point it to new entry
 * find last entry in course and point it to new entry
 * @param courseId
 * @param studentName
 */
void Database::add(int courseId, string studentName) {
    StudentEntry *student = getStudent_(studentName);
    CourseEntry *course = getCourse_(courseId);
    if (findEntryBeforeCommon_(course, student) != 0) { // if course and student are connected
        return;
    }
    ConnectionEntry *entry = new ConnectionEntry((BaseEntry *) student, (BaseEntry *) course);
    if (student->entry == 0) { // if student does not have any courses
        student->entry = entry;
    } else {
        ConnectionEntry *lastEntry = getLastStudentEntry_(student);
        lastEntry->left = (BaseEntry *) entry;
    }
    if (course->entry == 0) { // if course does not have any students
        course->entry = entry;
    } else {
        ConnectionEntry *lastEntry = getLastCourseEntry_(course);
        lastEntry->right = (BaseEntry *) entry;
    }
}

/**
 * Find common entry
 * @param course
 * @param student
 * @return entry which is before common entry in list of Student
 *      0 - if there is no common entry
 */
BaseEntry * Database::findEntryBeforeCommon_(const CourseEntry *course, const StudentEntry *student) const {
    if (student->entry == 0) { // if student does not have any courses
        return 0;
    }

    BaseEntry *next = (BaseEntry *) student->entry;
    BaseEntry *prev = (BaseEntry *) student;

    while (next->isConnectionEntry()) { // while it is not a StudentEntry again
        // here `entry` is a ConnectionEntry
        if (getCourse_((ConnectionEntry *) next) == course) {
            return prev;
        }
        prev = next;
        next = ((ConnectionEntry *) next)->left; // next student's entry
    }
    return 0;
}

StudentEntry *Database::getStudent_(const string studentName) const {
    try {
        return students.get(StudentEntry(studentName));
    }
    catch (const runtime_error &e) {
        throw runtime_error("Student " + studentName + " was not found\n");
    }
}

CourseEntry *Database::getCourse_(int courseId) const {
    try {
        return courses.get(CourseEntry(courseId));
    }
    catch (const runtime_error &e) {
        throw runtime_error("Course " + to_string(courseId) + " was not found\n");
    }
}

/**
 * Get last entry for student
 * student must have at least one entry
 * @param student
 * @return
 */
ConnectionEntry *Database::getLastStudentEntry_(const StudentEntry *student) const {
    BaseEntry *prev = 0;
    BaseEntry *next = (BaseEntry *) student->entry;
    while (next->isConnectionEntry()) { // while next is not a StudentEntry
        prev = next;
        next = ((ConnectionEntry *) next)->left;
    }
    if (next == (BaseEntry *) student) {
        return (ConnectionEntry *) prev;
    }
    throw runtime_error("incorrect cycle for student");
}

/**
 * Get last entry for course
 * student must have at least one entry
 * @param student
 * @return
 */
ConnectionEntry *Database::getLastCourseEntry_(const CourseEntry *course) const {
    BaseEntry *prev = 0;
    BaseEntry *next = (BaseEntry *) course->entry;
    while (next->isConnectionEntry()) { // while next is not a CourseEntry
        prev = next;
        next = ((ConnectionEntry *) next)->right;
    }
    if (next == (BaseEntry *) course) {
        return (ConnectionEntry *) prev;
    }
    throw runtime_error("incorrect cycle for course");
}

/**
 * Print all courses of student
 * @param studentName
 * @return string containing list of all courses of "Student was not found"
 */
string Database::listCourses(string studentName) const {
    StudentEntry *student;
    try {
        student = getStudent_(studentName);
    }
    catch (const runtime_error &e) {
        return "Student was not found";
    }
    BaseEntry *entry = (BaseEntry *) student->entry;
    if (!entry) {
        return "Student does not take any courses";
    }
    string result = "";
    while (entry->isConnectionEntry()) {
        result += to_string(getCourse_((ConnectionEntry *) entry)->getId()) + "\n";
        entry = ((ConnectionEntry *) entry)->left;
    }
    return result;
}

CourseEntry *Database::getCourse_(const ConnectionEntry *entry) const {
    BaseEntry *temp = entry->right;
    while (temp->isConnectionEntry()) { // while entry is not a Course
        temp = ((ConnectionEntry *) temp)->right;
    }
    return (CourseEntry *) temp;
}

/**
 * Get string with list of students on particular course
 * @param courseId course id (int)
 * @return string containing all student names
 */
string Database::listStudents(int courseId) const {
    CourseEntry *course;
    try {
        course = getCourse_(courseId);
    }
    catch (const runtime_error &e) {
        return "Course was not found";
    }
    return listStudents_(course);
}

/**
 * Get string with list of students on particular course
 * @param course pointer to course in hash-table
 * @return string containing all student names
 */
string Database::listStudents_(const CourseEntry *course) const {
    string result = "";
    BaseEntry *entry = (BaseEntry *) course->entry;
    if (!entry) {
        return "Course does not have any students";
    }
    while (entry->isConnectionEntry()) { // while it is not a CourseEntry
        result += getStudent_((ConnectionEntry *) entry)->getName() + "\n";
        entry = ((ConnectionEntry *) entry)->right;
    }
    return result;
}

/**
 * get student for loop with particular entry
 * @param entry in loop
 * @return pointer to student
 */
StudentEntry *Database::getStudent_(const ConnectionEntry *entry) const {
    BaseEntry *next = entry->left;
    while (next->isConnectionEntry()) { // while it is not a StudentEntry
        next = ((ConnectionEntry *) next)->left;
    }
    return (StudentEntry *) next;
}

/**
 * Delete student from course
 * find common entry
 * find preceding entries for student and course
 * exclude entry from both cycles
 * delete entry
 * @param course
 * @param student
 */
void Database::remove(int courseId, const char *studentName) {
    CourseEntry *course = getCourse_(courseId);
    StudentEntry *student = getStudent_(studentName);
    BaseEntry *beforeCommonEntry = findEntryBeforeCommon_(course, student);
    if (beforeCommonEntry == 0) {
        return;
    }
    ConnectionEntry *commonEntry;
    if (beforeCommonEntry->isConnectionEntry()) {
        commonEntry = (ConnectionEntry *) ((ConnectionEntry *) beforeCommonEntry)->left;
    } else {
        commonEntry = ((StudentEntry *) beforeCommonEntry)->entry;
    }
    excludeEntry_(beforeCommonEntry, student);

    excludeEntry_(commonEntry, course);
    delete commonEntry;
}

/**
 * Find preceding entry for student cycle
 * @param nextEntry
 * @param student
 */
BaseEntry *Database::findPrevEntry_(const ConnectionEntry *nextEntry, const StudentEntry *student) const {
    BaseEntry *entry = (BaseEntry *) student->entry;
    if (student->entry == nextEntry) {
        return (BaseEntry *) student;
    }
    while (entry->isConnectionEntry()) { // while it is not a StudentEntry
        BaseEntry *left = ((ConnectionEntry *) entry)->left;
        if (left->isConnectionEntry()) {
            if ((ConnectionEntry *) left == nextEntry) {
                return entry;
            }
        }
        entry = ((ConnectionEntry *) entry)->left;
    }
    return 0;
}

/**
 * Find preceding entry for course cycle
 * @param nextEntry
 * @param student
 */
ConnectionEntry *Database::findPrevEntry_(const ConnectionEntry *nextEntry, const CourseEntry *course) const {
    BaseEntry *entry = (BaseEntry *) course->entry;
    while (entry->isConnectionEntry()) { // while it is not a CourseEntry
        BaseEntry *right = ((ConnectionEntry *) entry)->right;
        if (right->isConnectionEntry()) {
            if ((ConnectionEntry *) right == nextEntry) {
                return (ConnectionEntry *) entry;
            }
        }
        entry = ((ConnectionEntry *) entry)->right;
    }
    return 0;
}

void Database::excludeEntry_(const BaseEntry *beforeCommonEntry, StudentEntry *student) {
    if (beforeCommonEntry == (BaseEntry *) student) { // if it is first entry for student
        ConnectionEntry * commonEntry = ((StudentEntry *) beforeCommonEntry)->entry;
        if (!commonEntry->left->isConnectionEntry()) { // if it is the only beforeCommonEntry for student (return back to student
            student->entry = 0;
        } else {
            student->entry = (ConnectionEntry *) commonEntry->left;
        }
    } else {
        ConnectionEntry *commonEntry = (ConnectionEntry *) ((ConnectionEntry *) beforeCommonEntry)->left;
//        ConnectionEntry *prevEntry = findPrevEntry_(beforeCommonEntry, student);
        ((ConnectionEntry *) beforeCommonEntry)->left = commonEntry->left;
    }
}

void Database::excludeEntry_(const ConnectionEntry *entry, CourseEntry *course) {
    if (course->entry == entry) { // if it is first entry for course
        if (!entry->right->isConnectionEntry()) { // if it is the only entry for course
            course->entry = 0;
        } else {
            course->entry = (ConnectionEntry *) entry->right;
        }
    } else {
        ConnectionEntry *prevEntry = findPrevEntry_(entry, course);
        prevEntry->right = entry->left;
    }
}

/**
 * Remove student from all courses
 * @param student
 */
void Database::remove(const char *studentName) {
    StudentEntry *student = getStudent_(studentName);
    BaseEntry *entry = (BaseEntry *) student->entry;
    while (entry->isConnectionEntry()) { // for all entries of this student
        CourseEntry *course = getCourse_((ConnectionEntry *) entry);
        excludeEntry_((ConnectionEntry *) entry, course);
        BaseEntry *delEntry = entry;
        entry = ((ConnectionEntry *) entry)->left;
        delete delEntry;
    }
    student->entry = 0;
}

/**
 * Remove course from all students
 * @param courseId
 */
void Database::remove(int courseId) {
    CourseEntry *course = getCourse_(courseId);
    if (!course->entry) { // if there is no students in this course
        return;
    }
    BaseEntry *entry = (BaseEntry *) course->entry;
    while (entry->isConnectionEntry()) { // for all entries of this course
        StudentEntry *student = getStudent_((ConnectionEntry *) entry);
        BaseEntry *prevCommonEntry = findPrevEntry_((ConnectionEntry *) entry, student);
        excludeEntry_(prevCommonEntry, student);
        BaseEntry *delEntry = entry;
        entry = ((ConnectionEntry *) entry)->right;
        delete delEntry;
    }
    course->entry = 0;
}
