#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "classes.h"

using namespace std;

int main()
{
    string file = "sampleData.csv";
    Section *CMPT225 = new Section();

    CMPT225->readFromFile(file);
    CMPT225->addStudent("30554332", 100);
    CMPT225->changeGrade("30500660", 0);

    CMPT225->writeToFile(file);

    CMPT225->printStudents();
    CMPT225->printStats();

    return 0;
}
