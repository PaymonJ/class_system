#ifndef SECTION_H
#define SECTION_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "student.h"

using namespace std;

class Section {
    public:
        Section();
        void addStudent(int studentNumber, float grade);
        void changeGrade(unsigned int studentNumber, float newGrade);
        void printStudents();
        void printStats();
        void readFromFile(string fileName);
        void writeToFile(string fileName);
    private:
        float minGrade;
        float maxGrade;
        float mean;
        float standardDeviation;
        vector<Student> students;
        Student* studentSearch(unsigned int studentID);
        void calculateStats();
};

#endif