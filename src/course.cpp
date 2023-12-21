#include "../include/course.h"
#include <iostream>
#include <string>

Course::Course() : name(""), ects(0), courseType(false), semester(0) {}

Course::Course(string name, int semester, int ects, bool courseType) : name(name), ects(ects), courseType(courseType), semester(semester) {}

Course::~Course() {}

void Course::print(vector<Professor *> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl
             << endl;
    }
    cout << "\n"
         << endl;
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
