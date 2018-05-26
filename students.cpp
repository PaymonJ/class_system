#include <iostream>
#include <string>
#include <cmath>
#include "classes.h"

using namespace std;

int main()
{
    Section *CMPT225 = new Section();
    CMPT225->addStudent("31257685", 1);
    CMPT225->addStudent("39290219", 4);
    CMPT225->addStudent("93299292", 7);
    CMPT225->addStudent("02020020", 2);
    CMPT225->addStudent("29292929", 6);
    CMPT225->printStudents();
    CMPT225->printStats();

    return 0;
}
