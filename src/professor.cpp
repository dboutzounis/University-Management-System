#include "../include/professor.h"
#include "../include/course.h"
#include "../include/extrafuncs.h"
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

// Constructing Professor
Professor::Professor() : Person(), trait(""), rank(""), officeNo("") {}

// Constructing Professor using the parameters on the initializer list
Professor::Professor(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string trait, string rank, string officeNo) : Person(fname, lname, day, month, year, gender, nationality, email, phone), trait(trait), rank(rank), officeNo(officeNo) {}

// Constructing Professor using the parameters on the initializer list
Professor::Professor(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string id, string trait, string rank, string officeNo) : Person(fname, lname, day, month, year, gender, nationality, email, phone, id), trait(trait), rank(rank), officeNo(officeNo) {}

// Copy constructing Professor object
Professor::Professor(const Professor &old_obj) {
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
        this->trait = old_obj.trait;
        this->rank = old_obj.rank;
        this->officeNo = old_obj.officeNo;
    }
}

// Destructing Professor
Professor::~Professor() {
    courses.clear();
}

// Allocating memory for Professor
Person *Professor::create() const {
    return new Professor(*this);
}

// Helper print function for overloading << operator
void Professor::print(ostream &str) const {
    str << "Professor" << endl;
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
    str << "Trait: " << this->trait << endl;
    str << "Rank: " << this->rank << endl;
    str << "Office Number: " << this->officeNo << endl;
}

// Passing Professor data to the output stream (display)
ostream &operator<<(ostream &str, Professor &obj) {
    obj.print(str);
    return str;
}

// Passing Student data to the input stream (read)
istream &operator>>(istream &str, Professor &obj) {
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
    cout << "Input ID: ";
    str >> obj.id;
    cout << "Input trait: ";
    str >> obj.trait;
    cout << "Input rank: ";
    str >> obj.rank;
    cout << "Input office number: ";
    str >> obj.officeNo;

    return str;
}

// Displaying Professor
void Professor::display() const {
    cout << this;
}

// Displaying a Course from the vector of Professor's Courses
void Professor::displayCourse(const string &courseName) const {
    vector<Course *>::const_iterator const_iter;
    for (const_iter = courses.begin(); const_iter != courses.end(); ++const_iter) {
        if ((*const_iter)->getName().compare(courseName) == 0) {
            (*const_iter)->display();
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Searching a Course in the vector of Professor's Courses
bool Professor::searchCourse(const string &courseName) const {
    vector<Course *>::const_iterator const_iter;
    for (const_iter = courses.begin(); const_iter != courses.end(); ++const_iter) {
        if ((*const_iter)->getName().compare(courseName) == 0) {
            return true;
        }
    }
    return false;
}

// Inserting a Course in the vector of Professor's Courses
bool Professor::insertCourse(Course *course) {
    if (!searchCourse(course->getName())) {
        courses.push_back(course);
        return true;
    }
    return false;
}

// Removing a Course from the vector of Professor's Courses
bool Professor::removeCourse(const string &courseName) {
    vector<Course *>::iterator iter;
    for (iter = courses.begin(); iter != courses.end(); ++iter) {
        if ((*iter)->getName().compare(courseName) == 0) {
            courses.erase(iter);
            return true;
        }
    }
    return false;
}

// Displaying Statistics of all Courses of current semester
void Professor::displayStatistics() const {
    vector<Course *>::const_iterator const_iter;
    map<string, double> grades;
    map<string, double>::const_iterator g_iter;
    
    cout << "Statistics of Professor " << lname << " " << fname << endl;
    cout << "Current Semester Course Statistics:" << endl; 

    for (const_iter = courses.begin(); const_iter != courses.end(); ++const_iter) {
        grades = (*const_iter)->getGrades();
        double sum = 0.0;
        int count = 0, countP = 0, distribution[11] = {0};
        for (g_iter = grades.begin(); g_iter != grades.end(); ++g_iter) {
            if((*const_iter)->searchStudent(g_iter->first)){    
                count++;
                if (g_iter->second >= 5.0)
                    countP++;
                sum += g_iter->second;
                distribution[static_cast<int>(round(g_iter->second))]++;
            }
        }
        if (count == 0) {
            cout << "No students participated in " << (*const_iter)->getName() << " this semester." << endl;
            continue;
        }
        cout << "Statistics of course " << (*const_iter)->getName() << ":" << endl;
        cout << "Students that took part in the exams were " << count << "." << endl;
        cout << "Success rate: " << (static_cast<double>(countP) / count) * 100 << "%." << endl;
        cout << "Fail rate: " << 100 - (static_cast<double>(countP) / count) * 100 << "%." << endl;
        for (int i = 0; i < 11; i++)
            cout << "Students with grade " << i << " were: " << distribution[i] << "." << endl;
        cout << "Average grade: " << sum / count << "." << endl;
    }

    cout << "\nAll-Time Course Statistics:" << endl; 

    for (const_iter = courses.begin(); const_iter != courses.end(); ++const_iter) {
        grades = (*const_iter)->getGrades();
        if (grades.size() == 0) {
            cout << "No students participated in " << (*const_iter)->getName() << "." << endl;
            continue;
        }
        double sum = 0.0;
        int count = 0, distribution[11] = {0};
        for (g_iter = grades.begin(); g_iter != grades.end(); ++g_iter) {
            if (g_iter->second >= 5.0)
                count++;
            sum += g_iter->second;
            distribution[static_cast<int>(round(g_iter->second))]++;
        }
        cout << "Statistics of course " << (*const_iter)->getName() << ":" << endl;
        cout << "Students that took part in the exams were " << grades.size() << "." << endl;
        cout << "Success rate: " << (static_cast<double>(count) / grades.size()) * 100 << "%." << endl;
        cout << "Fail rate: " << 100 - (static_cast<double>(count) / grades.size()) * 100 << "%." << endl;
        for (int i = 0; i < 11; i++)
            cout << "Students with grade " << i << " were: " << distribution[i] << "." << endl;
        cout << "Average grade: " << sum / grades.size() << "." << endl
             << endl;
    }
}