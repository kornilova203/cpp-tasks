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
        string line;
        while (getline(input, line)) {  // read all lines
            Student s(line);
            students.insert(s);
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
            Course c(courseId);
            courses.insert(c);
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
