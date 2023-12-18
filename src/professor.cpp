#include "../include/professor.h"
#include <iostream>
#include <string>
using namespace std;

// Constructing Professor
Professor::Professor() : Person(), trait(""), rank(""), officeNo("") {}

// Constructing Professor using the parameters on the initializer list
Professor::Professor(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id, string trait, string rank, string officeNo) : Person(fname, lname, day, month, year, gender, nationality, email, phone, id), trait(trait), rank(rank), officeNo(officeNo) {}

// Destructing Professor
Professor::~Professor() {}

// Passing Professor data to the output stream (display)
ostream &operator<<(ostream &str, Professor &obj) {
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
    str << "Trait: " << obj.trait << endl;
    str << "Rank: " << obj.rank << endl;
    str << "Office Number: " << obj.officeNo << endl;

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
istream &operator>>(istream &str, Professor &obj) {
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
    cout << "Input your trait: ";
    str >> obj.trait;
    cout << "Input your rank: ";
    str >> obj.rank;
    cout << "Input your office number: ";
    str >> obj.officeNo;

    return str;
}
