#include "../include/person.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(void) {
    Person p;

    cout << p;
    cout << p.getCount() << endl;

    return 0;
}