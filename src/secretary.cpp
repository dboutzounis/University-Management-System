#include "../include/secretary.h"
#include <iostream>
#include <map>
#include <string>

// Constructing Secretary
Secretary::Secretary() : department(""), yearsOfStudy(0) {}

// Constructing Secretary using the parameters on the initializer list
Secretary::Secretary(string department, int yearsOfStudy) : department(department), yearsOfStudy(yearsOfStudy) {}

// Destructing the dymically alocated memory of Person objects
Secretary::~Secretary() {
    map<string, Person *>::iterator iter;

    for (iter = unidata.begin(); iter != unidata.end(); ++iter)
        delete iter->second;
    unidata.clear();
}

Person *Secretary::allocatePerson(const Person &person) {
    Person *newP = person.create();
    return newP;
}

// Copy Constructing Secretary object
Secretary::Secretary(const Secretary &old_obj) {
    if (this != &old_obj) {
        // Deallocating memory of the current Secretary instance, so we can copy the old_obj
        map<string, Person *>::iterator iter;
        for (iter = unidata.begin(); iter != unidata.end(); ++iter)
            delete iter->second;
        unidata.clear();

        // Copying old_obj to the current Secretary instance
        map<string, Person *>::const_iterator const_iter;
        for (const_iter = old_obj.unidata.begin(); const_iter != old_obj.unidata.end(); ++const_iter) {
            Person *person = allocatePerson(*(const_iter->second));
            unidata.insert(pair<string, Person *>(person->id, person));
        }
        department = old_obj.department;
        yearsOfStudy = old_obj.yearsOfStudy;
    }
}

// Overloading operator= to copy construct
Secretary Secretary::operator=(const Secretary &old_obj) {
    if (this != &old_obj) {
        // Deallocating memory of the current Secretary instance, so we can copy the old_obj
        map<string, Person *>::iterator iter;
        for (iter = unidata.begin(); iter != unidata.end(); ++iter)
            delete iter->second;
        unidata.clear();

        // Copying old_obj to the current Secretary instance
        map<string, Person *>::const_iterator const_iter;
        for (const_iter = old_obj.unidata.begin(); const_iter != old_obj.unidata.end(); ++const_iter) {
            Person *person = allocatePerson(*(const_iter->second));
            unidata.insert(pair<string, Person *>(person->id, person));
        }
        department = old_obj.department;
        yearsOfStudy = old_obj.yearsOfStudy;
    }

    return *this;
}

// Overloading operator+= to add a new Person to the map
Secretary Secretary::operator+=(const Person &person) {
    if (!search(person.id)) {
        // Allocating memory for new Person
        Person *p = allocatePerson(person);
        // Inserting the new Person to the unidata map
        unidata.insert(pair<string, Person *>(p->id, p));
    }

    return *this;
}

// Overloading operator-= to remove Person from the map
Secretary Secretary::operator-=(const Person &person) {
    // Searching if the Person exists in order to remove him/her
    if (search(person.id)) {
        delete unidata[person.id];
        unidata.erase(person.id);
    }

    return *this;
}

// Passing Secretary data to the output stream (display)
ostream &operator<<(ostream &str, Secretary &obj) {
    str << endl;
    str << "Department " << obj.department << " data:" << endl;
    str << endl;

    map<string, Person *>::iterator iter;
    int c = 0;
    for (iter = obj.unidata.begin(); iter != obj.unidata.end(); ++iter) {
        str << endl;
        str << "Person " << ++c << ":" << endl;
        str << *iter->second << endl;
    }

    return str;
}

// Passing Secretary data to the input stream (read)
istream &operator>>(istream &str, Secretary &obj) {
    int countPeople;

    cout << "How many people would you like to insert? ";
    str >> countPeople;

    for (int i = 0; i < countPeople; i++) {
        char type;
        cout << "Type 's' or 'S' to add a student, else type 'p' or 'P' to add a proffesor: ";
        do {
            str >> type;
            if (type != 's' && type != 'S' && type != 'p' && type != 'P')
                cout << "Inut wrong, try again: ";
        } while (type != 's' && type != 'S' && type != 'p' && type != 'P');
        if (type == 's' || type == 'S') {
            Student s;
            str >> s;
            obj += s;
        } else {
            Professor p;
            str >> p;
            obj += p;
        }
        cout << endl;
    }

    return str;
}

// Displaying Person with given id
void Secretary::displayPerson(string id) {
    cout << *unidata.at(id);
}

// Searching if a Person with given id exists
bool Secretary::search(string id) {
    map<string, Person *>::iterator iter;
    iter = unidata.find(id);
    if (iter != unidata.end()) {
        return true;
    }

    return false;
}

// Inserting a Person in the map
bool Secretary::insert(const Person &person) {
    if (!search(person.id)) {
        // Allocating memory for new Person
        Person *p = allocatePerson(person);
        // Inserting the new Person to the unidata map
        unidata.insert(pair<string, Person *>(p->id, p));
        return true;
    }

    return false;
}

// Removing a Person (that exists) with given id
bool Secretary::remove(string id) {
    if (search(id)) {
        delete unidata[id];
        unidata.erase(id);
        return true;
    }

    return false;
}

// Unidata map size
int Secretary::count() {
    return unidata.size();
}