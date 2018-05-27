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

        CMPT225->writeToFile(file);

        CMPT225->printStudents();
        CMPT225->printStats();
    }
    catch (std::exception& invalid_argument)
    {
        cout << "Non-numeric grade found in " << file << endl;
    }


    return 0;
}
