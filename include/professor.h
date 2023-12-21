#pragma once
#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "course.h"
#include "person.h"
#include <iostream>
#include <string>
using namespace std;

// Definition of Professor Class
class Professor : public Person {
private:
    string trait;
    string rank;
    string officeNo;
    vector<Course *> courses;

    // Helper functions
    Person *create() const;
    void print(ostream &str) const;

public:
    // Constructor
    Professor();
    // Constructor with parameters
    Professor(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id, string trait, string rank, string officeNo);
    // Copy Constructor
    Professor(const Professor &old_obj);
    // Destructor
    ~Professor();
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Professor &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Professor &obj);
    // Display Professor
    void display() const;

    /* Other Functions */

    inline string getTrait() const {
        return trait;
    }

    inline string getRank() const {
        return rank;
    }

    inline string getOfficeNo() const {
        return officeNo;
    }

    // Allowing Secretary class to access the private members of Professor Class (friend class)
    friend class Secretary;
};

#endif