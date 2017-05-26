#include <iostream>
#include "Database.h"

#include "catch.hpp"

SCENARIO("Using db") {
    GIVEN("Database with students and courses") {
        Database db((char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/test-data/students.txt",
                    (char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/test-data/courses.txt");
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
        Database db((char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/test-data/students.txt",
                    (char *) "/home/lk/Dropbox/ITMO/programming/cpp-tasks/many-to-many/test-data/courses.txt");
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
            db.remove(1, "Roman");
            THEN("BaseEntry is removed from student and from course") {
                REQUIRE(db.listCourses("Roman") == "11\n12\n");
                REQUIRE(db.listStudents(1) == "Petr\nEkaterina\n");
            }
        }

        WHEN("Remove student from his second course") {
            db.remove(11, "Roman");
            THEN("BaseEntry is removed from student and from course") {
                REQUIRE(
                        db.listCourses("Roman") == "1\n12\n"
                );
                REQUIRE(db.listStudents(11) == "Petr\n");
            }
        }

        WHEN("Remove student from his third course") {
            db.remove(12, "Roman");
            THEN("BaseEntry is removed from student and from course") {
                REQUIRE(db.listCourses("Roman") == "1\n11\n");
                REQUIRE(db.listStudents(12) == "Ekaterina\n");
            }
        }

        WHEN("Remove all courses from student") {
            db.remove(12, "Roman");
            db.remove(11, "Roman");
            db.remove(1, "Roman");
            THEN("Student is removed from all courses") {
                REQUIRE(db.listCourses("Roman") == "Student does not take any courses");
                REQUIRE(db.listStudents(1) == "Petr\nEkaterina\n");
                REQUIRE(db.listStudents(11) == "Petr\n");
                REQUIRE(db.listStudents(12) == "Ekaterina\n");
            }
        }

        WHEN("Remove student from list") {
            db.remove("Roman");
            THEN("Student is removed from all courses") {
                REQUIRE(db.listCourses("Roman") == "Student does not take any courses");
                REQUIRE(db.listStudents(1) == "Petr\nEkaterina\n");
                REQUIRE(db.listStudents(11) == "Petr\n");
                REQUIRE(db.listStudents(12) == "Ekaterina\n");
            }
        }

        WHEN("Remove course from list") {
            db.remove(11);
            THEN("Course is removed from all students") {
                REQUIRE(db.listStudents(11) == "Course does not have any students");
                REQUIRE(db.listCourses("Roman") == "1\n12\n");
                REQUIRE(db.listCourses("Petr") == "1\n");
                REQUIRE(db.listCourses("Ekaterina") == "12\n1\n");
            }
        }
    }
}