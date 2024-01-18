#include "../include/course.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


// Constructor
Course::Course() : name(""), ects(0), courseType(false), semester(0) {}

// Constructor with parameters
Course::Course(string name, unsigned int semester, unsigned int ects, bool courseType) : name(name), ects(ects), courseType(courseType), semester(semester) {}

// Copy Constructor
Course::Course(const Course &old_obj) {
    if (this != &old_obj) {
        this->name = old_obj.name;
        this->ects = old_obj.ects;
        this->courseType = old_obj.courseType;
        this->semester = old_obj.semester;
        this->staff = old_obj.staff;
        this->students = old_obj.students;
        this->grades = old_obj.grades;
    }
}

// Destructor
Course::~Course() {
    staff.clear();
    students.clear();
    grades.clear();
}

// Helper function for output stream operator overloading
void Course::print(ostream &str) {
    str << "Course: " << name << endl;
    str << "Semester: " << semester << endl;
    str << "ECTS: " << ects << endl;
    if (courseType)
        str << "Type: Mandatory" << endl;
    else
        str << "Type: Optional" << endl;
    str << "Teaching staff:" << endl;
    map<string, Professor *>::iterator iter;
    for (iter = staff.begin(); iter != staff.end(); ++iter)
        str << iter->second->getFname() << " " << iter->second->getLname() << " E-mail: " << iter->second->getEmail() << " Phone: " << iter->second->getPhone() << endl;
    str << endl;
}

// Output stream operator overloading
ostream &operator<<(ostream &str, Course &obj) {    
    obj.print(str);
    return str;
}

// Input stream operator overloading
istream &operator>>(istream &str, Course &obj) {
    cout << "Input the name of the Course: ";
    str >> obj.name;
    cout << "Input the semester of this Course: ";
    str >> obj.semester;
    cout << "Input the ECTS of the Course: ";
    str >> obj.ects;
    cout << "Input 1 if course is mandatory and 0 if it's optional: ";
    str >> obj.courseType;

    return str;
}

// Display Course
void Course::display() const {
    cout << this;
}

// Display Professor
void Course::displayProfessor(const string &id) const {
    if (searchProfessor(id)) {
        staff.at(id)->display();
        return;
    }
    cout << "Professor not found." << endl;
}

// Search Professor
bool Course::searchProfessor(const string &id) const {
    map<string, Professor *>::const_iterator const_iter;
    for (const_iter = staff.begin(); const_iter != staff.end(); ++const_iter) {
        if (const_iter->second->getID().compare(id) == 0) {
            return true;
        }
    }
    return false;
}

// Insert Professor
bool Course::insertProfessor(Professor *professor) {
    if (!searchProfessor(professor->getID())) {
        staff.insert(pair<string, Professor *>(professor->getID(), professor));
        return true;
    }
    return false;
}

// Remove Professor
bool Course::removeProfessor(const string &id) {
    if (searchProfessor(id)) {
        staff.erase(id);
        return true;
    }
    return false;
}

// Display Student
void Course::displayStudent(const string &id) const {
    if (searchStudent(id)) {
        students.at(id)->display();
        cout << name << " grade is " << grades.at(id) << endl;
        return;
    }
    cout << "Student not found." << endl;
}

// Search Student
bool Course::searchStudent(const string &id) const {
    map<string, Student *>::const_iterator const_iter;
    for (const_iter = students.begin(); const_iter != students.end(); ++const_iter) {
        if (const_iter->second->getID().compare(id) == 0) {
            return true;
        }
    }
    return false;
}

// Insert Student
bool Course::insertStudent(Student *student) {
    if (!searchStudent(student->getID())) {
        students.insert(pair<string, Student *>(student->getID(), student));
        grades.insert(pair<string, double>(student->getID(), NAN));
        return true;
    }
    return false;
}

// Remove Student
bool Course::removeStudent(const string &id) {
    if (searchStudent(id)) {
        students.erase(id);
        return true;
    }
    return false;
}
