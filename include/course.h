#pragma once
#ifndef COURSE_H
#define COURSE_H

#include "professor.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Definition of Course Class
class Course {
private:
    string name;
    int ects;
    bool courseType;
    int semester;
    vector<Professor> staff;

public:
    // Constructor
    Course();
    // Constructor with parameters
    Course(string name, int semester, int ects, bool courseType);
    // Destructor
    ~Course();
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Course &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Course &obj);

    /* Other Functions */

    inline string getName() const {
        return name;
    }

    inline int getEcts() const {
        return ects;
    }

    inline int getSemester() const {
        return semester;
    }

    inline string getCourseType() const {
        if (courseType) {
            return "Mandatory";
        }
        return "Optional";
    }

    void display(vector<Professor> &v);

    // Allowing Secretary class to access the private members of Course Class (friend class)
    friend class Secretary;
};

#endif