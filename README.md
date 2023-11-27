# Object Oriented Programming Project

## University Department Management System

![](https://www.di.uoa.gr/sites/default/files/2020-04/DIT_banner.jpg)

## Overview

The purpose of the project, is to implement a system that manages the members of a university, such as the students and the professors. The secretary is responsible for the use of this program in order to collect, organize and store all the necessary data of the department.

This part of the project, implements the two most important classes that constitute the university department management system. These two classes are:
the person class and the secretary class.

## Person Class

This Person class in general, can represent a student or a professor. As private members the Person class has:

-   `First name`
-   `Last name`
-   `Day of birth`
-   `Month of birth`
-   `Year of birth`
-   `Gender`
-   `Nationality`
-   `E-mail`
-   `Phone number`
-   `ID`

The class also uses a static int variable (count) that counts how many objects of this class have been constructed.

These are the methods of the class Person:

-   `Constructors`
-   `Destructor`
-   `Output stream operator overloading`
-   `Input stream operator overloading`
-   `Accessors`

Inside the Person class the Secretary class is declared as friend in order for the Secretary to access the private members and methods of the Person class.

## Secretary Class

This Secretary class in general, represents a Secretary data base that contains all the information of the university members. As private members the Secretary class has:

-   `Department name`
-   `Map Data Structure`

We chose to use a Map Data Structure for the Secretary data base in order to quickly access/insert/search/remove any of the university members through their ID.

These are the methods of the class Secretary:

-   `Constructors`
-   `Destructor`
-   `Copy Constructor`
-   `Operator= overloading`
-   `Operator+= overloading`
-   `Operator-= overloading`
-   `Output stream operator overloading`
-   `Input stream operator overloading`
-   `Display`
-   `Search`
-   `Insert`
-   `Remove`
-   `Count`
-   `Accessors`
-   `Mutators`

## Compile and Run

We implemented a main program, that showcases our university department management system. The main program presents a menu with the available options of the Secretary class. The user needs to type the number of the option they want to execute.

To compile and run the main program:

```
make
```

```
./main
```

## Authors

-   Boutzounis Dimitrios-Nikolaos sdi2200112
-   Stavrou Spyridon sdi2200172
