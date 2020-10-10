#include "student.h"

Student::Student(unsigned int studentNo, float percent) 
    : studentNumber(studentNo), grade(percent) {}

unsigned int Student::getStudentNumber()
{
    return this->studentNumber;
}

float Student::getGrade()
{
    return this->grade;
}

void Student::setGrade(float newGrade)
{
    this->grade = newGrade;
}