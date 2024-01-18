#pragma once

#include "professor.h"
#include "student.h"
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
    bool courseType; // Coursetype==True means that the course is mandatory, else it's optional
    unsigned int semester;
    map<string, Professor *> staff;
    map<string, Student *> students;
    map<string, double> grades;

    // Helper functions
    void print(ostream &str);

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
    // Display Professor
    void displayProfessor(const string &id) const;
    // Search Professor
    bool searchProfessor(const string &id) const;
    // Insert Professor
    bool insertProfessor(Professor *professor);
    // Remove Professor
    bool removeProfessor(const string &id);
    // Display Student
    void displayStudent(const string &id) const;
    // Search Student
    bool searchStudent(const string &id) const;
    // Insert Student
    bool insertStudent(Student *student);
    // Remove Student
    bool removeStudent(const string &id);

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

    inline void setGrades(const map<string, double> &grades) {
        this->grades = grades;
    }
};
