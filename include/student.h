#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "course.h"
#include "person.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Definition of Student class
class Student : public Person {
private:
    unsigned int semester;
    unsigned int ects;
    double gpa;
    unsigned int memberSince;
    vector<Course> courses;

    // Helper functions
    void print(ostream &str) const;

public:
    // Constructor
    Student();
    // Constructor with parameters
    Student(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, unsigned int semester, unsigned int ects, double gpa, unsigned int memberSince);
    Student(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string id, unsigned int semester, unsigned int ects, double gpa, unsigned int memberSince);
    // Copy Constructor
    Student(const Student &old_obj);
    // Destructor
    ~Student();
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Student &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Student &obj);
    // Display Student
    void display() const;
    // Create Student
    Person *create() const;
    // Display Course
    void displayCourse(const string &courseName) const;
    // Search Course
    bool searchCourse(const string &courseName) const;
    // Insert Course
    bool insertCourse(const Course &course);
    // Remove Course
    bool removeCourse(const string &courseName);

    /* Other Functions */

    inline unsigned int getSemester() const {
        return semester;
    }

    inline unsigned int getEcts() const {
        return ects;
    }

    inline double getGpa() const {
        return gpa;
    }

    inline unsigned int getStartingYear() const {
        return memberSince;
    }

    inline void setSemester(unsigned int semester) {
        this->semester = semester;
    }

    inline void setEcts(unsigned int ects) {
        this->ects = ects;
    }

    inline void setGPA(double gpa) {
        this->gpa = gpa;
    }

    inline void setStartingYear(unsigned int memberSince) {
        this->memberSince = memberSince;
    }
};

#endif