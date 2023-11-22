#include "../include/person.h"
#include <iostream>
#include <string>
using namespace std;

int Person::count = 0;

Person::Person() : fname(""), lname(""), age(0), gender('\0'), email(""), phone(""), id("") {
    count++;
}

Person::Person(string fname, string lname, int age, char gender, string email, string phone, string id) : fname(fname), lname(lname), age(age), gender(gender), email(email), phone(phone), id(id) {
    count++;
}

Person::~Person() {
    count--;
}

ostream &operator<<(ostream &str, Person &obj) {
    str << "Full name: " << obj.fname << " " << obj.lname << endl;
    str << "Age: " << obj.age << endl;
    if (obj.gender == 'M' || obj.gender == 'm') {
        str << "Gender: Male" << endl;
    } else if (obj.gender == 'F' || obj.gender == 'f') {
        str << "Gender: Female" << endl;
    } else {
        str << "Gender: Other" << endl;
    }
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
    cout << "Input your age: ";
    str >> obj.age;
    cout << "Input your gender: ";
    str >> obj.gender;
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

int Person::getAge() const {
    return age;
}

string Person::getGender() const {
    if (gender == 'M' || gender == 'm') {
        return "Male";
    } else if (gender == 'F' || gender == 'f') {
        return "Female";
    } else {
        return "Unknown";
    }
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

void Person::setFname(string fname) {
    this->fname = fname;
}

void Person::setLname(string lname) {
    this->lname = lname;
}

void Person::setAge(int age) {
    this->age = age;
}

void Person::setGender(char gender) {
    this->gender = gender;
}

void Person::setEmail(string email) {
    this->email = email;
}

void Person::setPhone(string phone) {
    this->phone = phone;
}

void Person::setId(string id) {
    this->id = id;
}