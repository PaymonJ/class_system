#ifndef STUDENT_H
#define STUDENT_H

/*
* Each student consists of a student number and grade.
* Contains abilities to read student number and grade values along with ability to change grade.
*/
class Student {
    public:
        Student(unsigned int studentNo, float percent);
        unsigned int getStudentNumber();
        float getGrade();
        void setGrade(float newGrade);
    private:
        unsigned int studentNumber;
        float grade;
};

#endif