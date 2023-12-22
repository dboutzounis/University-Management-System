#pragma once
#ifndef SECRETARY_H
#define SECRETARY_H

#include "course.h"
#include "professor.h"
#include "student.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
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
    void display(const string &id) const;
    // Search Person in the map
    bool search(const string &id) const;
    // Insert Person in the map
    bool insert(const Person &person);
    // Remove Person from the map
    bool remove(const string &id);
    // Unidata map size
    int count();
    // Display Course
    void displayCourse(const string &courseName) const;
    // Search Course
    bool searchCourse(const string &courseName) const;
    // Insert Course to Secretary
    bool insertCourse(const Course &course);
    // Remove Course from Secretary
    bool removeCourse(const string &courseName);
    // Student registration to course
    void registerStudentToCourse(const string &coursename, const string &id);
    // Course assignment to professor
    void assignCourseToProfessor(const string &coursename, const string &id);

    /* Other Functions */

    inline string getDepartment() const {
        return department;
    }

    inline int getYearsOfStudy() const {
        return yearsOfStudy;
    }

    inline string getFname(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->fname;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline string getLname(string id) const {
        try {
            if (this->search(id) == false)
                throw;
            return unidata.at(id)->lname;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline string getBirthDate(string id) const {
        try {
            if (this->search(id) == false)
                throw;
            return to_string(unidata.at(id)->day) + "/" + to_string(unidata.at(id)->month) + "/" + to_string(unidata.at(id)->year);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline string getGender(string id) const {
        try {
            if (this->search(id) == false)
                throw;
            if (unidata.at(id)->gender == 'M' || unidata.at(id)->gender == 'm')
                return "Male";
            else if (unidata.at(id)->gender == 'F' || unidata.at(id)->gender == 'f')
                return "Female";
            return "Other";
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline string getNationality(string id) const {
        try {
            if (this->search(id) == false)
                throw;
            return unidata.at(id)->nationality;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline string getEmail(string id) const {
        try {
            if (this->search(id) == false)
                throw;
            return unidata.at(id)->email;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline string getPhone(string id) const {
        try {
            if (this->search(id) == false)
                throw;
            return unidata.at(id)->phone;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setFname(string id, string fname) {
        try {
            if (this->search(id) == false)
                throw;
            unidata[id]->fname = fname;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setLname(string id, string lname) {
        try {
            if (this->search(id) == false)
                throw;
            unidata[id]->lname = lname;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setBirthDate(string id, int day, int month, int year) {
        try {
            if (this->search(id) == false)
                throw;
            unidata[id]->day = day;
            unidata[id]->month = month;
            unidata[id]->year = year;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setGender(string id, char gender) {
        try {
            if (this->search(id) == false)
                throw;
            unidata[id]->gender = gender;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setNationality(string id, string nationality) {
        try {
            if (this->search(id) == false)
                throw;
            unidata[id]->nationality = nationality;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setEmail(string id, string email) {
        try {
            if (this->search(id) == false)
                throw;
            unidata[id]->email = email;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setPhone(string id, string phone) {
        try {
            if (this->search(id) == false)
                throw;
            unidata[id]->phone = phone;
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setSemester(string id, int semester) {
        try {
            if (this->search(id) == false)
                throw(0);
            if (typeid(*unidata[id]) == typeid(Professor))
                throw;
            dynamic_cast<Student *>(unidata[id])->semester = semester;

        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Student's semester but gave a Professor's ID." << endl;
        }
    }

    inline void setECTS(string id, int ects) {
        try {
            if (this->search(id) == false)
                throw(0);
            if (typeid(*unidata[id]) == typeid(Professor))
                throw;
            dynamic_cast<Student *>(unidata[id])->ects = ects;
        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Student's ECTS but gave a Professor's ID." << endl;
        }
    }

    inline void setGPA(string id, double gpa) {
        try {
            if (this->search(id) == false)
                throw(0);
            if (typeid(*unidata[id]) == typeid(Professor))
                throw;
            dynamic_cast<Student *>(unidata[id])->gpa = gpa;

        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Student's GPA but gave a Professor's ID." << endl;
        }
    }

    inline void setStartingYear(string id, int memberSince) {
        try {
            if (this->search(id) == false)
                throw(0);
            if (typeid(*unidata[id]) == typeid(Professor))
                throw;
            dynamic_cast<Student *>(unidata[id])->memberSince = memberSince;

        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Student's starting year but gave a Professor's ID." << endl;
        }
    }

    inline void setTrait(string id, const string &trait) {
        try {
            if (this->search(id) == false)
                throw(0);
            if (typeid(*unidata[id]) == typeid(Student))
                throw;
            dynamic_cast<Professor *>(unidata[id])->trait = trait;

        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Professor's trait but gave a Student's ID." << endl;
        }
    }

    inline void setRank(string id, const string &rank) {
        try {
            if (this->search(id) == false)
                throw(0);
            if (typeid(*unidata[id]) == typeid(Student))
                throw;
            dynamic_cast<Professor *>(unidata[id])->rank = rank;

        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Professor's rank but gave a Student's ID." << endl;
        }
    }

    inline void setOfficeNo(string id, const string &officeNo) {
        try {
            if (this->search(id) == false)
                throw(0);
            if (typeid(*unidata[id]) == typeid(Student))
                throw;
            dynamic_cast<Professor *>(unidata[id])->officeNo = officeNo;

        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Professor's office number but gave a Student's ID." << endl;
        }
    }
};

#endif