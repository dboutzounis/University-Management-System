#pragma once
#ifndef SECRETARY_H
#define SECRETARY_H

#include "course.h"
#include "professor.h"
#include "student.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// Definition of Secretary Class
class Secretary {
private:
    // Using the map from STL to store pairs of <string, Person *> (string = key, Person * points to instances of the Person object)
    map<string, Person *> unidata;
    string department;
    int yearsOfStudy;
    map<int, vector<Course *>> curriculum;

    Person *allocatePerson(const Person &person);

public:
    // Constructor
    Secretary();
    // Constructor with the department name as parameter
    Secretary(string department, int yearsOfStudy);
    // Destructor
    ~Secretary();
    // Copy Constructor
    Secretary(const Secretary &old_obj);
    // Operator= overloading
    Secretary operator=(const Secretary &old_obj);
    // Operator+= overloading
    Secretary operator+=(const Person &person);
    // Operator-= overloading
    Secretary operator-=(const Person &person);
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Secretary &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Secretary &obj);
    // Display Person from the map
    void displayPerson(string id);
    // Search Person in the map
    bool search(string id);
    // Insert Person in the map
    bool insert(const Person &person);
    // Remove Person from the map
    bool remove(string id);
    // Unidata map size
    int count();
    // Student registration to course
    void registerStudentToCourse(const Course &c, string id);
    // Course assignment to professor
    void assignCourseToProfessor(const Course &c, string id);

    /* Other Functions */

    inline string getDepartment() const {
        return department;
    }

    inline int getYearsOfStudy() const {
        return yearsOfStudy;
    }

    inline string getFname(string id) const {
        return unidata.at(id)->fname;
    }

    inline string getLname(string id) const {
        return unidata.at(id)->lname;
    }

    inline string getBirthDate(string id) const {
        return to_string(unidata.at(id)->day) + "/" + to_string(unidata.at(id)->month) + "/" + to_string(unidata.at(id)->year);
    }

    inline string getGender(string id) const {
        if (unidata.at(id)->gender == 'M' || unidata.at(id)->gender == 'm')
            return "Male";
        else if (unidata.at(id)->gender == 'F' || unidata.at(id)->gender == 'f')
            return "Female";

        return "Other";
    }

    inline string getNationality(string id) const {
        return unidata.at(id)->nationality;
    }

    inline string getEmail(string id) const {
        return unidata.at(id)->email;
    }

    inline string getPhone(string id) const {
        return unidata.at(id)->phone;
    }

    inline void setFname(string id, string fname) {
        unidata[id]->fname = fname;
    }

    inline void setLname(string id, string lname) {
        unidata[id]->lname = lname;
    }

    inline void setBirthDate(string id, int day, int month, int year) {
        unidata[id]->day = day;
        unidata[id]->month = month;
        unidata[id]->year = year;
    }

    inline void setGender(string id, char gender) {
        unidata[id]->gender = gender;
    }

    inline void setNationality(string id, string nationality) {
        unidata[id]->nationality = nationality;
    }

    inline void setEmail(string id, string email) {
        unidata[id]->email = email;
    }

    inline void setPhone(string id, string phone) {
        unidata[id]->phone = phone;
    }
};

#endif