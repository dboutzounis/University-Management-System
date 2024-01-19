#include "../include/secretary.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    try {
        if (argc != 2)
            throw(1);
    } catch (int n) {
        cerr << "Usage: ./main <input-file>" << endl;
        exit(EXIT_FAILURE);
    }

    Secretary secretary;
    Professor professor;
    Student student;
    Course course;
    unsigned int mode, submode, edit_mode, day, month, year, semester, ects;
    string id, str;
    char ch;

    secretary.parseInput(argv[1]);

    cout << setprecision(3) << "---------- WELCOME TO THE SECRETARY OF " << secretary.getDepartment() << "! ----------" << endl;

    while (true) {
        // Displaying the available secretary options
        cout << endl;
        cout << "----- SECRETARY MENU -----" << endl;
        cout << "0.Exit" << endl;
        cout << "1.Insert/Modify/Remove Professor" << endl;
        cout << "2.Insert/Modify/Remove Student" << endl;
        cout << "3.Insert/Modify/Remove Course" << endl;
        cout << "4.Assign Course to Professor" << endl;
        cout << "5.Register Student to Course" << endl;
        cout << "6.Display and Save the Students who Passed a Particular Course in a Semester " << endl;
        cout << "7.Display Professor Statistics" << endl;
        cout << "8.Display Student Statistics" << endl;
        cout << "9.Display Students who Graduate" << endl;
        cout << "10.Assign Grades for a particular Course" << endl;
        cout << "11.Unregister a Student from a Course" << endl;
        cout << "12.Unassign course from a Professor" << endl;
        cout << "13.Secretary Display" << endl;

        // Checking if user gave valid input
        do {
            cout << "> Enter mode: ";
            cin >> mode;
            if (mode < 0 || mode > 13)
                cout << "Invalid input, try again." << endl;
        } while (mode < 0 || mode > 13);

        switch (mode) {
        case 1:
            cout << "Available actions for Professor:" << endl;
            cout << "0.Back" << endl;
            cout << "1.Insert Professor" << endl;
            cout << "2.Modify Professor" << endl;
            cout << "3.Remove Professor" << endl;

            do {
                cout << "> Enter mode: ";
                cin >> submode;
                if (submode < 0 || submode > 3)
                    cout << "Invalid input, try again." << endl;
            } while (submode < 0 || submode > 3);

            switch (submode) {
            case 1:
                cin >> professor;
                id = secretary.insert(professor);
                if (id.compare("") != 0)
                    cout << "Professor " << professor.getFname() << " " << professor.getLname() << " was inserted successfully with ID " << id << "." << endl;
                else
                    cout << "Professor " << professor.getFname() << " " << professor.getLname() << " could not be inserted." << endl;
                break;

            case 2:
                cout << "What do you want to edit?" << endl;
                cout << "0.Back" << endl;
                cout << "1.First Name" << endl;
                cout << "2.Last Name" << endl;
                cout << "3.Birthdate" << endl;
                cout << "4.Gender" << endl;
                cout << "5.Nationality" << endl;
                cout << "6.Email" << endl;
                cout << "7.Phone Number" << endl;
                cout << "8.Trait" << endl;
                cout << "9.Rank" << endl;
                cout << "10.OfficeNo" << endl;

                do {
                    cout << "> Enter mode: ";
                    cin >> edit_mode;
                    if (edit_mode < 0 || edit_mode > 12)
                        cout << "Invalid input, try again." << endl;
                } while (edit_mode < 0 || edit_mode > 12);

                switch (edit_mode) {
                case 1:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new First Name: ";
                    cin >> str;
                    secretary.setFname(id, str);
                    break;

                case 2:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Last Name: ";
                    cin >> str;
                    secretary.setLname(id, str);
                    break;

                case 3:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Birthdate: " << endl;
                    cout << "Day: ";
                    cin >> day;
                    cout << "Month: ";
                    cin >> month;
                    cout << "Year: ";
                    cin >> year;
                    secretary.setBirthDate(id, day, month, year);
                    break;

                case 4:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Gender: ";
                    cin >> ch;
                    secretary.setGender(id, ch);
                    break;

                case 5:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Nationality: ";
                    cin >> str;
                    secretary.setNationality(id, str);
                    break;

                case 6:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Email: ";
                    cin >> str;
                    secretary.setEmail(id, str);
                    break;

                case 7:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Phone Number: ";
                    cin >> str;
                    secretary.setPhone(id, str);
                    break;

                case 8:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Trait: ";
                    cin >> str;
                    secretary.setTrait(id, str);
                    break;

                case 9:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Rank: ";
                    cin >> str;
                    secretary.setRank(id, str);
                    break;

                case 10:
                    cout << "Give Professor's ID: ";
                    cin >> id;
                    cout << "Give the new Office Number: ";
                    cin >> str;
                    secretary.setOfficeNo(id, str);
                    break;

                default:
                    break;
                }

                break;

            case 3:
                cout << "Give Professor's ID: ";
                cin >> id;
                if (secretary.remove(id))
                    cout << "Professor with ID " << id << " was removed successfully." << endl;
                else
                    cout << "Professor with ID " << id << " could not be removed." << endl;
                break;

            default:
                break;
            }
            break;

        case 2:
            cout << "Available actions for Student:" << endl;
            cout << "0.Back" << endl;
            cout << "1.Insert Student" << endl;
            cout << "2.Modify Student" << endl;
            cout << "3.Remove Student" << endl;

            do {
                cout << "> Enter mode: ";
                cin >> submode;
                if (submode < 0 || submode > 3)
                    cout << "Invalid input, try again." << endl;
            } while (submode < 0 || submode > 3);

            switch (submode) {
            case 1:
                cin >> student;
                id = secretary.insert(student);
                if (id.compare("") != 0)
                    cout << "Student " << student.getFname() << " " << student.getLname() << " was inserted successfully with ID " << id << "." << endl;
                else
                    cout << "Student " << student.getFname() << " " << student.getLname() << " could not be inserted." << endl;
                break;

            case 2:
                cout << "What do you want to edit?" << endl;
                cout << "0.Back" << endl;
                cout << "1.First Name" << endl;
                cout << "2.Last Name" << endl;
                cout << "3.Birthdate" << endl;
                cout << "4.Gender" << endl;
                cout << "5.Nationality" << endl;
                cout << "6.Email" << endl;
                cout << "7.Phone Number" << endl;
                cout << "8.Semester" << endl;
                cout << "9.Starting Year" << endl;

                do {
                    cout << "> Enter mode: ";
                    cin >> edit_mode;
                    if (edit_mode < 0 || edit_mode > 9)
                        cout << "Invalid input, try again." << endl;
                } while (edit_mode < 0 || edit_mode > 9);

                switch (edit_mode) {
                case 1:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new First Name: ";
                    cin >> str;
                    secretary.setFname(id, str);
                    break;

                case 2:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Last Name: ";
                    cin >> str;
                    secretary.setLname(id, str);
                    break;

                case 3:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Birthdate: " << endl;
                    cout << "Day: ";
                    cin >> day;
                    cout << "Month: ";
                    cin >> month;
                    cout << "Year: ";
                    cin >> year;
                    secretary.setBirthDate(id, day, month, year);
                    break;

                case 4:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Gender: ";
                    cin >> ch;
                    secretary.setGender(id, ch);
                    break;

                case 5:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Nationality: ";
                    cin >> str;
                    secretary.setNationality(id, str);
                    break;

                case 6:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Email: ";
                    cin >> str;
                    secretary.setEmail(id, str);
                    break;

                case 7:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Phone Number: ";
                    cin >> str;
                    secretary.setPhone(id, str);
                    break;

                case 8:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Semester: ";
                    cin >> semester;
                    secretary.setSemester(id, semester);
                    break;

                case 9:
                    cout << "Give Student's ID: ";
                    cin >> id;
                    cout << "Give the new Starting Year: ";
                    cin >> year;
                    secretary.setStartingYear(id, year);
                    break;

                default:
                    break;
                }

                break;

            case 3:
                cout << "Give Student's ID: ";
                cin >> id;
                if (secretary.remove(id))
                    cout << "Student with ID " << id << " was removed successfully." << endl;
                else
                    cout << "Student with ID " << id << " could not be removed." << endl;
                break;

            default:
                break;
            }
            break;

        case 3:
            cout << "Available actions for Course:" << endl;
            cout << "0.Back" << endl;
            cout << "1.Insert Course" << endl;
            cout << "2.Modify Course" << endl;
            cout << "3.Remove Course" << endl;

            do {
                cout << "> Enter mode: ";
                cin >> submode;
                if (submode < 0 || submode > 3)
                    cout << "Invalid input, try again." << endl;
            } while (submode < 0 || submode > 3);

            switch (submode) {
            case 1:
                cin >> course;
                if (secretary.insertCourse(course))
                    cout << "Course " << course.getName() << " was inserted successfully." << endl;
                else
                    cout << "Course " << course.getName() << " could not be inserted." << endl;
                break;

            case 2:
                cout << "What do you want to edit?" << endl;
                cout << "0.Back" << endl;
                cout << "1.Name" << endl;
                cout << "2.Semester" << endl;
                cout << "3.Ects" << endl;
                cout << "4.Course Type" << endl;

                do {
                    cout << "> Enter mode: ";
                    cin >> edit_mode;
                    if (edit_mode < 0 || edit_mode > 4)
                        cout << "Invalid input, try again." << endl;
                } while (edit_mode < 0 || edit_mode > 4);

                switch (edit_mode) {
                case 1:
                    cout << "Give Course's Name: ";
                    cin >> str;
                    cout << "Give the new Course Name: ";
                    cin >> str;
                    secretary.setCourseName(id, str);
                    break;

                case 2:
                    cout << "Give Course's Name: ";
                    cin >> str;
                    cout << "Give the new Semester: ";
                    cin >> semester;
                    if (!secretary.transferCourse(str, semester)) {
                        cout << "Invalid semester" << endl;
                    }
                    break;

                case 3:
                    cout << "Give Course's Name: ";
                    cin >> str;
                    cout << "Give the new Ects: " << endl;
                    cin >> ects;
                    secretary.setCourseEcts(str, ects);
                    break;

                case 4:
                    cout << "Give Course's Name: ";
                    cin >> id;
                    cout << "Give the Course Type: ";
                    cin >> str;
                    if (str.compare("Mandatory") == 0)
                        secretary.setCourseType(id, true);
                    else
                        secretary.setCourseType(id, false);
                    break;

                default:
                    break;
                }

                break;

            case 3:
                cout << "Give Course's Name: ";
                cin >> str;
                if (secretary.removeCourse(str))
                    cout << "Course " << str << " was removed successfully." << endl;
                else
                    cout << "Course " << str << " could not be removed." << endl;
                break;

            default:
                break;
            }
            break;

        case 4:
            cout << "Give the Course you want to assign to a Professor: ";
            cin >> str;
            cout << "Give the Professor's ID: ";
            cin >> id;
            if (secretary.assignCourseToProfessor(str, id))
                cout << "Course " << str << " assigned to Professor with ID: " << id << endl;
            else
                cout << "Could not assign Course " << str << " to Professor with ID: " << id;
            break;

        case 5:
            cout << "Give the Course you want to register a Student: ";
            cin >> str;
            cout << "Give the Student's ID: ";
            cin >> id;
            if (secretary.registerStudentToCourse(str, id))
                cout << "Student with ID " << id << " registered to Course " << str << endl;
            else
                cout << "Could not register Student with ID " << id << " to Course " << str << endl;
            break;

        case 6:
            cout << "Give Course's Name: ";
            cin >> str;
            secretary.displaySaveStudentsWhoPassedCourse(str);
            break;

        case 7:
            cout << "Give the Professor's ID to display statistics: ";
            cin >> id;
            secretary.displayStatistics(id);
            break;

        case 8:
            cout << "Give the Student's ID to display statistics: ";
            cin >> id;
            secretary.displayGrades(id);
            break;

        case 9:
            cout << "Students that can graduate:" << endl;
            secretary.displayGraduates();
            break;

        case 10:
            cout << "Give Professor's ID: ";
            cin >> id;
            cout << "Give the Course's name: ";
            cin >> str;
            secretary.assignGrades(str, id);
            break;

        case 11:
            cout << "Give the Student's ID: ";
            cin >> id;
            cout << "Give the Course's Name: ";
            cin >> str;
            if (secretary.unregisterStudentFromCourse(str, id))
                cout << "Student with ID " << id << " unregistered from Course " << str << endl;
            else
                cout << "Could not unregister Student with ID " << id << " from Course " << str << endl;
            break;

        case 12:
            cout << "Give the Professor's ID: ";
            cin >> id;
            cout << "Give the Course's Name: ";
            cin >> str;
            if (secretary.unassignCourseFromProfessor(str, id))
                cout << "Course " << str << " unassigned from Professor with ID " << id << endl;
            else
                cout << "Could not unassign Course " << str << " from Professor with ID " << id << endl;
            break;

        case 13:
            cout << secretary;
            break;

        default:
            cout << "Exited secretary of " << secretary.getDepartment() << "." << endl;
            secretary.updateFile(argv[1]);
            return 0;
        }
    }

    return 0;
}