#pragma once
#ifndef SECRETARY_H
#define SECRETARY_H

#include "person.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Secretary {
private:
    map<string, Person *> unidata;

public:
    Secretary();
    ~Secretary();
    Secretary(const Secretary &old_obj);
    Secretary &operator=(const Secretary &old_obj);
    Secretary &operator+=(Person *person);
    friend ostream &operator<<(ostream &str, Secretary &obj);
    friend istream &operator>>(istream &str, Secretary &obj);
    Person *createPerson(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id);
    bool search(Person *person);
};

#endif