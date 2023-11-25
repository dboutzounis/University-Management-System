#include "../include/secretary.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(void) {
    string dep, id;
    cout << "Enter the name of the department: ";
    cin >> dep;
    cout << endl;
    Secretary secretary(dep), copiedSecretary;
    char mode;
    cout << "WELCOME TO THE SECRETARY OF " << secretary.getDepartment() << "!" << endl
         << endl;

    while (true) {
        // Displaying the available secretary options
        cout << "Secretary Menu" << endl;
        cout << "1.Input People" << endl;
        cout << "2.Search Person" << endl;
        cout << "3.Remove Person" << endl;
        cout << "4.Copy Department" << endl;
        cout << "5.Display Department" << endl;
        cout << "6.Exit" << endl;

        // Checking if user gave valid input
        do {
            cout << "> Enter mode: ";
            cin >> mode;
            if (mode < '1' && mode > '6')
                cout << "Invalid input, try again." << endl;
        } while (mode < '1' && mode > '6');

        switch (mode) {
        case '1':
            cin >> secretary;
            break;

        case '2':
            cout << "Enter the ID of the person you are searching for: ";
            cin >> id;
            if (secretary.search(id)) {
                cout << "We found the person: " << endl;
                secretary.displayPerson(id);
            } else {
                cout << "Person not found." << endl;
            }
            cout << endl;
            break;

        case '3':
            cout << "Enter the ID of the person you want to remove: ";
            cin >> id;
            if (secretary.remove(id)) {
                cout << "Person removed." << endl;
            } else {
                cout << "Person cannot be removed." << endl;
            }
            cout << endl;
            break;

        case '4':
            cout << "This is the copied Secretary before the copy constructor:" << endl;
            cout << copiedSecretary;
            copiedSecretary = secretary;
            cout << "This is the copied secretary after the copy constructor:" << endl;
            cout << copiedSecretary;
            break;

        case '5':
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