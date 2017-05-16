// Multiple to multiple

// students <-> courses

// 1. get list of students going to particular course
// 2. get courses of particular student

// actions:
// student chooses course
// course stops
// student leaves course

// sets of students and courses do not change

// matrix:
// OX -students
// OY - courses

// cnext - course
// snext - student

// void *

// student: string + pointer to hashCode() = sum of characters
// course: int code hashCode = sum of numbers

// add(c, s)
// delete(c, s)
// delete(s)
// delete(c)
// printCourses(s)
// printStudents(c)

#include <iostream>
#include "Database.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    Database db((char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/students.txt",
                (char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/courses.txt");
    REQUIRE(db.studentsToString() == "Students:\n"
                                             "Roman\n"
                                             "Petr\n"
                                             "Ekaterina\n"
                                             "Nicolay\n"
                                             "Margarita\n"
                                             "Evgeniy\n"
                                             "Svetlana\n"
                                             "Vasiliy\n");
    REQUIRE(db.coursesToString() == "Courses:\n"
                                            "1\n"
                                            "11\n"
                                            "12\n"
                                            "14\n"
                                            "32\n"
                                            "16\n"
                                            "314\n"
                                            "234\n"
                                            "324\n"
                                            "294\n"
                                            "278\n");
}