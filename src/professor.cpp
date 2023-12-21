#include "../include/professor.h"
#include "../include/extrafuncs.h"
#include <iostream>
#include <string>
using namespace std;

// Constructing Professor
Professor::Professor() : Person(), trait(""), rank(""), officeNo("") {}

// Constructing Professor using the parameters on the initializer list
Professor::Professor(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id, string trait, string rank, string officeNo) : Person(fname, lname, day, month, year, gender, nationality, email, phone, id), trait(trait), rank(rank), officeNo(officeNo) {}

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
Professor::~Professor() {}

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

// Display Professor
void Professor::display() const {
    cout << this;
}