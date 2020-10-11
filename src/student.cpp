#include "student.h"
#include <stdexcept>

Student::Student(unsigned int studentNo, float percent) 
    : studentNumber(studentNo), grade(percent)
{
    if (percent < 0 || percent > 100) {
        throw std::invalid_argument("InvalidArgumentException: grade must be between 0 and 100 inclusively.");
    }
}

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