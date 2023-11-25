#include "../include/person.h"
#include <iostream>
#include <string>
using namespace std;

// Initializing the person counter
int Person::count = 0;

// Constructing Person
Person::Person() : fname(""), lname(""), day(0), month(0), year(0), gender('\0'), nationality(""), email(""), phone(""), id("") {
    count++;
}

// Constructing Person using the parameters on the initializer list
Person::Person(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id) : fname(fname), lname(lname), day(day), month(month), year(year), gender(gender), nationality(nationality), email(email), phone(phone), id(id) {
    count++;
}

// Destructing Person
Person::~Person() {
    count--;
}

// Passing Person data to the output stream (display)
ostream &operator<<(ostream &str, Person &obj) {
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

    return str;
}

// Passing Person data to the input stream (read)
istream &operator>>(istream &str, Person &obj) {
    cout << "Input your first name: ";
    str >> obj.fname;
    cout << "Input your last name: ";
    str >> obj.lname;
    cout << "Input your birth date: " << endl;
    cout << "Day: ";
    str >> obj.day;
    cout << "Month: ";
    str >> obj.month;
    cout << "Year: ";
    str >> obj.year;
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

    return str;
}
