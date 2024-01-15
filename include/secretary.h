#pragma once

#include "course.h"
#include "person.h"
#include "professor.h"
#include "student.h"
#include <chrono>
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
    // Using the map from STL to store pairs of <int, vector<Course *>> (int = Semester, vector<Course *> holds all the Courses of a Semester)
    map<unsigned int, vector<Course *> > curriculum;
    string department;
    string departmentID;
    unsigned int yearsOfStudy;
    unsigned int currentYear;
    unsigned int graduationEcts;
    unsigned int *countStudents;
    unsigned int countProfessors;

    // Helper functions
    Person *allocatePerson(const Person &person);
    unsigned int getCurrentYear();
    string generateID(const Person &person);

public:
    // Constructor
    Secretary();
    // Constructor with the department name as parameter
    Secretary(string department, string departmentID, unsigned int yearsOfStudy, unsigned int graduationEcts);
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
    int size();
    // Display Course
    void displayCourse(const string &courseName) const;
    // Search Course
    bool searchCourse(const string &courseName) const;
    // Insert Course to Secretary
    bool insertCourse(const Course &course);
    // Remove Course from Secretary
    bool removeCourse(const string &courseName);
    // Transfer a Course to a new semester
    bool transferCourse(const string &courseName, unsigned int newSemester);
    // Student registration to course
    bool registerStudentToCourse(const string &courseName, const string &id);
    // Unregister Student from Course
    bool unregisterStudentFromCourse(const string &courseName, const string &id);
    // Unassign Course from Professor
    bool unassignCourseFromProfessor(const string &courseName, const string &id);
    // Course assignment to professor
    bool assignCourseToProfessor(const string &courseName, const string &id);
    // Cin grades input from professor
    void assignGrades(const string &courseName, const string &id);
    // Function that checks if a student graduates
    bool graduates(const string &id);
    // Function that displays all students that graduate
    void displayGraduates();
    // Function that displays statistics for a professor's courses
    void displayStatistics(const string &id);
    // Function that displays a student's grades
    void displayGrades(const string &id);
    // Function that parses input info and inserts it to the Secretary
    void parseInput(const string &path);


    /* Other Functions */

    unsigned int getCourseEcts(const string &courseName) const;
    unsigned int getCourseSemester(const string &courseName) const;
    string getCourseType(const string &courseName) const;
    void setCourseName(const string &courseName, const string &newCourseName);
    void setCourseEcts(const string &courseName, unsigned int newEcts);
    void setCourseSemester(const string &courseName, unsigned int newSemester);
    void setCourseType(const string &courseName, bool newCourseType);

    inline string getDepartment() const {
        return department;
    }

    inline int getYearsOfStudy() const {
        return yearsOfStudy;
    }

    inline unsigned int getGraduationEcts() const {
        return graduationEcts;
    }

    inline void setDepartment(const string &str) {
        department = str;
    }

    inline void setYearsOfStudy(unsigned int n) {
        yearsOfStudy = n;
    }

    inline void setGraduationEcts(unsigned int n) {
        graduationEcts = n;
    }

    inline string getFname(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->getFname();
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
        return "";
    }

    inline string getLname(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->getLname();
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
        return "";
    }

    inline string getBirthDate(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->getBirthDate();
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
        return "";
    }

    inline string getGender(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->getGender();
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
        return "";
    }

    inline string getNationality(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->getNationality();
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
        return "";
    }

    inline string getEmail(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->getEmail();
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
        return "";
    }

    inline string getPhone(string id) const {
        try {
            if (this->search(id) == false)
                throw(0);
            return unidata.at(id)->getPhone();
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
        return "";
    }

    inline void setFname(string id, string fname) {
        try {
            if (this->search(id) == false)
                throw(0);
            unidata[id]->setFname(fname);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setLname(string id, string lname) {
        try {
            if (this->search(id) == false)
                throw(0);
            unidata[id]->setLname(lname);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setBirthDate(string id, unsigned int day, unsigned int month, unsigned int year) {
        try {
            if (this->search(id) == false)
                throw(0);
            unidata[id]->setBirthDate(day, month, year);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setGender(string id, char gender) {
        try {
            if (this->search(id) == false)
                throw(0);
            unidata[id]->setGender(gender);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setNationality(string id, string nationality) {
        try {
            if (this->search(id) == false)
                throw(0);
            unidata[id]->setNationality(nationality);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setEmail(string id, string email) {
        try {
            if (this->search(id) == false)
                throw(0);
            unidata[id]->setEmail(email);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setPhone(string id, string phone) {
        try {
            if (this->search(id) == false)
                throw(0);
            unidata[id]->setPhone(phone);
        } catch (...) {
            cerr << "Non existing ID." << endl;
        }
    }

    inline void setSemester(string id, unsigned int semester) {
        try {
            if (this->search(id) == false)
                throw(0);
            Person *p = unidata.at(id);
            if (typeid(*p) == typeid(Professor))
                throw('a');
            dynamic_cast<Student *>(unidata[id])->setSemester(semester);
        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Student's semester but gave a Professor's ID." << endl;
        }
    }

    inline void setECTS(string id, unsigned int ects) {
        try {
            if (this->search(id) == false)
                throw(0);
            Person *p = unidata.at(id);
            if (typeid(*p) == typeid(Professor))
                throw('a');
            dynamic_cast<Student *>(unidata[id])->setEcts(ects);
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
            Person *p = unidata.at(id);
            if (typeid(*p) == typeid(Professor))
                throw('a');
            dynamic_cast<Student *>(unidata[id])->setGPA(gpa);
        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Student's GPA but gave a Professor's ID." << endl;
        }
    }

    inline void setStartingYear(string id, unsigned int memberSince) {
        try {
            if (this->search(id) == false)
                throw(0);
            Person *p = unidata.at(id);
            if (typeid(*p) == typeid(Professor))
                throw('a');
            dynamic_cast<Student *>(unidata[id])->setStartingYear(memberSince);
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
            Person *p = unidata.at(id);
            if (typeid(*p) == typeid(Student))
                throw('a');
            dynamic_cast<Professor *>(unidata[id])->setTrait(trait);
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
            Person *p = unidata.at(id);
            if (typeid(*p) == typeid(Student))
                throw('a');
            dynamic_cast<Professor *>(unidata[id])->setRank(rank);
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
            Person *p = unidata.at(id);
            if (typeid(*p) == typeid(Student))
                throw('a');
            dynamic_cast<Professor *>(unidata[id])->setOfficeNo(officeNo);
        } catch (int n) {
            cerr << "Non existing ID." << endl;
        } catch (...) {
            cerr << "Error - You tried to change the Professor's office number but gave a Student's ID." << endl;
        }
    }
};
