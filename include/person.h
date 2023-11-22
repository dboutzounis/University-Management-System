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
    int age;
    char gender;
    string email;
    string phone;
    string id;
    static int count;

public:
    Person();
    Person(string fname, string lname, int age, char gender, string email, string phone, string id);
    ~Person();
    friend ostream &operator<<(ostream &str, Person &obj);
    friend istream &operator>>(istream &str, Person &obj);
    string getFname() const;
    string getLname() const;
    int getAge() const;
    string getGender() const;
    string getEmail() const;
    string getPhone() const;
    string getId() const;
    static int getCount();
    void setFname(string fname);
    void setLname(string lname);
    void setAge(int age);
    void setGender(char gender);
    void setEmail(string email);
    void setPhone(string phone);
    void setId(string id);
};

#endif