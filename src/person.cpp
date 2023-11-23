#include "../include/person.h"
#include <iostream>
#include <string>
using namespace std;

int Person::count = 0;

Person::Person() : fname(""), lname(""), day(0), month(0), year(0), gender('\0'), nationality(""), email(""), phone(""), id("") {
    count++;
}

Person::Person(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id) : fname(fname), lname(lname), day(day), month(month), year(year), gender(gender), nationality(nationality), email(email), phone(phone), id(id) {
    count++;
}

Person::~Person() {
    count--;
}

ostream &operator<<(ostream &str, Person &obj) {
    str << "Full name: " << obj.fname << " " << obj.lname << endl;
    str << "Birth Date: " << obj.day << "/" << obj.month << "/" << obj.year << endl;
    if (obj.gender == 'M' || obj.gender == 'm') {
        str << "Gender: Male" << endl;
    } else if (obj.gender == 'F' || obj.gender == 'f') {
        str << "Gender: Female" << endl;
    } else {
        str << "Gender: Other" << endl;
    }
    str << "Nationality: " << obj.nationality << endl;
    str << "E-mail: " << obj.email << endl;
    str << "Phone number: " << obj.phone << endl;
    str << "Academic ID: " << obj.id << endl;

    return str;
}

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
    cout << "Input your academic id: ";
    str >> obj.id;

    return str;
}

string Person::getFname() const {
    return fname;
}

string Person::getLname() const {
    return lname;
}

string Person::getBirthDate() const {
    string str = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    return str;
}

string Person::getGender() const {
    if (gender == 'M' || gender == 'm') {
        return "Male";
    } else if (gender == 'F' || gender == 'f') {
        return "Female";
    } else {
        return "Other";
    }
}

string Person::getNationality() const {
    return nationality;
}

string Person::getEmail() const {
    return email;
}

string Person::getPhone() const {
    return phone;
}

string Person::getId() const {
    return id;
}

int Person::getCount() {
    return count;
}

void Person::setEmail(string email) {
    this->email = email;
}

void Person::setPhone(string phone) {
    this->phone = phone;
}
