#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string fname;
    string lname;
    int day, month, year;
    char gender;
    string nationality;
    string email;
    string phone;
    string id;
    static int count;

public:
    Person();
    Person(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id);
    ~Person();
    friend ostream &operator<<(ostream &str, Person &obj);
    friend istream &operator>>(istream &str, Person &obj);
    string getFname() const;
    string getLname() const;
    string getBirthDate() const;
    string getGender() const;
    string getNationality() const;
    string getEmail() const;
    string getPhone() const;
    string getId() const;
    static int getCount();
    void setEmail(string email);
    void setPhone(string phone);
};

#endif