#include "../include/secretary.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Constructing Secretary
Secretary::Secretary() : department(""), departmentID(""), yearsOfStudy(0) {
    currentYear = getCurrentYear();
    countProfessors = 0;
    countStudents = new unsigned int[currentYear + 1];

    for (int i = 0; i <= currentYear; ++i) {
        countStudents[i] = 0;
    }
}

// Constructing Secretary using the parameters on the initializer list
Secretary::Secretary(string department, string departmentID, unsigned int yearsOfStudy) : department(department), departmentID(departmentID), yearsOfStudy(yearsOfStudy) {
    currentYear = getCurrentYear();
    countProfessors = 0;
    countStudents = new unsigned int[currentYear + 1];

    for (int i = 0; i <= currentYear; ++i) {
        countStudents[i] = 0;
    }
}

// Destructing the dymically alocated memory of Person objects
Secretary::~Secretary() {
    map<string, Person *>::iterator iter;

    for (iter = unidata.begin(); iter != unidata.end(); ++iter)
        delete iter->second;
    unidata.clear();

    delete[] countStudents;
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

        delete[] countStudents;

        // Copying old_obj to the current Secretary instance
        map<string, Person *>::const_iterator const_iter;
        for (const_iter = old_obj.unidata.begin(); const_iter != old_obj.unidata.end(); ++const_iter) {
            Person *person = allocatePerson(*(const_iter->second));
            unidata.insert(pair<string, Person *>(person->getID(), person));
        }

        department = old_obj.department;
        departmentID = old_obj.departmentID;
        yearsOfStudy = old_obj.yearsOfStudy;
        currentYear = old_obj.currentYear;
        countProfessors = old_obj.countProfessors;

        countStudents = new unsigned int[currentYear + 1];

        for (int i = 0; i <= currentYear; ++i) {
            countStudents[i] = old_obj.countStudents[i];
        }
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

        delete[] countStudents;

        // Copying old_obj to the current Secretary instance
        map<string, Person *>::const_iterator const_iter;
        for (const_iter = old_obj.unidata.begin(); const_iter != old_obj.unidata.end(); ++const_iter) {
            Person *person = allocatePerson(*(const_iter->second));
            unidata.insert(pair<string, Person *>(person->getID(), person));
        }

        department = old_obj.department;
        departmentID = old_obj.departmentID;
        yearsOfStudy = old_obj.yearsOfStudy;
        currentYear = old_obj.currentYear;
        countProfessors = old_obj.countProfessors;

        countStudents = new unsigned int[currentYear + 1];

        for (int i = 0; i <= currentYear; ++i) {
            countStudents[i] = old_obj.countStudents[i];
        }
    }

    return *this;
}

// Overloading operator+= to add a new Person to the map
Secretary Secretary::operator+=(const Person &person) {
    if (person.getID().compare("") == 0) {
        // Allocating memory for new Person
        Person *p = allocatePerson(person);
        // Generating ID for the new Person
        p->setID(generateID(*p));
        // Inserting the new Person to the unidata map
        unidata.insert(pair<string, Person *>(p->getID(), p));
    } else {
        if (!search(person.getID())) {
            // Allocating memory for new Person
            Person *p = allocatePerson(person);
            // Inserting the new Person to the unidata map
            unidata.insert(pair<string, Person *>(p->getID(), p));
        }
    }

    return *this;
}

// Overloading operator-= to remove Person from the map
Secretary Secretary::operator-=(const Person &person) {
    // Searching if the Person exists in order to remove him/her
    if (search(person.getID())) {
        delete unidata[person.getID()];
        unidata.erase(person.getID());
    }

    return *this;
}

// Passing Secretary data to the output stream (display)
ostream &operator<<(ostream &str, Secretary &obj) {
    str << endl;
    str << "Department " << obj.department << " data:" << endl;
    str << endl;
    str << "Department ID: " << obj.departmentID << endl;
    str << "Years to complete " << obj.department << " :" << obj.yearsOfStudy << " years" << endl;
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
    if (const_iter != unidata.end())
        return true;

    return false;
}

// Inserting a Person in the map
bool Secretary::insert(const Person &person) {
    if (person.getID().compare("") == 0) {
        // Allocating memory for new Person
        Person *p = allocatePerson(person);
        // Generating ID for the new Person
        p->setID(generateID(*p));
        // Inserting the new Person to the unidata map
        unidata.insert(pair<string, Person *>(p->getID(), p));
        return true;
    } else {
        if (!search(person.getID())) {
            // Allocating memory for new Person
            Person *p = allocatePerson(person);
            // Inserting the new Person to the unidata map
            unidata.insert(pair<string, Person *>(p->getID(), p));
            return true;
        }
    }

    return false;
}

// Removing a Person (that exists) with given id
bool Secretary::remove(const string &id) {
    if (search(id)) {
        if (typeid(unidata.at(id)) == typeid(Student)) {
            map<unsigned int, vector<Course *>>::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                vector<Course *> course = iter->second;
                for (int i = 0; i < course.size(); i++)
                    if (course[i]->searchStudent(id))
                        course[i]->removeStudent(id);
            }
        } else {
            map<unsigned int, vector<Course *>>::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                vector<Course *> course = iter->second;
                for (int i = 0; i < course.size(); i++)
                    if (course[i]->searchProfessor(id))
                        course[i]->removeProfessor(id);
            }
        }
        delete unidata[id];
        unidata.erase(id);
        return true;
    }
    return false;
}

// Unidata map size
int Secretary::size() {
    return unidata.size();
}

// Displaying a Course with given name
void Secretary::displayCourse(const string &courseName) const {
    map<unsigned int, vector<Course *>>::const_iterator const_iter;
    for (const_iter = curriculum.begin(); const_iter != curriculum.end(); ++const_iter) {
        vector<Course *> course = const_iter->second;
        for (int i = 0; i < course.size(); i++) {
            if (course[i]->getName().compare(courseName) == 0) {
                course[i]->display();
                return;
            }
        }
    }
    cout << "Course not found." << endl;
}

// Seacrhing a Course with given name
bool Secretary::searchCourse(const string &courseName) const {
    map<unsigned int, vector<Course *>>::const_iterator const_iter;
    for (const_iter = curriculum.begin(); const_iter != curriculum.end(); ++const_iter) {
        vector<Course *> course = const_iter->second;
        for (int i = 0; i < course.size(); i++)
            if (course[i]->getName().compare(courseName) == 0)
                return true;
    }
    return false;
}

// Inserting a Course in the curriculum
bool Secretary::insertCourse(const Course &course) {
    if (!searchCourse(course.getName())) {
        Course *c = new Course(course);
        curriculum.at(course.getSemester()).push_back(c);
        return true;
    }
    return false;
}

// Removing a Course from the Curriculum
bool Secretary::removeCourse(const string &courseName) {
    map<unsigned int, vector<Course *>>::iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        vector<Course *> courses = iter->second;
        vector<Course *>::iterator c_iter;
        for (c_iter = courses.begin(); c_iter != courses.end(); ++c_iter) {
            if ((*c_iter)->getName().compare(courseName) == 0) {
                map<string, Person *>::iterator p_iter;
                for (p_iter = unidata.begin(); p_iter != unidata.end(); ++p_iter) {
                    if (typeid(p_iter->second) == typeid(Student)) {
                        if (dynamic_cast<Student *>(p_iter->second)->searchCourse(courseName))
                            dynamic_cast<Student *>(p_iter->second)->removeCourse(courseName);
                    } else {
                        if (dynamic_cast<Professor *>(p_iter->second)->searchCourse(courseName))
                            dynamic_cast<Professor *>(p_iter->second)->removeCourse(courseName);
                    }
                }
                delete *c_iter;
                courses.erase(c_iter);
                return true;
            }
        }
    }
    return false;
}

unsigned int Secretary::getCurrentYear() {
    // Get the current time
    chrono::system_clock::time_point currentTime = chrono::system_clock::now();

    // Convert the time to a time_point representing the local time
    time_t localTime = chrono::system_clock::to_time_t(currentTime);

    // Extract the current year using put_time
    tm *tm = localtime(&localTime);
    unsigned int currentYear = tm->tm_year + 1900;

    return currentYear;
}

string Secretary::generateID(const Person &person) {
    if (typeid(person) == typeid(Student)) {
        int c = countStudents[dynamic_cast<const Student &>(person).getStartingYear()];
        if (c < 10)
            return departmentID + to_string(dynamic_cast<const Student &>(person).getStartingYear()) + "0000" + to_string(c);
        else if (c < 100)
            return departmentID + to_string(dynamic_cast<const Student &>(person).getStartingYear()) + "000" + to_string(c);
        else if (c < 1000)
            return departmentID + to_string(dynamic_cast<const Student &>(person).getStartingYear()) + "00" + to_string(c);
        else if (c < 10000)
            return departmentID + to_string(dynamic_cast<const Student &>(person).getStartingYear()) + "0" + to_string(c);
        else
            return departmentID + to_string(dynamic_cast<const Student &>(person).getStartingYear()) + to_string(c);
    } else {
        int c = countProfessors;
        if (c < 10)
            return departmentID + "00" + to_string(c);
        else if (c < 100)
            return departmentID + "0" + to_string(c);
        else
            return departmentID + to_string(c);
    }
}