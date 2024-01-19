#include "../include/secretary.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Constructing Secretary
Secretary::Secretary() : department(""), departmentID(""), yearsOfStudy(0), graduationEcts(0) {
    currentYear = getCurrentYear();
    countProfessors = 0;
    countStudents.resize(currentYear + 1);
    for (long unsigned int i = 0; i < countStudents.size(); ++i) {
        countStudents[i] = 0;
    }
}

// Constructing Secretary using the parameters on the initializer list
Secretary::Secretary(string department, string departmentID, unsigned int yearsOfStudy, unsigned int graduationEcts) : department(department), departmentID(departmentID), yearsOfStudy(yearsOfStudy), graduationEcts(graduationEcts) {
    currentYear = getCurrentYear();
    countProfessors = 0;
    countStudents.resize(currentYear + 1);
    for (long unsigned int i = 0; i < countStudents.size(); ++i) {
        countStudents[i] = 0;
    }
}

// Destructing the dymically alocated memory of Person objects
Secretary::~Secretary() {
    map<string, Person *>::iterator iter;

    for (iter = unidata.begin(); iter != unidata.end(); ++iter)
        delete iter->second;
    unidata.clear();

    map<unsigned int, vector<Course *> >::iterator m_iter;

    for (m_iter = curriculum.begin(); m_iter != curriculum.end(); ++m_iter) {
        vector<Course *>::iterator c_iter;
        for (c_iter = m_iter->second.begin(); c_iter != m_iter->second.end(); ++c_iter)
            delete *c_iter;
        m_iter->second.clear();
    }

    curriculum.clear();
    countStudents.clear();
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

        map<unsigned int, vector<Course *> >::iterator m_iter;
        
        for (m_iter = curriculum.begin(); m_iter != curriculum.end(); ++m_iter) {
            vector<Course *>::iterator c_iter;
            for (c_iter = m_iter->second.begin(); c_iter != m_iter->second.end(); ++c_iter)
                delete *c_iter;
            m_iter->second.clear();
        }

        curriculum.clear();
        countStudents.clear();

        // Copying old_obj to the current Secretary instance
        map<string, Person *>::const_iterator const_iter;
        
        for (const_iter = old_obj.unidata.begin(); const_iter != old_obj.unidata.end(); ++const_iter) {
            Person *person = allocatePerson(*(const_iter->second));
            unidata.insert(pair<string, Person *>(person->getID(), person));
        }

        map<unsigned int, vector<Course *> >::const_iterator c_iter;
        vector<Course *>::const_iterator v_iter;
        for (c_iter = old_obj.curriculum.begin(); c_iter != old_obj.curriculum.end(); c_iter++) {
            for (v_iter = c_iter->second.begin(); v_iter != c_iter->second.end(); ++v_iter) {
                insertCourse(**v_iter);
            }
        }

        department = old_obj.department;
        departmentID = old_obj.departmentID;
        yearsOfStudy = old_obj.yearsOfStudy;
        currentYear = old_obj.currentYear;
        countProfessors = old_obj.countProfessors;
        graduationEcts = old_obj.graduationEcts;
        countStudents = old_obj.countStudents;
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

        map<unsigned int, vector<Course *> >::iterator m_iter;
        
        for (m_iter = curriculum.begin(); m_iter != curriculum.end(); ++m_iter) {
            vector<Course *>::iterator c_iter;
            for (c_iter = m_iter->second.begin(); c_iter != m_iter->second.end(); ++c_iter)
                delete *c_iter;
            m_iter->second.clear();
        }
        
        curriculum.clear();
        countStudents.clear();

        // Copying old_obj to the current Secretary instance
        map<string, Person *>::const_iterator const_iter;

        for (const_iter = old_obj.unidata.begin(); const_iter != old_obj.unidata.end(); ++const_iter) {
            Person *person = allocatePerson(*(const_iter->second));
            unidata.insert(pair<string, Person *>(person->getID(), person));
        }

        map<unsigned int, vector<Course *> >::const_iterator c_iter;

        vector<Course *>::const_iterator v_iter;
        for (c_iter = old_obj.curriculum.begin(); c_iter != old_obj.curriculum.end(); c_iter++) {
            for (v_iter = c_iter->second.begin(); v_iter != c_iter->second.end(); ++v_iter) {
                insertCourse(**v_iter);
            }
        }

        department = old_obj.department;
        departmentID = old_obj.departmentID;
        yearsOfStudy = old_obj.yearsOfStudy;
        currentYear = old_obj.currentYear;
        countProfessors = old_obj.countProfessors;
        graduationEcts = old_obj.graduationEcts;
        countStudents = old_obj.countStudents;
    }

    return *this;
}

// Overloading operator+= to add a new Person to the map
Secretary Secretary::operator+=(const Person &person) {
    if (person.getID().compare("0") == 0) {
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

    if (typeid(person) == typeid(Student))
        countStudents[dynamic_cast<const Student &>(person).getStartingYear()]++;
    else
        countProfessors++;
    return *this;
}

// Overloading operator-= to remove Person from the map
Secretary Secretary::operator-=(const Person &person) {
    // Searching if the Person exists in order to remove him/her
    if (search(person.getID())) {
        Person *p = unidata.at(person.getID());
        if (typeid(*p) == typeid(Student)) {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                for (long unsigned int i = 0; i < iter->second.size(); i++)
                    if (iter->second[i]->searchStudent(person.getID()))
                        iter->second[i]->removeStudent(person.getID());
            }
        } else {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                for (long unsigned int i = 0; i < iter->second.size(); i++)
                    if (iter->second[i]->searchProfessor(person.getID()))
                        iter->second[i]->removeProfessor(person.getID());
            }
        }
        delete unidata[person.getID()];
        unidata.erase(person.getID());
    }

    return *this;
}

// Passing Secretary data to the output stream (display)
ostream &operator<<(ostream &str, Secretary &obj) {
    str << endl;
    str << "Department " << obj.department << endl;
    str << endl;
    str << "Department ID: " << obj.departmentID << endl;
    str << "Years to complete " << obj.department << " :" << obj.yearsOfStudy << " years" << endl;
    str << "Graduation ECTS:" << obj.graduationEcts << endl;
    str << endl;

    str << "University Members:" << endl
        << endl;
    map<string, Person *>::iterator iter;
    int c = 0;
    for (iter = obj.unidata.begin(); iter != obj.unidata.end(); ++iter) {
        str << endl;
        str << "Member " << ++c << ":" << endl;
        str << *iter->second << endl;
    }

    str << "\nCurriculum:\n"
        << endl;
    map<unsigned int, vector<Course *> >::iterator m_iter;
    for (m_iter = obj.curriculum.begin(); m_iter != obj.curriculum.end(); ++m_iter) {
        vector<Course *>::iterator v_iter;
        str << "Semester " << m_iter->first << ":" << endl;
        for (v_iter = m_iter->second.begin(); v_iter != m_iter->second.end(); ++v_iter) {
            str << **v_iter << endl;
        }
        str << endl;
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
        cout << "Type 's' or 'S' to add a Student, else type 'p' or 'P' to add a Professor: ";
        do {
            str >> type;
            if (type != 's' && type != 'S' && type != 'p' && type != 'P')
                cout << "Invalid input, try again: ";
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
    for (unsigned int i = 1; i <= obj.yearsOfStudy * 2; i++) {
        cout << "How many courses the semester " << i << " has? ";
        int coursesOfSemester;
        str >> coursesOfSemester;
        cout << "Courses of semester " << i << ":" << endl;
        Course c;
        for (int j = 0; j < coursesOfSemester; j++) {
            str >> c;
        }
    }

    return str;
}

// Displaying Person with given id
void Secretary::display(const string &id) const {
    if (!search(id)) {
        cout << "Non existing ID.";
        return;
    }

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
string Secretary::insert(const Person &person) {
    if (person.getID().compare("0") == 0) {
        // Allocating memory for new Person
        Person *p = allocatePerson(person);
        // Generating ID for the new Person
        p->setID(generateID(*p));
        // Inserting the new Person to the unidata map
        unidata.insert(pair<string, Person *>(p->getID(), p));
        if (typeid(person) == typeid(Student))
            countStudents[dynamic_cast<const Student &>(person).getStartingYear()]++;
        else
            countProfessors++;
        return p->getID();
    } else {
        if (!search(person.getID())) {
            // Allocating memory for new Person
            Person *p = allocatePerson(person);
            // Inserting the new Person to the unidata map
            unidata.insert(pair<string, Person *>(p->getID(), p));
            if (typeid(person) == typeid(Student))
                countStudents[dynamic_cast<const Student &>(person).getStartingYear()]++;
            else
                countProfessors++;
            return p->getID();
        }
        if (typeid(person) == typeid(Student))
            countStudents[dynamic_cast<const Student &>(person).getStartingYear()]++;
        else
            countProfessors++;
    }

    return "";
}

// Removing a Person (that exists) with given id
bool Secretary::remove(const string &id) {
    if (search(id)) {
        Person *p = unidata.at(id);
        if (typeid(*p) == typeid(Student)) {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                vector<Course *>::iterator c_iter;
                for (c_iter = iter->second.begin(); c_iter != iter->second.end(); ++c_iter)
                    if ((*c_iter)->searchStudent(id))
                        (*c_iter)->removeStudent(id);
            }
        } else {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                vector<Course *>::iterator c_iter;
                for (c_iter = iter->second.begin(); c_iter != iter->second.end(); ++c_iter)
                    if ((*c_iter)->searchProfessor(id))
                        (*c_iter)->removeProfessor(id);
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
    map<unsigned int, vector<Course *> >::const_iterator const_iter;
    for (const_iter = curriculum.begin(); const_iter != curriculum.end(); ++const_iter) {
        for (long unsigned int i = 0; i < const_iter->second.size(); i++) {
            if (const_iter->second[i]->getName().compare(courseName) == 0) {
                const_iter->second[i]->display();
                return;
            }
        }
    }
    cout << "Course not found." << endl;
}

// Seacrhing a Course with given name
bool Secretary::searchCourse(const string &courseName) const {
    map<unsigned int, vector<Course *> >::const_iterator const_iter;
    for (const_iter = curriculum.begin(); const_iter != curriculum.end(); ++const_iter) {
        for (long unsigned int i = 0; i < const_iter->second.size(); i++)
            if (const_iter->second[i]->getName().compare(courseName) == 0)
                return true;
    }
    return false;
}

// Inserting a Course in the curriculum
bool Secretary::insertCourse(const Course &course) {
    if (!searchCourse(course.getName())) {
        map<unsigned int, vector<Course *> >::iterator iter;
        iter = curriculum.find(course.getSemester());
        if (iter == curriculum.end()) {
            vector<Course *> courseV;
            curriculum.insert(pair<unsigned int, vector<Course *> >(course.getSemester(), courseV));
        }
        Course *c;
        try {
            c = new Course(course);
        } catch (bad_alloc &ba) {
            cerr << "bad_alloc caught: " << ba.what() << endl;
            exit(EXIT_FAILURE);
        }
        curriculum.at(course.getSemester()).push_back(c);
        return true;
    }
    return false;
}

// Removing a Course from the Curriculum
bool Secretary::removeCourse(const string &courseName) {
    map<unsigned int, vector<Course *> >::iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        vector<Course *>::iterator c_iter;
        for (c_iter = iter->second.begin(); c_iter != iter->second.end(); ++c_iter) {
            if ((*c_iter)->getName().compare(courseName) == 0) {
                map<string, Person *>::iterator p_iter;
                for (p_iter = unidata.begin(); p_iter != unidata.end(); ++p_iter) {
                    Person *p = p_iter->second;
                    if (typeid(*p) == typeid(Student)) {
                        if (dynamic_cast<Student *>(p_iter->second)->searchCourse(courseName))
                            dynamic_cast<Student *>(p_iter->second)->removeCourse(courseName);
                    } else {
                        if (dynamic_cast<Professor *>(p_iter->second)->searchCourse(courseName))
                            dynamic_cast<Professor *>(p_iter->second)->removeCourse(courseName);
                    }
                }
                delete *c_iter;
                iter->second.erase(c_iter);
                return true;
            }
        }
    }
    return false;
}

// Transfer a Course to a new semester
bool Secretary::transferCourse(const string &courseName, unsigned int newSemester) {
    map<unsigned int, vector<Course *> >::iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        vector<Course *>::iterator c_iter;
        for (c_iter = iter->second.begin(); c_iter != iter->second.end(); ++c_iter) {
            if ((*c_iter)->getName().compare(courseName) == 0) {
                Course *temp = *c_iter;
                iter->second.erase(c_iter);
                curriculum.at(newSemester).push_back(temp);
                temp->setSemester(newSemester);
                return true;
            }
        }
    }
    return false;
}

// Registering a Student to a Course
bool Secretary::registerStudentToCourse(const string &courseName, const string &id) {
    if (search(id)) {
        Person *p = unidata.at(id);
        if (typeid(*p) == typeid(Student)) {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                for (long unsigned int i = 0; i < iter->second.size(); i++) {
                    if (iter->second[i]->getName().compare(courseName) == 0) {
                        if (dynamic_cast<Student *>(unidata.at(id))->getSemester() < iter->second[i]->getSemester())
                            return false;
                        Student *s = dynamic_cast<Student *>(unidata.at(id));
                        iter->second[i]->insertStudent(s);
                        s->insertCourse(iter->second[i]);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Assigning a Course to a Professor
bool Secretary::assignCourseToProfessor(const string &courseName, const string &id) {
    if (search(id)) {
        Person *p = unidata.at(id);
        if (typeid(*p) == typeid(Professor)) {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                for (long unsigned int i = 0; i < iter->second.size(); i++) {
                    if (iter->second[i]->getName().compare(courseName) == 0) {
                        iter->second[i]->insertProfessor(dynamic_cast<Professor *>(unidata.at(id)));
                        dynamic_cast<Professor *>(unidata.at(id))->insertCourse(iter->second[i]);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Unregistering a Student from a Course
bool Secretary::unregisterStudentFromCourse(const string &courseName, const string &id) {
    if (search(id)) {
        Person *p = unidata.at(id);
        if (typeid(*p) == typeid(Student)) {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                for (long unsigned int i = 0; i < iter->second.size(); i++) {
                    if (iter->second[i]->getName().compare(courseName) == 0) {
                        iter->second[i]->unregisterStudent(id);
                        dynamic_cast<Student *>(unidata.at(id))->unregisterCourse(courseName);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Unassigning a Course from a Professor
bool Secretary::unassignCourseFromProfessor(const string &courseName, const string &id) {
    if (search(id)) {
        Person *p = unidata.at(id);
        if (typeid(*p) == typeid(Professor)) {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                for (long unsigned int i = 0; i < iter->second.size(); i++) {
                    if (iter->second[i]->getName().compare(courseName) == 0) {
                        iter->second[i]->removeProfessor(id);
                        dynamic_cast<Professor *>(unidata.at(id))->removeCourse(courseName);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Assigning grades to all the Students of a Course
void Secretary::assignGrades(const string &courseName, const string &id) {
    map<string, double> grades;
    bool flag = false;
    if (search(id)) {
        Person *p = unidata.at(id);
        if (typeid(*p) == typeid(Professor)) {
            map<unsigned int, vector<Course *> >::iterator iter;
            for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                for (long unsigned int i = 0; i < iter->second.size(); i++) {
                    if (iter->second[i]->getName().compare(courseName) == 0) {
                        flag = true;
                        grades = iter->second[i]->getGrades();
                        map<string, double>::iterator g_iter;
                        cout << "Input grades for course " << iter->second[i]->getName() << endl;
                        for (g_iter = grades.begin(); g_iter != grades.end(); ++g_iter) {
                            if (iter->second[i]->searchStudent(g_iter->first)) {
                                do {
                                    cout << g_iter->first << ": ";
                                    cin >> g_iter->second;
                                    if (g_iter->second < 0 || g_iter->second > 10)
                                        cout << "Invalid input" << endl;
                                } while (g_iter->second < 0 || g_iter->second > 10);
                                iter->second[i]->setGrades(grades);
                                if (g_iter->second >= 5)
                                    dynamic_cast<Student *>(unidata.at(g_iter->first))->insertPassedCourse(iter->second[i]);
                            }
                        }
                        cout << "Grades for Course " << courseName << " assigned successfully.\n";
                    }
                }
            }
            if (!flag)
                cout << "Could not find Course " << courseName << endl;
        } else
            cout << "Not allowed to set grades as a student." << endl;
    } else
        cout << "Non existing ID given." << endl;
}

// Display and Save Students who passed a certain Course
void Secretary::displaySaveStudentsWhoPassedCourse(const string &courseName) {
    map<unsigned int, vector<Course *> >::iterator iter;

    string filename = courseName + ".txt";
    ofstream outputFile;

    try {
        outputFile.open(filename);
        if (!outputFile.is_open())
            throw(0);
    } catch (...) {
        cerr << "Error opening output file for course " << courseName << "." << endl;
        exit(EXIT_FAILURE);
    }

    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        for (long unsigned int i = 0; i < iter->second.size(); i++) {
            if (iter->second[i]->getName().compare(courseName) == 0) {
                map<string, double>::iterator g_iter;
                map<string, double> grades = iter->second[i]->getGrades();
                for (g_iter = grades.begin(); g_iter != grades.end(); ++g_iter) {
                    if (g_iter->second >= 5.0) {
                        cout << "Student " << getFname(g_iter->first) << " " << getLname(g_iter->first) << " passed " << courseName << " with grade " << g_iter->second << endl;
                        outputFile << "Student " << getFname(g_iter->first) << " " << getLname(g_iter->first) << " passed " << courseName << " with grade " << g_iter->second << endl;
                    }
                }
            }
        }
    }
    outputFile.close();
    cout << "Students who passed, were saved to the file " << filename << endl;
}

// Function that checks if a student graduates
bool Secretary::graduates(const string &id) {
    if (!search(id))
        return false;

    Person *p = unidata.at(id);
    if (typeid(*p) == typeid(Professor))
        return false;

    int mandatory = 0;
    map<unsigned int, vector<Course *> >::iterator iter;
    vector<Course *>::iterator c_iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        for (c_iter = iter->second.begin(); c_iter != iter->second.end(); ++c_iter) {
            if ((*c_iter)->getCourseType().compare("Mandatory") == 0)
                mandatory++;
        }
    }

    if (!dynamic_cast<Student *>(unidata.at(id))->mandatorypassed(mandatory))
        return false;

    if (dynamic_cast<Student *>(unidata.at(id))->getEcts() >= graduationEcts)
        return true;

    return false;
}

// Function that displays all students that graduate
void Secretary::displayGraduates() {
    map<string, Person *>::iterator iter;
    for (iter = unidata.begin(); iter != unidata.end(); ++iter) {
        if (graduates(iter->first)) {
            cout << *dynamic_cast<Student *>(iter->second) << endl;
        }
    }
}

// Function that displays statistics for a professor's courses
void Secretary::displayStatistics(const string &id) {
    if (!search(id))
        return;

    Person *p = unidata.at(id);
    if (typeid(Professor) == typeid(*p))
        dynamic_cast<Professor *>(unidata.at(id))->displayStatistics();
}

// Function that displays a student's grades
void Secretary::displayGrades(const string &id) {
    if (!search(id))
        return;

    Person *p = unidata.at(id);
    if (typeid(Student) == typeid(*p))
        dynamic_cast<Student *>(unidata.at(id))->displayGrades();
}

// Function that parses input info and inserts it to the Secretary
void Secretary::parseInput(const string &path) {
    ifstream database;

    try {
        database.open(path);
        if (!database.is_open())
            throw(0);
    } catch (...) {
        cerr << "Error opening input file." << endl;
        exit(EXIT_FAILURE);
    }

    string line, id;
    if (getline(database, line)) {
        vector<string> dataList;
        string token;
        stringstream str(line);

        while (getline(str, token, ' '))
            dataList.push_back(token);

        if (dataList.size() != 5) {
            cerr << "Error invalid input of Secretary in file." << endl;
            exit(EXIT_FAILURE);
        }

        if (dataList[0].compare("Secretary") == 0) {
            department = dataList[1];
            departmentID = dataList[2];
            yearsOfStudy = stoi(dataList[3]);
            graduationEcts = stoi(dataList[4]);
        } else {
            cerr << "Error invalid input of Secretary in file." << endl;
            exit(EXIT_FAILURE);
        }
    }

    while (getline(database, line)) {
        vector<string> dataList;
        string token;
        stringstream str(line);

        while (getline(str, token, ' '))
            dataList.push_back(token);

        if (dataList[0].compare("Student") == 0) {
            if (dataList.size() < 15) {
                cerr << "Error invalid input of Student in file." << endl;
                exit(EXIT_FAILURE);
            }

            unsigned int day = stoi(dataList[3]);
            unsigned int month = stoi(dataList[4]);
            unsigned int year = stoi(dataList[5]);
            char gender = dataList[6].at(0);
            int semester = stoi(dataList[11]);
            int ects = stoi(dataList[12]);
            double gpa = stod(dataList[13]);
            int memberSince = stoi(dataList[14]);
            try {
                if (semester <= 0 || ects < 0 || gpa < 0 || memberSince < 0)
                    throw(0);
            } catch (...) {
                cerr << "Error invalid input of Student in file." << endl;
                exit(EXIT_FAILURE);
            }

            Student s = Student(dataList[1], dataList[2], day, month, year, gender, dataList[7], dataList[8], dataList[9], dataList[10], semester, ects, gpa, memberSince);
            id = insert(s);
            for (long unsigned int i = 15; i < dataList.size(); i += 2) {
                if (!searchCourse(dataList[i])) {
                    cerr << "Error course not found in Secretary." << endl;
                    exit(EXIT_FAILURE);
                }

                if (i + 1 >= dataList.size()) {
                    cerr << "Error invalid input of grade in file." << endl;
                    exit(EXIT_FAILURE);
                }

                double grade = stod(dataList[i + 1]);

                if (grade < 0 || grade > 10) {
                    cerr << "Error invalid input of grade in file." << endl;
                    exit(EXIT_FAILURE);
                }

                if (grade >= 5) {
                    registerStudentToCourse(dataList[i], id);
                    map<unsigned int, vector<Course *> >::iterator iter;
                    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
                        vector<Course *>::iterator c_iter;
                        for (c_iter = iter->second.begin(); c_iter != iter->second.end(); ++c_iter) {
                            if ((*c_iter)->getName().compare(dataList[i]) == 0) {
                                map<string, double> grades = (*c_iter)->getGrades();
                                grades.at(id) = grade;
                                (*c_iter)->setGrades(grades);
                                dynamic_cast<Student *>(unidata.at(id))->insertPassedCourse(*c_iter);
                            }
                        }
                    }
                    unregisterStudentFromCourse(dataList[i], id);
                }
            }
        } else if (dataList[0].compare("Professor") == 0) {
            if (dataList.size() < 14) {
                cerr << "Error invalid input of Professor in file." << endl;
                exit(EXIT_FAILURE);
            }

            unsigned int day = stoi(dataList[3]);
            unsigned int month = stoi(dataList[4]);
            unsigned int year = stoi(dataList[5]);
            char gender = dataList[6].at(0);
            Professor p = Professor(dataList[1], dataList[2], day, month, year, gender, dataList[7], dataList[8], dataList[9], dataList[10], dataList[11], dataList[12], dataList[13]);
            id = insert(p);
            for (long unsigned int i = 14; i < dataList.size(); ++i) {
                if (!searchCourse(dataList[i])) {
                    cerr << "Error course not found in Secretary." << dataList[2] << endl;
                    exit(EXIT_FAILURE);
                }
                assignCourseToProfessor(dataList[i], id);
            }
        } else if (dataList[0].compare("Course") == 0) {
            if (dataList.size() != 5) {
                cerr << "Error invalid input of Course in file." << endl;
                exit(EXIT_FAILURE);
            }

            int semester = stoi(dataList[2]);
            int ects = stoi(dataList[3]);
            bool mandatory;

            try {
                if (semester <= 0 || semester > static_cast<int>(yearsOfStudy) * 2 || ects < 0)
                    throw(0);
            } catch (...) {
                cerr << "Error invalid input of Course in file." << endl;
                exit(EXIT_FAILURE);
            }

            if (dataList[4].compare("Mandatory") == 0) {
                mandatory = true;
            } else if (dataList[4].compare("Optional") == 0) {
                mandatory = false;
            } else {
                cerr << "Error invalid input of Course in file." << endl;
                exit(EXIT_FAILURE);
            }

            Course c = Course(dataList[1], semester, ects, mandatory);
            insertCourse(c);
        } else {
            cerr << "Error invalid input in file." << endl;
            exit(EXIT_FAILURE);
        }
        dataList.clear();
    }
    database.close();
}

// Function that updates the input file based on the changes user made
void Secretary::updateFile(const string &path) {
    ofstream outputFile;

    try {
        outputFile.open(path);
        if (!outputFile.is_open())
            throw(0);
    } catch (...) {
        cerr << "Error opening file for updating." << endl;
        exit(EXIT_FAILURE);
    }

    outputFile << "Secretary " << department << " " << departmentID << " " << to_string(yearsOfStudy) << " " << to_string(graduationEcts) << endl;

    map<unsigned int, vector<Course *> >::iterator c_iter;
    for (c_iter = curriculum.begin(); c_iter != curriculum.end(); ++c_iter) {
        for (long unsigned int i = 0; i < c_iter->second.size(); ++i) {
            string str = "Course " + c_iter->second[i]->getName() + " " + to_string(c_iter->second[i]->getSemester()) + " " + to_string(c_iter->second[i]->getEcts()) + " " + c_iter->second[i]->getCourseType() + "\n";
            outputFile << str;
        }
    }

    map<string, Person *>::iterator iter;
    vector<Course *> courses;
    for (iter = unidata.begin(); iter != unidata.end(); ++iter) {
        Person *p = iter->second;
        if (typeid(*p) == typeid(Student)) {
            map<string, double> grades;
            string str = "Student " + iter->second->getFname() + " " + iter->second->getLname() + " " + iter->second->getBirthDate() + " " + iter->second->getGender() + " " + iter->second->getNationality() + " " + iter->second->getEmail() + " " + iter->second->getPhone() + " " + iter->second->getID() + " " + to_string(dynamic_cast<Student *>(iter->second)->getSemester()) + " " + to_string(dynamic_cast<Student *>(iter->second)->getEcts()) + " " + to_string(dynamic_cast<Student *>(iter->second)->getGpa()) + " " + to_string(dynamic_cast<Student *>(iter->second)->getStartingYear());
            courses = dynamic_cast<Student *>(iter->second)->getPassedCourses();
            for (long unsigned int i = 0; i < courses.size(); ++i) {
                str += " ";
                str += courses[i]->getName();
                str += " ";
                grades = courses[i]->getGrades();
                str += to_string(grades.at(iter->second->getID()));
            }
            outputFile << str << endl;
        } else {
            string str = "Professor " + iter->second->getFname() + " " + iter->second->getLname() + " " + iter->second->getBirthDate() + " " + iter->second->getGender() + " " + iter->second->getNationality() + " " + iter->second->getEmail() + " " + iter->second->getPhone() + " " + iter->second->getID() + " " + dynamic_cast<Professor *>(iter->second)->getTrait() + " " + dynamic_cast<Professor *>(iter->second)->getRank() + " " + dynamic_cast<Professor *>(iter->second)->getOfficeNo();
            courses = dynamic_cast<Professor *>(iter->second)->getCourses();
            for (long unsigned int i = 0; i < courses.size(); ++i) {
                str += " ";
                str += courses[i]->getName();
            }
            outputFile << str << endl;
        }
    }

    outputFile.close();
}

// Getting current year
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

// Generating ID for Persons
string Secretary::generateID(const Person &person) {
    if (typeid(person) == typeid(Student)) {
        unsigned int c = countStudents[dynamic_cast<const Student &>(person).getStartingYear()];
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
        unsigned int c = countProfessors;
        if (c < 10)
            return departmentID + "00" + to_string(c);
        else if (c < 100)
            return departmentID + "0" + to_string(c);
        else
            return departmentID + to_string(c);
    }
}

unsigned int Secretary::getCourseEcts(const string &courseName) const {
    map<unsigned int, vector<Course *> >::const_iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        vector<Course *> course = iter->second;
        for (long unsigned int i = 0; i < course.size(); i++) {
            if (course[i]->getName().compare(courseName) == 0)
                return course[i]->getEcts();
        }
    }
    cerr << "Non existing Course name." << endl;
    return 0;
}

unsigned int Secretary::getCourseSemester(const string &courseName) const {
    map<unsigned int, vector<Course *> >::const_iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        vector<Course *> course = iter->second;
        for (long unsigned int i = 0; i < course.size(); i++) {
            if (course[i]->getName().compare(courseName) == 0)
                return course[i]->getSemester();
        }
    }
    cerr << "Non existing Course name." << endl;
    return 0;
}

string Secretary::getCourseType(const string &courseName) const {
    map<unsigned int, vector<Course *> >::const_iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        vector<Course *> course = iter->second;
        for (long unsigned int i = 0; i < course.size(); i++) {
            if (course[i]->getName().compare(courseName) == 0)
                return course[i]->getCourseType();
        }
    }
    cerr << "Non existing Course name." << endl;
    return "";
}

void Secretary::setCourseName(const string &courseName, const string &newCourseName) {
    map<unsigned int, vector<Course *> >::const_iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        for (long unsigned int i = 0; i < iter->second.size(); i++) {
            if (iter->second[i]->getName().compare(courseName) == 0)
                iter->second[i]->setName(newCourseName);
        }
    }
    cerr << "Non existing Course name." << endl;
}

void Secretary::setCourseEcts(const string &courseName, unsigned int newEcts) {
    map<unsigned int, vector<Course *> >::const_iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        for (long unsigned int i = 0; i < iter->second.size(); i++) {
            if (iter->second[i]->getName().compare(courseName) == 0)
                iter->second[i]->setEcts(newEcts);
        }
    }
    cerr << "Non existing Course name." << endl;
}

void Secretary::setCourseSemester(const string &courseName, unsigned int newSemester) {
    map<unsigned int, vector<Course *> >::const_iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        for (long unsigned int i = 0; i < iter->second.size(); i++) {
            if (iter->second[i]->getName().compare(courseName) == 0)
                iter->second[i]->setSemester(newSemester);
        }
    }
    cerr << "Non existing Course name." << endl;
}

void Secretary::setCourseType(const string &courseName, bool newCourseType) {
    map<unsigned int, vector<Course *> >::const_iterator iter;
    for (iter = curriculum.begin(); iter != curriculum.end(); ++iter) {
        for (long unsigned int i = 0; i < iter->second.size(); i++) {
            if (iter->second[i]->getName().compare(courseName) == 0)
                iter->second[i]->setEcts(newCourseType);
        }
    }
    cerr << "Non existing Course name." << endl;
}