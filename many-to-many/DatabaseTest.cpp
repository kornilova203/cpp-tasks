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
// listCourses(s)
// printStudents(c)

#include <iostream>
#include "Database.h"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

SCENARIO("Using db") {
    GIVEN("Database with students and courses") {
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
        db.add(1, "Roman");
        REQUIRE(db.listCourses("Roman") == "1\n");
        REQUIRE(db.listStudents(1) == "Roman\n");

        WHEN("add student to not existing course") {
            int wasExeptThrown = 0;
            try {
                db.add(2, "Roman");
            }
            catch (runtime_error &ignored) {
                wasExeptThrown = 1;
            }
            THEN("exception is thrown and nothing changes") {
                REQUIRE(wasExeptThrown == 1);
                REQUIRE(db.listCourses("Roman") == "1\n");
            }
        }

        WHEN("add not existing student to course") {
            int wasExeptThrown = 0;
            try {
                db.add(1, "I do not exist");
            }
            catch (runtime_error &ignored) {
                wasExeptThrown = 1;
            }
            THEN("exception is thrown and nothing changes") {
                REQUIRE(wasExeptThrown == 1);
                REQUIRE(db.listStudents(1) == "Roman\n");
            }
        }

        WHEN("add second student to course") {
            db.add(1, "Petr");
            THEN("updated list of students in course") {
                REQUIRE(db.listStudents(1) == "Roman\nPetr\n");
                REQUIRE(db.listCourses("Petr") == "1\n");
            }
        }

        WHEN("Add student to course 2 times") {
            db.add(1, "Petr");
            db.add(1, "Petr");
            THEN("Student added only ones") {
                REQUIRE(db.listStudents(1) == "Roman\nPetr\n");
                REQUIRE(db.listCourses("Petr") == "1\n");
            }
        }

    }
    GIVEN("Database with several entries") {
        Database db((char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/students.txt",
                    (char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/courses.txt");
        db.add(1, "Roman");
        db.add(11, "Roman");
        db.add(1, "Petr");
        db.add(11, "Petr");
        db.add(12, "Roman");
        db.add(12, "Ekaterina");
        db.add(1, "Ekaterina");
        REQUIRE(db.listStudents(1) == "Roman\nPetr\nEkaterina\n");
        REQUIRE(db.listStudents(11) == "Roman\nPetr\n");
        REQUIRE(db.listStudents(12) == "Roman\nEkaterina\n");

        REQUIRE(db.listCourses("Roman") == "1\n11\n12\n");
        REQUIRE(db.listCourses("Petr") == "1\n11\n");
        REQUIRE(db.listCourses("Ekaterina") == "12\n1\n");

        WHEN("Remove student from his first course") {
            db.del(1, "Roman");
            THEN("Entry is removed from student and from course") {
                REQUIRE(db.listCourses("Roman") == "11\n12\n");
                REQUIRE(db.listStudents(1) == "Petr\nEkaterina\n");
            }
        }

        WHEN("Remove student from his second course") {
            db.del(11, "Roman");
            THEN("Entry is removed from student and from course") {
                REQUIRE(
                        db.listCourses("Roman") == "1\n12\n"
                );
                REQUIRE(db.listStudents(11) == "Petr\n");
            }
        }

        WHEN("Remove student from his third course") {
            db.del(12, "Roman");
            THEN("Entry is removed from student and from course") {
                REQUIRE(db.listCourses("Roman") == "1\n11\n");
                REQUIRE(db.listStudents(12) == "Ekaterina\n");
            }
        }
    }
}