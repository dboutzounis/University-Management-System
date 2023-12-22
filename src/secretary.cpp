#include "../include/secretary.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

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

    cout << "Curriculum input: " << endl;
    for (int i = 1; i <= obj.yearsOfStudy * 2; i++) {
        cout << "How many courses the Semester " << i << " has? ";
        int coursesOfSemester;
        str >> coursesOfSemester;
        cout << "Courses of Semester " << i << ":" << endl;
        Course c;
        for (int j = 0; j < coursesOfSemester; j++) {
            str >> c;
        }
    }

    return str;
}

// Displaying Person with given id
void Secretary::display(const string &id) const {
    cout << *unidata.at(id);
}

// Searching if a Person with given id exists
bool Secretary::search(const string &id) const {
    map<string, Person *>::const_iterator const_iter;
    const_iter = unidata.find(id);
    if (const_iter != unidata.end()) {
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
bool Secretary::remove(const string &id) {
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

// Displaying a Course with given name
void Secretary::displayCourse(const string &courseName) const {
    map<int, vector<Course *>>::const_iterator const_iter;
    for (const_iter = curriculum.begin(); const_iter != curriculum.end(); ++const_iter) {
        vector<Course *> course = const_iter->second;
        for (int i = 0; i < course.size(); i++) {
            if (course[i]->name.compare(courseName) == 0) {
                cout << course[i];
                return;
            }
        }
    }
    cout << "Course not found." << endl;
}

// Seacrhing a Course with given name
bool Secretary::searchCourse(const string &courseName) const {
    map<int, vector<Course *>>::const_iterator const_iter;
    for (const_iter = curriculum.begin(); const_iter != curriculum.end(); ++const_iter) {
        vector<Course *> course = const_iter->second;
        for (int i = 0; i < course.size(); i++) {
            if (course[i]->name.compare(courseName) == 0)
                return true;
        }
    }
    return false;
}

// Inserting a Course in the curriculum
bool Secretary::insertCourse(const Course &course) {
    if (!searchCourse(course.name)) {
        Course *c = new Course(course);
        curriculum.at(course.semester).push_back(c);
        return true;
    }
    return false;
}

bool Secretary::removeCourse(const string &courseName) {
    if (searchCourse(courseName)) {
        Course *c;
        map<int, vector<Course *>>::iterator iter;
        for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
            vector<Course *> course = iter->second;
            vector<Course *>::iterator i;
            for (i = course.begin(); i != course.end(); i++) {
                if ((*i)->name.compare(courseName) == 0) {
                    c = *i;
                    course.erase(i);
                }
            }
        }
    }
    return false;
}