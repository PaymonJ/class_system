# class_system
## Introduction

This application, called Class System, is used for managing the grades of a classroom. The classroom's data is comprised of data relating to each student which is comprised of a student number and a grade. The student data can be entered manually in the program itself, or read from a properly formatted `.CSV` file.

Within the program, one can do the following:
* add students to a classroom either manually or read from a `.CSV`
* change an existing students grade
* view the mean and standard deviation calculated from the classroom data
* output student data and statistics to terminal or to a `.CSV` file.

## Methods

The program consists of two classes: `Student` and `Section`. Class `Student` is a node consisting of both a student number and a grade, and class `Section` is the class that is to contain all students and has several functions to assist with managing the grades of a class.

Here are the methods of each class:

`Student`
* Public
  * `Student()` - the constructor
  * `getStudentNumber()` - returns the student's student number
  * `getGrade()` - returns the student's grade
  * `updateGrade(newGrade)` - changes the student's grade with `newGrade`
* Private
  * `studentNumber` - stores the student's student number
  * `grade` - stores the student's grade

`Section`
* Public
  * `Section()` - the constructor
  * `addStudent(studentNumber, grade)` - adds a new student to the section
  * `changeGrade(studentNumber, newGrade)` - changes the grade belonging to the student in the section to `newGrade`
  * `printStudents()` - prints all students in the section
  * `printStats()` - prints section statistics
  * `readFromFile(fileName)` - reads student data from `fileName`
  * `writeToFile(fileName)` - writes student data to `fileName` and section statistics to `STATSfileName`
* Private
  * `validateGrade(grade)` - ensures that `grade` >= 0 and <= 100 
  * `calculateStats()` - calculates the mean and standard deviation of the class after everytime a grade is entered or changed
  * `section[]` - the section holding the class data
  * `size` - keeps track of the amount of students in the section
  * `minGrade` - keeps track of the minimum section grade
  * `maxGrade` - keeps track of the maximum section grade
  * `mean` - stores the mean of the class grades
  * `standardDeviation` - stores the standard deviation of the class grades


## Test Case
The test case provided in `main.cpp` reads the given sample data from `sampleData.csv`, adds some new students, changes the student's grades, then save the modified data to `sampleData.csv` and the new class statistics to `STATSsampleData.csv`.

Here is how to run the test case:

1. Download/clone this repository.
1. Open the downloaded/cloned folder.
1. Compile and run using this command: `g++ -o run -std=c++11 main.cpp && ./run`.
