# Object Oriented Programming Project

## University Department Management System

![](https://www.di.uoa.gr/sites/default/files/2020-04/DIT_banner.jpg)

## Overview

The purpose of the project, is to implement a system that manages the members of a university, such as the students and the professors. The secretary is responsible for the use of this program in order to collect, organize and store all the necessary data of the department.

This project is implemented using five classes that constitute different fields of a university. First of all, the Student and Professor classes represent the members of the department and inherit their main characteristics from an abstract-base class called Person. Another field of the department are the Courses, which are represented by a class that holds info about the elements of the course, such as the semester, grades, staff, etc. All these classes are managed by a single class called Secretary, which is able to handle all the interactions between them, collect info, provide additional context and operations.  

## Implementation

### Person Class

This class in general, represents an abstract version of the Student and Professor classes. As protected members the Person class holds the fullname, birthdate, gender, nationality, email, phone and id (initialized when a Person enters the Secretary).

The class also uses a static int variable (count) that counts how many objects of this class have been constructed.

Inside the class, we declared a pure virtual memory allocator and display functions for subclasses, in order to make the class abstract.

These are the methods of the Person class:

-   `Constructors`
-   `Destructor`
-   `Output stream operator overloading`
-   `Input stream operator overloading`
-   `Accessors`
-   `Mutators`
-   `Virtual Allocators for subclasses`

### Professor Class

A Professor is defined as a Person who can teach Courses and assign grades to the Students who participate in them. Due to this fact, the Professor Class inherits the data members and the methods from the base class Person but also, adds four more fields: trait (DEP, EDIP), rank (Emeritus, Professor, Assistant), office number and a vector with all the Courses he/she teach.

These are the methods of the Professor class:

-   `Constructors`
-   `Destructor`
-   `Output stream operator overloading`
-   `Input stream operator overloading`
-   `Accessors`
-   `Mutators`
-   `Allocator`
-   `Insert Course`
-   `Remove Course`
-   `Search Course`
-   `Display Statistics`


### Student Class

A Student is defined as a Person who can attend Courses, participate in exams and graduate. The Student Class inherits the data members and the methods from the base class Person but also, adds six more fields: semester, ects, gpa, starting year, a vector for the Courses he/she attends this semester and a vector with all the Courses he/she passed through the years.

These are the methods of the Student class:

-   `Constructors`
-   `Destructor`
-   `Output stream operator overloading`
-   `Input stream operator overloading`
-   `Accessors`
-   `Mutators`
-   `Allocator`
-   `Insert Course - Passed Course`
-   `Remove Course - Passed Course`
-   `Search Course - Passed Course`
-   `Display Grades`

### Course Class

The Course class represents any available Course that the university offers for participation to the Students and for teaching to the Professors. The class consists of the following data members: course name, ects, course type (Mandatory, Optional), semester, a map handling the students that attend this Course (current semester), a map holding the teaching staff and a map that carries the grades of the students. 

These are the methods of the Course class:

-   `Constructors`
-   `Destructor`
-   `Output stream operator overloading`
-   `Input stream operator overloading`
-   `Accessors`
-   `Mutators`
-   `Insert Student - Professor`
-   `Remove Student - Professor`
-   `Search Student - Professor`
-   `Display Student - Professor`

### Secretary Class

The Secretary class in general, represents a Secretary data base that contains all the information about the university members and the courses. This class holds the following data members: department name, department id, years of study, current year, graduation ects, student-professor count, the map unidata that consists of all the members (Students, Professors) of the university and the map curriculum that handles the Courses of each semester.

#### Unidata Map

A map (key = id, Person *) was the best choice to store all the members of the university, because it provides fast access to any value using a unique key and thus makes the display/search/insert/modify/remove member operations way easier. Every Person entered in the Secretary is equiped with a uniquely generated id. The id provided to the Students consists of the department id, the starting year of the Student and the order he registered that year (student count). The id provided to the Professors consists of the department id and the order they were assigned to teach in the university (professor count).

#### Curriculum Map

A map (key = semester, vector(Course *)) was used to implement the concept of semester. With this map, we were able to organize every Course according to its semester. That's why we gathered all the Courses of a semester in the same vector. This allows us to handle any display/search/insert/modify/remove Course operations, but also to assign/unassign Professors, register/unregister Students, assign grades, display statistics, Students who passed a certain course and Students who can graduate, all these with the help of the classes mentioned before.

#### Parse/Update File

The Secretary class has the ability to input data through a file. This is be possible with the function ParseInput(), which takes as an argument a file in order to open it and access any data necessary to initialize a Secretary object. To achieve this operation, the file must have a certain format:

```
Secretary <department name> <department id> <years of study> <graduation ects>
Course <name> <semester> <ects> <type (Mandatory/Optional)>
.
.
.
Professor <firstname> <lastname> <day> <month> <year> <gender> <nationality> <email> <phone> <id="0"> <trait> <rank> <office> (<Course_1> ... <Course_n>)
.
.
.
Student <firstname> <lastname> <day> <month> <year> <gender> <nationality> <email> <phone> <id="0"> <semester> <ects> <gpa> <starting year> (<Course_1> <Grade_1> ... <Course_n> <Grade_n>)
.
.
.
```
In the start of every line there must be Course, Professor or Student. Only the first line has Secretary. The elements inside () are optional.

The Secretary elements must be on the first line, the Courses follow and then there are the Professors and the Students.

At the end of the program execution this file updates with the same format based on the modifications the user did in the Secretary Menu.

These are the methods of the class Secretary:

-   `Constructors`
-   `Destructor`
-   `Copy Constructor`
-   `Operator= overloading`
-   `Operator+= overloading`
-   `Operator-= overloading`
-   `Output stream operator overloading`
-   `Input stream operator overloading`
-   `Accessors`
-   `Mutators`
-   `Display Student - Professor - Course`
-   `Search Student - Professor - Course`
-   `Insert Student - Professor - Course`
-   `Remove Student - Professor - Course`
-   `Assign/Unassign Course to/from Professor`
-   `Register/Unregister Student to/from Course`
-   `Assign grades`
-   `Display Statistics/Grades/Graduates/Students who passed a Course`
-   `Parse/Update File`
-   `Size of Unidata`

## Main

We implemented a main program, that showcases our university department management system. The main program presents a menu with the available options of the Secretary class. The user needs to type the number of the option they want to execute.

We provide a ready-to-use file called `database.txt` for Secretary initialization.

## Compile and Run

To compile and run the main program:

```
make
```

```
./main <input-file>
```

To clean the object-executable files:

```
make clean
```

## Authors

-  [Boutzounis Dimitrios-Nikolaos sdi2200112](https://github.com/dboutzounis)
-   [Stavrou Spyridon sdi2200172](https://github.com/spirosst16)
