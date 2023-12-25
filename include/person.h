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
    unsigned int day, month, year;
    char gender;
    string nationality;
    string email;
    string phone;
    string id;

    // Helper functions
    virtual void print(ostream &str) const;

public:
    // Constructor
    Person();
    // Constructor with parameters
    Person(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone);
    Person(string fname, string lname, unsigned int day, unsigned int month, unsigned int year, char gender, string nationality, string email, string phone, string id);
    // Destructor
    virtual ~Person();
    // Output stream operator overloading
    friend ostream &operator<<(ostream &str, Person &obj);
    // Input stream operator overloading
    friend istream &operator>>(istream &str, Person &obj);
    // Display Person
    virtual void display() const = 0;
    // Create Person
    virtual Person *create() const = 0;

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

    inline string getID() const {
        return id;
    }

    inline static int getCount() {
        return count;
    }

    inline void setFname(const string &fname) {
        this->fname = fname;
    }

    inline void setLname(const string &lname) {
        this->fname = lname;
    }

    inline void setBirthDate(unsigned int day, unsigned int month, unsigned int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    inline void setGender(char gender) {
        this->gender = gender;
    }

    inline void setNationality(const string &nationality) {
        this->nationality = nationality;
    }

    inline void setEmail(const string &email) {
        this->email = email;
    }

    inline void setPhone(const string &phone) {
        this->phone = phone;
    }

    inline void setID(const string &id) {
        this->id = id;
    }
};

#endif