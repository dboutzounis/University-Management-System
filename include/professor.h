#pragma once

#include "person.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Course;

// Definition of Professor Class
class Professor : public Person {
private:
    string trait;
    string rank;
    string officeNo;
    vector<Course *> courses;

    // Helper functions
    void print(ostream &str) const;

public:
    // Constructor
    Professor();
    // Constructor with parameters
    Professor(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string trait, string rank, string officeNo);
    Professor(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string id, string trait, string rank, string officeNo);
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
    // Create Professor
    Person *create() const;
    // Display Course
    void displayCourse(const string &courseName) const;
    // Search Course
    bool searchCourse(const string &courseName) const;
    // Insert Course
    bool insertCourse(Course *course);
    // Remove Course
    bool removeCourse(const string &courseName);
    // Display course statistics
    void displayStatistics() const;

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

    inline vector<Course *> getCourses() const {
        return courses;
    }

    inline void setTrait(const string &trait) {
        this->trait = trait;
    }

    inline void setRank(const string &rank) {
        this->rank = rank;
    }

    inline void setOfficeNo(const string &officeNo) {
        this->officeNo = officeNo;
    }
};
