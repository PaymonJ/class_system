#ifndef CLASSES_H
#define CLASSES_H

using namespace std;

/*
* Each student consists of a student number and grade.
* Contains abilities to read student number and grade values along with ability to change grade.
*/
class Student {
    public:
        Student(string studentNo, float percent) { studentNumber = studentNo; grade = percent; };
        string getStudentNumber() { return studentNumber; }
        float getGrade() { return grade; }
        void updateGrade(float updatedGrade) { grade = updatedGrade; }
    private:
        string studentNumber;
        float grade;
};

/*
* Array based implementation of a class section.
* Contains abilities to add students, modify them, and calculate statistics based on their grades.
* IO capabilities including writing to STDOUT, reading from a file, and writing to files.
*/
class Section {
    public:
        Section(){size = 0;};
        void addStudent(string studentNumber, float grade);
        void changeGrade(string studentNumber, float newGrade);
        void printStudents();
        void printStats();
        void readFromFile(string fileName);
        void writeToFile(string fileName);
    private:
        bool validateGrade(float grade) { return grade < 0 || grade > 100 ? false : true;}; /* Checks to see if the grade is not less than 0 or greater than 100. */
        void calculateStats();
        Student* binarySearch(Student* arrOfStudents[], int first, int last, string student);
        Student* section[1000];
        unsigned int size;
        float minGrade;
        float maxGrade;
        float mean;
        float standardDeviation;
};

/* PUBLIC METHODS */

/*
* Adds a new student to the class instance.
* Inserts new student in chronological order by student number.
*/
void Section::addStudent(string studentNumber, float grade)
{
    /* Ensure grade is valid - return if it is not. */
    if (!validateGrade(grade))
    {
        cout << "Invalid grade." << endl;
        return;
    }

    /* Create new student. */
    Student *newStudent = new Student(studentNumber, grade);

    /* If no other students exist, just insert at the beginning - set min/max grade accordingly. */
    if(size == 0)
    {
        section[0] = newStudent;
        minGrade = newStudent->getGrade();
        maxGrade = newStudent->getGrade();
    }
    else
    {
        /* First ensures student is not a duplicate - return if it does not. */
        Student *checkDup = binarySearch(section, 0, size-1, studentNumber);
        if (checkDup != NULL)
        {
            cout << "Student " << studentNumber << " found. Not adding." << endl;
            return;
        }
        /* Check if new student has the min.max grade. */
        if(newStudent->getGrade() < minGrade) minGrade = newStudent->getGrade();
        if(newStudent->getGrade() > maxGrade) maxGrade = newStudent->getGrade();

        /* Place student in chronological order by student number using insertion algorithm. */
        int i = size;
        while ((i > 0) && (newStudent->getStudentNumber() < section[i-1]->getStudentNumber()))
        {
            section[i] = section[i-1];
            i = i - 1;
        }
        section[i] = newStudent;
    }
    size++;
    calculateStats();
}

/*
* Changes grade of existing student.
*/
void Section::changeGrade(string studentNumber, float newGrade)
{
    /* First ensures student exists - return if it does not. */
    Student *studentToUpdate = binarySearch(section, 0, size-1, studentNumber);
    if (studentToUpdate == NULL) cout << "Student " << studentNumber << " not found. Grade not updated." << endl;
    else
    {
        /* Ensure grade is valid - return if it is not. */
        if (!validateGrade(newGrade))
        {
            cout << "Invalid grade." << endl;
            return;
        }

        /* Update grade, calculate statistics, and check if the new grade is the new min/max. */
        float oldGrade = studentToUpdate->getGrade();
        studentToUpdate->updateGrade(newGrade);
        calculateStats();
        if(studentToUpdate->getGrade() < minGrade) minGrade = studentToUpdate->getGrade();
        if(studentToUpdate->getGrade() > maxGrade) maxGrade = studentToUpdate->getGrade();
        cout << "Student " << studentNumber << " grade updated from " << oldGrade << " to " << studentToUpdate->getGrade() << "." << endl;
    }
}

/*
* Prints all student numbers and respective grades to terminal..
*/
void Section::printStudents()
{
    cout << "Student Number, Grade" << endl;
    cout << "---------------------" << endl;
    for(unsigned int i = 0; i < size; i++)
    {
        cout << section[i]->getStudentNumber() << ", " << section[i]->getGrade() << endl;
    }
}

/*
* Prints statistics to terminal.
*/
void Section::printStats()
{
    cout << "Total students: " << size << endl;
    cout << "Minimum Grade: " << minGrade << endl;
    cout << "Maximum Grade: " << maxGrade << endl;
    cout << "Mean: " << mean << endl;
    cout << "Standard Deviation: " << standardDeviation << endl;
}

/*
* Reads data from CSV file and puts information into a class instance.
*/
void Section::readFromFile(string fileName)
{
    ifstream fileToRead(fileName.c_str());
    string studentNumber;
    string gradeString;
    float grade;
    while(getline(fileToRead, studentNumber, ','))
    {
        getline(fileToRead, gradeString);
        grade = stof(gradeString);

        addStudent(studentNumber, grade);
    }
    fileToRead.close();
}

/*
* Writes the final state of the section to a file with any changes made.
* Writes a second file with the statistics(class size, min grade, max grade, mean, and std deviation).
*/
void Section::writeToFile(string fileName)
{
    ofstream fileToWrite(fileName.c_str());
    string output = "";
    for(unsigned int i = 0; i < size; i++)
    {
        output += section[i]->getStudentNumber() + "," + to_string(section[i]->getGrade()) + "\n";
    }
    fileToWrite << output;
    fileToWrite.close();

    ofstream fileToWriteStats(("STATS" + fileName).c_str());
    string outputStats = "";
    outputStats += "Total students: " + to_string(size) + "\n";
    outputStats += "Minimum grade: " + to_string(minGrade) + "\n";
    outputStats += "Maximum grade: " + to_string(maxGrade) + "\n";
    outputStats += "Mean: " + to_string(mean) + "\n";
    outputStats += "Standard Deviation: " + to_string(standardDeviation) + "\n";
    fileToWriteStats << outputStats;
    fileToWriteStats.close();
}

/* PRIVATE METHODS */

/*
* Calculates mean and std deviation.
*/
void Section::calculateStats()
{
    float sum = 0;
    for(unsigned int i = 0; i < size; i++)
    {
        sum += section[i]->getGrade();
    }
    mean = sum/size;
    sum = 0;
    for(unsigned int i = 0; i < size; i++)
    {
        sum += pow((section[i]->getGrade() - mean), 2);
    }
    standardDeviation = sqrt(sum/size);
}

/*
* Binary search algorithm that checks if a student is already registered.
* Returns the student if they are registered, and NULL if there are not.
*/
Student* Section::binarySearch(Student* arrOfStudents[], int first, int last, string student)
{
    if (first <= last)
    {
        int mid = (first + last)/2;
        if (arrOfStudents[mid]->getStudentNumber() == student) return arrOfStudents[mid];
        else if (arrOfStudents[mid]->getStudentNumber() > student) return binarySearch(arrOfStudents, first, mid-1, student);
        else return binarySearch(arrOfStudents, mid+1, last, student);
    }
    return NULL;
}

#endif
