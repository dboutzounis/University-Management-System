#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <iostream>
#include <string>
using namespace std;

// Definition of Student class
class Student : public Person {
private:
    int semester;
    int ects;
    double gpa;
    int memberSince;

public:
    // Constructor
    Student();
    // Constructor with parameters
    Student(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id, int semester, int ects, int memberSince);
    // Destructor
    ~Student();
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Student &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Student &obj);

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