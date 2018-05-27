#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "classes.h"

using namespace std;

int main()
{
    string file = "sampleData.csv";

    try
    {
        Section *CMPT225 = new Section();
        CMPT225->readFromFile(file);

        CMPT225->addStudent("31254789", 75);
        CMPT225->addStudent("32698567", 88);
        CMPT225->addStudent("38945321", 62);

        CMPT225->changeGrade("32543595", 51);
        CMPT225->changeGrade("32404376", 42);

        CMPT225->writeToFile(file);
        CMPT225->printStudents();
        CMPT225->printStats();
    }
    catch (invalid_argument &eIA)
    {
        cout << "Exception: " << eIA.what() << endl;
        cout << "Non-numeric grade found in " << file << endl;
    }
    catch (exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}
