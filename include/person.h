#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

// Definition of Person Class
class Person {
private:
    static int count;

protected:
    string fname;
    string lname;
    int day, month, year;
    char gender;
    string nationality;
    string email;
    string phone;
    string id;

    // Helper functions
    virtual Person *create() const = 0;
    virtual void print(ostream &str) const;

public:
    // Constructor
    Person();
    // Constructor with parameters
    Person(string fname, string lname, int day, int month, int year, char gender, string nationality, string email, string phone, string id);
    // Destructor
    virtual ~Person();
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Person &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Person &obj);
    // Display Person
    virtual void display() const = 0;

    /* Other Functions */

    inline string getFname() const {
        return fname;
    }

    inline string getLname() const {
        return lname;
    }

    inline string getBirthDate() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    inline string getGender() const {
        if (gender == 'M' || gender == 'm')
            return "Male";
        else if (gender == 'F' || gender == 'f')
            return "Female";

        return "Other";
    }

    inline string getNationality() const {
        return nationality;
    }

    inline string getEmail() const {
        return email;
    }

    inline string getPhone() const {
        return phone;
    }

    inline string getId() const {
        return id;
    }

    inline static int getCount() {
        return count;
    }

    // Allowing Secretary class to access the private members of Person Class (friend class)
    friend class Secretary;
};

#endif