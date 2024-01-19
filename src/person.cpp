#include "../include/person.h"
#include "../include/extrafuncs.h"
#include <iostream>
#include <string>
using namespace std;

// Initializing the person counter
int Person::count = 0;

// Constructing Person
Person::Person() : fname(""), lname(""), day(0), month(0), year(0), gender('\0'), nationality(""), email(""), phone(""), id("0") {
    count++;
}

// Constructing Person using the parameters on the initializer list
Person::Person(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone) : fname(fname), lname(lname), day(day), month(month), year(year), gender(gender), nationality(nationality), email(email), phone(phone), id("0") {
    try {
        if (!isValidDate(day, month, year))
            throw(0);
    } catch (...) {
        cerr << "Error invalid birthdate given." << endl;
        exit(EXIT_FAILURE);
    }

    count++;
}

// Constructing Person using the parameters on the initializer list
Person::Person(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string id) : fname(fname), lname(lname), day(day), month(month), year(year), gender(gender), nationality(nationality), email(email), phone(phone), id(id) {
    try {
        if (!isValidDate(day, month, year))
            throw(0);
    } catch (...) {
        cerr << "Error invalid birthdate given." << endl;
        exit(EXIT_FAILURE);
    }

    count++;
}

// Destructing Person
Person::~Person() {
    count--;
}

// Helper print function for overloading << operator
void Person::print(ostream &str) const {
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
}

// Passing Person data to the output stream (display)
ostream &operator<<(ostream &str, Person &obj) {
    obj.print(str);
    return str;
}

// Passing Person data to the input stream (read)
istream &operator>>(istream &str, Person &obj) {
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

    return str;
}
