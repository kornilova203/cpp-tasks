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
            students.insert(Student(name));
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
            courses.insert(Course(courseId));
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
    Student *student = getStudent_(studentName);
    Course *course = getCourse_(courseId);
    if (findCommonEntry_(course, student) != 0) { // if course and student are connected
        return;
    }
    Entry *entry = new Entry(course, student);
    if (student->entry == 0) { // if student does not have any courses
        student->entry = entry;
    } else {
        Entry *lastEntry = getLastStudentEntry_(student);
        lastEntry->setNextStudentEntry(entry);
    }
    if (course->entry == 0) { // if course does not have any students
        course->entry = entry;
    } else {
        Entry *lastEntry = getLastCourseEntry_(course);
        lastEntry->setNextCourseEntry(entry);
    }
}

/**
 * Check if student and course have connection
 * @param course
 * @param student
 * @return 1 - if have connection; 0 - otherwise
 */
Entry * Database::findCommonEntry_(const Course *course, const Student *student) const {
    Entry *entry = student->entry;
    if (entry == 0) { // if student does not have any courses
        return 0;
    }
    while (entry != 0) {
        if (getCourse_(entry) == course) {
            return entry;
        }
        entry = entry->getNextStudentEntry();
    }
    return 0;
}

Student *Database::getStudent_(const string studentName) const {
    try {
        return students.get(Student(studentName));
    }
    catch (const runtime_error &e) {
        throw runtime_error("Student " + studentName + " was not found\n");
    }
}

Course *Database::getCourse_(int courseId) const {
    try {
        return courses.get(Course(courseId));
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
Entry *Database::getLastStudentEntry_(const Student *student) const {
    Entry *lastEntry = student->entry;
    while (lastEntry->getNextStudentEntry() != 0) {
        lastEntry = lastEntry->getNextStudentEntry();
    }
    if (lastEntry->getNextStudent() == student) {
        return lastEntry;
    }
    throw runtime_error("incorrect cycle for student");
}

/**
 * Get last entry for course
 * student must have at least one entry
 * @param student
 * @return
 */
Entry *Database::getLastCourseEntry_(const Course *course) const {
    Entry *lastEntry = course->entry;
    while (lastEntry->getNextCourseEntry() != 0) {
        lastEntry = lastEntry->getNextCourseEntry();
    }
    if (lastEntry->getNextCourse() == course) {
        return lastEntry;
    }
    throw runtime_error("incorrect cycle for course");
}

/**
 * Print all courses of student
 * @param studentName
 * @return string containing list of all courses of "Student was not found"
 */
string Database::listCourses(string studentName) const {
    Student *student;
    try {
        student = getStudent_(studentName);
    }
    catch (const runtime_error &e) {
        return "Student was not found";
    }
    Entry *entry = student->entry;
    string result = "";
    while (entry != 0) {
        result += to_string(getCourse_(entry)->getId()) + "\n";
        entry = entry->getNextStudentEntry();
    }
    if (result == "") {
        return "Student does not take any courses";
    }
    return result;
}

Course *Database::getCourse_(const Entry *entry) const {
    while (entry->getNextCourseEntry() != 0) {
        entry = entry->getNextCourseEntry();
    }
    return entry->getNextCourse();
}

/**
 * Get string with list of students on particular course
 * @param courseId course id (int)
 * @return string containing all student names
 */
string Database::listStudents(int courseId) const {
    Course *course;
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
string Database::listStudents_(const Course *course) const {
    string result = "";
    Entry *entry = course->entry;
    while (entry != 0) {
        result += getStudent_(entry)->getName() + "\n";
        entry = entry->getNextCourseEntry();
    }
    if (result == "") {
        return "Course does not have any students";
    }
    return result;
}

/**
 * get student for loop with particular entry
 * @param entry in loop
 * @return pointer to student
 */
Student *Database::getStudent_(const Entry *entry) const {
    Entry *next = entry->getNextStudentEntry();
    while (next != 0) { // find last entry for student loop
        entry = next;
        next = next->getNextStudentEntry();
    }
    return entry->getNextStudent();
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
    Course *course = getCourse_(courseId);
    Student *student = getStudent_(studentName);
    Entry *entry = findCommonEntry_(course, student);
    excludeEntry_(entry, student);
    excludeEntry_(entry, course);
    delete entry;
}

/**
 * Find preceding entry for student cycle
 * @param nextEntry
 * @param student
 */
Entry * Database::findPrevEntry_(const Entry *nextEntry, const Student *student) const {
    Entry *entry = student->entry;
    while (entry != 0) {
        if (entry->getNextStudentEntry() == nextEntry) {
            return entry;
        }
        entry = entry->getNextStudentEntry();
    }
    return 0;
}

/**
 * Find preceding entry for course cycle
 * @param nextEntry
 * @param student
 */
Entry * Database::findPrevEntry_(const Entry *nextEntry, const Course *course) const {
    Entry *entry = course->entry;
    while (entry != 0) {
        if (entry->getNextCourseEntry() == nextEntry) {
            return entry;
        }
        entry = entry->getNextCourseEntry();
    }
    return 0;
}

void Database::excludeEntry_(const Entry *entry, Student *student) {
    if (student->entry == entry) { // if it is first entry for student
        if (entry->getNextStudentEntry() == 0) { // if it is the only entry for student
            student->entry = 0;
        } else {
            student->entry = entry->getNextStudentEntry();
        }
    } else {
        Entry *prevEntry = findPrevEntry_(entry, student);
        if (prevEntry->getNextStudentEntry() != 0) {
            prevEntry->setNextStudentEntry(entry->getNextStudentEntry());
        } else {
            prevEntry->setNextStudent(entry->getNextStudent());
        }
    }
}

void Database::excludeEntry_(const Entry *entry, Course *course) {
    if (course->entry == entry) { // if it is first entry for course
        if (entry->getNextCourseEntry() == 0) { // if it is the only entry for course
            course->entry = 0;
        } else {
            course->entry = entry->getNextCourseEntry();
        }
    } else {
        Entry *prevEntry = findPrevEntry_(entry, course);
        if (prevEntry->getNextCourseEntry() != 0) {
            prevEntry->setNextCourseEntry(entry->getNextCourseEntry());
        } else {
            prevEntry->setNextCourse(entry->getNextCourse());
        }
    }
}

/**
 * Remove student from all courses
 * @param student
 */
void Database::remove(const char *studentName) {
    Student *student = getStudent_(studentName);
    Entry *entry = student->entry;
    while (entry != 0) { // for all entries of this student
        Course *course = getCourse_(entry);
        excludeEntry_(entry, course);
        Entry *delEntry = entry;
        entry = entry->getNextStudentEntry();
        delete delEntry;
    }
    student->entry = 0;
}

/**
 * Remove course from all students
 * @param courseId
 */
void Database::remove(int courseId) {
    Course *course = getCourse_(courseId);
    Entry *entry = course->entry;
    while (entry != 0) { // for all entries of this course
        Student *student = getStudent_(entry);
        excludeEntry_(entry, student);
        Entry *delEntry = entry;
        entry = entry->getNextCourseEntry();
        delete delEntry;
    }
    course->entry = 0;
}
