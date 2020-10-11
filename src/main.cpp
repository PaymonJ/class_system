#include <iostream>
#include <string>
#include "../include/section.h"

using namespace std;

int main()
{
    string file = "../sampleData.csv";

    try
    {
        Section *CMPT225 = new Section();
        CMPT225->readFromFile(file);

        CMPT225->addStudent(31254789, 75);
        CMPT225->addStudent(32698567, 88);
        CMPT225->addStudent(38945321, 62);

        CMPT225->changeGrade(32543595, 51);
        CMPT225->changeGrade(32404376, 42);

        CMPT225->writeToFile(file);
        CMPT225->printStudents();
        CMPT225->printStats();
    }
    catch (invalid_argument &eIA)
    {
        cout << eIA.what() << endl;
    }

    return 0;
}
