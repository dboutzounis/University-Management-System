#include "../include/student.h"
#include "../include/course.h"
#include "../include/extrafuncs.h"
#include <iostream>
#include <string>
using namespace std;

// Constructing Student
Student::Student() : Person(), semester(0), ects(0), gpa(0), memberSince(0) {}

// Constructing Student using the parameters on the initializer list
Student::Student(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, unsigned int semester, unsigned int ects, double gpa, unsigned int memberSince) : Person(fname, lname, day, month, year, gender, nationality, email, phone), semester(semester), ects(ects), gpa(gpa), memberSince(memberSince) {}

// Constructing Student using the parameters on the initializer list
Student::Student(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string id, unsigned int semester, unsigned int ects, double gpa, unsigned int memberSince) : Person(fname, lname, day, month, year, gender, nationality, email, phone, id), semester(semester), ects(ects), gpa(gpa), memberSince(memberSince) {}

// Copy constructing Student object
Student::Student(const Student &old_obj) {
    if (this != &old_obj) {
        this->fname = old_obj.fname;
        this->lname = old_obj.lname;
        this->day = old_obj.day;
        this->month = old_obj.month;
        this->year = old_obj.year;
        this->gender = old_obj.gender;
        this->nationality = old_obj.nationality;
        this->email = old_obj.email;
        this->phone = old_obj.phone;
        this->id = old_obj.id;
        this->semester = old_obj.semester;
        this->ects = old_obj.ects;
        this->gpa = old_obj.gpa;
        this->memberSince = old_obj.memberSince;
    }
}

// Destructing Student
Student::~Student() {
    courses.clear();
    passedCourses.clear();
}

// Allocating memory for Student
Person *Student::create() const {
    return new Student(*this);
}

// Helper print function for overloading << operator
void Student::print(ostream &str) const {
    str << "Student" << endl;
    str << "Full name: " << this->fname << " " << this->lname << endl;
    str << "Birth Date: " << this->day << "/" << this->month << "/" << this->year << endl;
    if (this->gender == 'M' || this->gender == 'm')
        str << "Gender: Male" << endl;
    else if (this->gender == 'F' || this->gender == 'f')
        str << "Gender: Female" << endl;
    else
        str << "Gender: Other" << endl;
    str << "Nationality: " << this->nationality << endl;
    str << "E-mail: " << this->email << endl;
    str << "Phone number: " << this->phone << endl;
    str << "ID: " << this->id << endl;
    str << "Semester: " << this->semester << endl;
    str << "ECTS: " << this->ects << endl;
    str << "GPA: " << this->gpa << endl;
    str << "Member since: " << this->memberSince << endl;
}

// Passing Student data to the output stream (display)
ostream &operator<<(ostream &str, Student &obj) {
    obj.print(str);
    return str;
}

// Passing Student data to the input stream (read)
istream &operator>>(istream &str, Student &obj) {
    cout << "Input first name: ";
    str >> obj.fname;
    cout << "Input last name: ";
    str >> obj.lname;
    cout << "Input birth date: " << endl;
    do {
        cout << "Day: ";
        str >> obj.day;
        cout << "Month: ";
        str >> obj.month;
        cout << "Year: ";
        str >> obj.year;
        if (!isValidDate(obj.day, obj.month, obj.year))
            cout << "Invalid date, try again." << endl;
    } while (!isValidDate(obj.day, obj.month, obj.year));
    cout << "Input gender ('M' or 'm' for male, 'F' or 'f' for female and 'O' or 'o' for other): ";
    str >> obj.gender;
    cout << "Input nationality: ";
    str >> obj.nationality;
    cout << "Input e-mail: ";
    str >> obj.email;
    cout << "Input phone number: ";
    str >> obj.phone;
    cout << "Input current semester: ";
    str >> obj.semester;
    cout << "Input starting year: ";
    str >> obj.memberSince;

    return str;
}

// Displaying Student
void Student::display() const {
    cout << this;
}

// Displaying a Course from the vector of Student's Courses
void Student::displayCourse(const string &courseName) const {
    vector<Course *>::const_iterator const_iter;
    for (const_iter = courses.begin(); const_iter != courses.end(); ++const_iter) {
        if ((*const_iter)->getName().compare(courseName) == 0) {
            (*const_iter)->display();
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Searching a Course in the vector of Student's Courses
bool Student::searchCourse(const string &courseName) const {
    vector<Course *>::const_iterator const_iter;
    for (const_iter = courses.begin(); const_iter != courses.end(); ++const_iter) {
        if ((*const_iter)->getName().compare(courseName) == 0) {
            return true;
        }
    }
    return false;
}

// Inserting a Course in the vector of Student's Courses
bool Student::insertCourse(Course *course) {
    if (!searchCourse(course->getName())) {
        courses.push_back(course);
        return true;
    }
    return false;
}

// Removing a Course from the vector of Student's Courses
bool Student::removeCourse(const string &courseName) {
    vector<Course *>::iterator iter;
    for (iter = courses.begin(); iter != courses.end(); ++iter) {
        if ((*iter)->getName().compare(courseName) == 0) {
            courses.erase(iter);
            return true;
        }
    }
    return false;
}

// Displaying a Passed Course from the vector of Student's Courses
void Student::displayPassedCourse(const string &courseName) const {
    vector<Course *>::const_iterator const_iter;
    for (const_iter = passedCourses.begin(); const_iter != passedCourses.end(); ++const_iter) {
        if ((*const_iter)->getName().compare(courseName) == 0) {
            (*const_iter)->display();
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Searching a Passed Course in the vector of Student's Courses
bool Student::searchPassedCourse(const string &courseName) const {
    vector<Course *>::const_iterator const_iter;
    for (const_iter = passedCourses.begin(); const_iter != passedCourses.end(); ++const_iter) {
        if ((*const_iter)->getName().compare(courseName) == 0) {
            return true;
        }
    }
    return false;
}

// Inserting a Passed Course in the vector of Student's Courses
bool Student::insertPassedCourse(Course *course) {
    if (!searchPassedCourse(course->getName())) {
        passedCourses.push_back(course);
        vector<Course *>::iterator iter;
        map<string, double> grades;
        int ectssum = 0;
        double sum = 0.0;
        for (iter = passedCourses.begin(); iter != passedCourses.end(); ++iter) {
            grades = (*iter)->getGrades();
            sum += ((*iter)->getEcts() * grades.at(id));
            ectssum += (*iter)->getEcts();
        }
        ects = ectssum;
        gpa = sum / ectssum;
        return true;
    }
    return false;
}

// Function that checks if a student has passed countMandatory mandatory courses
bool Student::mandatorypassed(int countMandatory) {
    int count = 0;
    vector<Course *>::iterator iter;
    for (iter = passedCourses.begin(); iter != passedCourses.end(); ++iter) {
        if ((*iter)->getCourseType().compare("Mandatory") == 0) {
            count++;
        }
    }
    if (count == countMandatory)
        return true;
    return false;
}

// Displaying Student grades
void Student::displayGrades() {
    map<string, double> grades;
    vector<Course *>::iterator iter;
    cout << "Current semester grades:" << endl;
    for (iter = courses.begin(); iter != courses.end(); ++iter) {
        grades = (*iter)->getGrades();
        cout << (*iter)->getName() << ": " << grades.at(id) << endl;
    }

    cout << "\nPrevious years grades:" << endl;
    for (iter = passedCourses.begin(); iter != passedCourses.end(); ++iter) {
        if (!searchCourse((*iter)->getName())) {
            grades = (*iter)->getGrades();
            cout << (*iter)->getName() << ": " << grades.at(id) << endl;
        }
    }

    cout << "\nGPA: " << gpa << endl;
}