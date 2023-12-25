#include "../include/course.h"
#include "../include/professor.h"
#include <iostream>
#include <string>

Course::Course() : name(""), ects(0), courseType(false), semester(0) {}

Course::Course(string name, unsigned int semester, unsigned int ects, bool courseType) : name(name), ects(ects), courseType(courseType), semester(semester) {}

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

Course::~Course() {}

void Course::print(map<string, Professor *> &m) {
    map<string, Professor *>::iterator iter;
    for (iter = m.begin(); iter != m.end(); ++iter) {
        cout << iter->second;
    }
    cout << endl;
}

ostream &operator<<(ostream &str, Course &obj) {
    str << "Course: " << obj.name << endl;
    str << "Semester: " << obj.semester << endl;
    str << "ECTS: " << obj.ects << endl;
    if (obj.courseType) {
        str << "Mandatory course" << endl;
    } else {
        str << "Optional course" << endl;
    }
    str << "Teaching staff:" << endl;
    obj.print(obj.staff);

    return str;
}

istream &operator>>(istream &str, Course &obj) {
    cout << "Input the name of the course: ";
    str >> obj.name;
    cout << "Input the semester of this course: ";
    str >> obj.semester;
    cout << "Input the ECTS of the course: ";
    str >> obj.ects;
    cout << "Input 1 if course is mandatory and 0 if it's optional: ";
    str >> obj.courseType;

    return str;
}

void Course::display() const {
    cout << this;
}
