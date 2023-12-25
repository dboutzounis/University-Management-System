#include "../include/student.h"
#include "../include/extrafuncs.h"
#include <iostream>
#include <string>
using namespace std;

// Constructing Student
Student::Student() : Person(), semester(0), ects(0), gpa(0), memberSince(0) {}

// Constructing Student using the parameters on the initializer list
Student::Student(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, unsigned int semester, unsigned int ects, double gpa, unsigned int memberSince) : Person(fname, lname, day, month, year, gender, nationality, email, phone), semester(1), ects(0), gpa(gpa), memberSince(memberSince) {}

// Constructing Student using the parameters on the initializer list
Student::Student(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string id, unsigned int semester, unsigned int ects, double gpa, unsigned int memberSince) : Person(fname, lname, day, month, year, gender, nationality, email, phone, id), semester(1), ects(0), gpa(gpa), memberSince(memberSince) {}

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

// Destructing Person
Student::~Student() {}

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
    cout << "Input your first name: ";
    str >> obj.fname;
    cout << "Input your last name: ";
    str >> obj.lname;
    cout << "Input your birth date: " << endl;
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
    cout << "Input your gender ('M' or 'm' for male, 'F' or 'f' for female and 'O' or 'o' for other): ";
    str >> obj.gender;
    cout << "Input your nationality: ";
    str >> obj.nationality;
    cout << "Input your e-mail: ";
    str >> obj.email;
    cout << "Input your phone number: ";
    str >> obj.phone;
    cout << "Input your ID: ";
    str >> obj.id;
    cout << "Input your current semester: ";
    str >> obj.semester;
    cout << "Input your ECTS: ";
    str >> obj.ects;
    cout << "Input your GPA: ";
    str >> obj.gpa;
    cout << "Input your starting year: ";
    str >> obj.memberSince;

    return str;
}

// Display Student
void Student::display() const {
    cout << this;
}