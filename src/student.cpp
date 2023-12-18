#include "../include/student.h"
#include <iostream>
#include <string>
using namespace std;

// Constructing Student
Student::Student() : Person(), semester(0), ects(0), memberSince(0), gpa(0) {}

// Constructing Student using the parameters on the initializer list
Student::Student(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id, int semester, int ects, int memberSince) : Person(fname, lname, day, month, year, gender, nationality, email, phone, id), semester(1), ects(0), memberSince(memberSince), gpa(0) {}

// Destructing Person
Student::~Student() {}

// Passing Student data to the output stream (display)
ostream &operator<<(ostream &str, Student &obj) {
    str << "Full name: " << obj.fname << " " << obj.lname << endl;
    str << "Birth Date: " << obj.day << "/" << obj.month << "/" << obj.year << endl;
    if (obj.gender == 'M' || obj.gender == 'm')
        str << "Gender: Male" << endl;
    else if (obj.gender == 'F' || obj.gender == 'f')
        str << "Gender: Female" << endl;
    else
        str << "Gender: Other" << endl;
    str << "Nationality: " << obj.nationality << endl;
    str << "E-mail: " << obj.email << endl;
    str << "Phone number: " << obj.phone << endl;
    str << "ID: " << obj.id << endl;
    str << "Semester: " << obj.semester << endl;
    str << "ECTS: " << obj.ects << endl;
    str << "GPA: " << obj.gpa << endl;
    str << "Member since: " << obj.memberSince << endl;

    return str;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust February for leap years
    if (month == 2 && isLeapYear(year))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];
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
    cout << "Input your starting year: ";
    str >> obj.memberSince;

    return str;
}