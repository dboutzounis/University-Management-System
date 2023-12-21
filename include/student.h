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
    int semester;
    int ects;
    double gpa;
    int memberSince;
    vector<Course *> courses;

    // Helper functions
    Person *create() const;
    void print(ostream &str) const;

public:
    // Constructor
    Student();
    // Constructor with parameters
    Student(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id, int semester, int ects, double gpa, int memberSince);
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

    /* Other Functions */

    inline int getSemester() const {
        return semester;
    }

    inline int getEcts() const {
        return ects;
    }

    inline double getGpa() const {
        return gpa;
    }

    inline int getStartingYear() const {
        return memberSince;
    }

    // Allowing Secretary class to access the private members of Student Class (friend class)
    friend class Secretary;
};

#endif