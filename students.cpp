#include <iostream>
#include <string>
#include <cmath>
#include "classes.h"

using namespace std;

int main()
{
    Section *CMPT225 = new Section();
    CMPT225->addStudent("1", 1);
    CMPT225->addStudent("3", 1);
    CMPT225->addStudent("2", 1);
    CMPT225->addStudent("3", 1);
    CMPT225->addStudent("4", 1);
    CMPT225->changeGrade("0", 1);
    CMPT225->changeGrade("3", 90);
    CMPT225->printStudents();

    return 0;
}
