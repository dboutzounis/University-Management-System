#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// Definition of Course Class
class Course {
private:
    string name;
    unsigned int ects;
    bool courseType;
    unsigned int semester;
    map<string, Professor *> staff;
    map<string, Student *> students;
    map<string, double> grades;

    // Helper functions
    void print(map<string, Professor *> &v);

public:
    // Constructor
    Course();
    // Constructor with parameters
    Course(string name, unsigned int semester, unsigned int ects, bool courseType);
    // Copy Constructor
    Course(const Course &old_obj);
    // Destructor
    ~Course();
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Course &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Course &obj);
    // Display Course
    void display() const;

    /* Other Functions */

    inline string getName() const {
        return name;
    }

    inline unsigned int getEcts() const {
        return ects;
    }

    inline unsigned int getSemester() const {
        return semester;
    }

    inline string getCourseType() const {
        if (courseType) {
            return "Mandatory";
        }
        return "Optional";
    }

    inline map<string, Professor *> getStaff() const {
        return this->staff;
    }

    inline map<string, Student *> getStudents() const {
        return this->students;
    }

    inline map<string, double> getGrades() const {
        return this->grades;
    }

    inline void setName(const string &name) {
        this->name = name;
    }

    inline void setEcts(unsigned int ects) {
        this->ects = ects;
    }

    inline void setSemester(unsigned int semester) {
        this->semester = semester;
    }

    inline void setCourseType(bool courseType) {
        this->courseType = courseType;
    }
};

#endif