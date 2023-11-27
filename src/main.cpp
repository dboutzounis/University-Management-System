#include "../include/secretary.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(void) {
    Person p;
    string department, mode, id;
    cout << "Enter the name of the department: ";
    getline(cin, department);
    cout << endl;
    Secretary secretary(department), copiedSecretary;
    cout << "---WELCOME TO THE SECRETARY OF " << secretary.getDepartment() << "!---" << endl
         << endl;

    while (true) {
        // Displaying the available secretary options
        cout << "-Secretary Menu-" << endl;
        cout << "1.Insert People" << endl;
        cout << "2.Insert Person" << endl;
        cout << "3.Search Person" << endl;
        cout << "4.Remove Person" << endl;
        cout << "5.Copy Department" << endl;
        cout << "6.Display Department" << endl;
        cout << "7.Exit" << endl;

        // Checking if user gave valid input
        do {
            cout << "> Enter mode: ";
            cin >> mode;
            if (mode[0] < '1' || mode[0] > '7' || mode.length() != 1)
                cout << "Invalid input, try again." << endl;
        } while (mode[0] < '1' || mode[0] > '7' || mode.length() != 1);

        switch (mode[0]) {
        case '1':
            cin >> secretary;
            break;

        case '2':
            cin >> p;
            if (secretary.insert(p))
                cout << "Person inserted successfully to " << secretary.getDepartment() << "." << endl;
            else
                cout << "Insertion to " << secretary.getDepartment() << " failed." << endl;
            cout << endl;
            break;

        case '3':
            cout << "Enter the ID of the person you are searching for: ";
            cin >> id;
            if (secretary.search(id)) {
                cout << "Found the person: " << endl;
                secretary.displayPerson(id);
            } else {
                cout << "Person not found." << endl;
            }
            cout << endl;
            break;

        case '4':
            cout << "Enter the ID of the person you want to remove: ";
            cin >> id;
            if (secretary.remove(id)) {
                cout << "Person removed successfully from " << secretary.getDepartment() << "." << endl;
            } else {
                cout << "Person cannot be removed." << endl;
            }
            cout << endl;
            break;

        case '5':
            cout << "This is the copied Secretary before the copy constructor:" << endl;
            cout << copiedSecretary;
            copiedSecretary = secretary;
            cout << "This is the copied secretary after the copy constructor:" << endl;
            cout << copiedSecretary;
            break;

        case '6':
            cout << secretary;
            break;

        default:
            cout << "Exited secretary of " << secretary.getDepartment() << "." << endl;
            return 0;
            break;
        }
    }

    return 0;
}