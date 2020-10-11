#include "section.h"

Section::Section() {}

/*
* Adds a new student to the class instance.
*/
void Section::addStudent(int studentNumber, float grade)
{
    try {
        Student newStudent = Student(studentNumber, grade);

        if (this->students.empty()) {
            this->minGrade = grade;
            this->maxGrade = grade;
            this->mean = grade;
            this->standardDeviation = 0;
        }
        else {
            if (this->studentSearch(studentNumber) != NULL) {
                throw std::invalid_argument("InvalidArgumentException: student " + to_string(studentNumber) + " already exists.");
            }

            if (grade < this->minGrade) this->minGrade = grade;
            if (grade > this->maxGrade) this->maxGrade = grade;
        }
        students.push_back(newStudent);
        this->calculateStats();
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
}

/*
* Changes grade of existing student.
*/
void Section::changeGrade(unsigned int studentNumber, float newGrade)
{
    Student* studentToUpdate = this->studentSearch(studentNumber);
    if (studentToUpdate == NULL) {
        throw std::invalid_argument("InvalidArgumentException: student " + to_string(studentNumber) + " not found.");
    }

    studentToUpdate->setGrade(newGrade);
    this->calculateStats();
    if (newGrade < this->minGrade) this->minGrade = newGrade;
    if (newGrade > this->maxGrade) this->maxGrade = newGrade;

}

/*
* Prints all student numbers and respective grades to terminal..
*/
void Section::printStudents()
{
    cout << "Student Number, Grade" << endl;
    cout << "---------------------" << endl;
    for(auto &student : this->students) {
        cout << student.getStudentNumber() << ", " << student.getGrade() << endl;
    }
}

/*
* Prints statistics to terminal.
*/
void Section::printStats()
{
    cout << "Total students: " << this->students.size() << endl;
    cout << "Minimum Grade: " << this->minGrade << endl;
    cout << "Maximum Grade: " << this->maxGrade << endl;
    cout << "Mean: " << this->mean << endl;
    cout << "Standard Deviation: " << this->standardDeviation << endl;
}

/*
* Reads data from CSV file and puts information into a class instance.
*/
void Section::readFromFile(string fileName)
{
    ifstream fileToRead(fileName.c_str());
    string studentNumberString;
    string gradeString;
    unsigned int studentNumber;
    float grade;
    while(getline(fileToRead, studentNumberString, ','))
    {
        getline(fileToRead, gradeString);
        studentNumber = stoi(studentNumberString);
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
    for(auto &student : this->students) {
        output += to_string(student.getStudentNumber()) + "," 
                    + to_string(student.getGrade()) + "\n"; 
    }
    fileToWrite << output;
    fileToWrite.close();

    ofstream fileToWriteStats(("STATS" + fileName).c_str());
    string outputStats = "";
    outputStats += "Total students: " + to_string(this->students.size()) + "\n";
    outputStats += "Minimum grade: " + to_string(this->minGrade) + "\n";
    outputStats += "Maximum grade: " + to_string(this->maxGrade) + "\n";
    outputStats += "Mean: " + to_string(this->mean) + "\n";
    outputStats += "Standard Deviation: " + to_string(this->standardDeviation) + "\n";
    fileToWriteStats << outputStats;
    fileToWriteStats.close();
}

/*
* Linear search algorithm that checks if a student is already registered.
* Returns the student if they are registered, and NULL if there are not.
*/
Student* Section::studentSearch(unsigned int studentID)
{
    for (auto &student : students) {
        if (student.getStudentNumber() == studentID) {
            return &student;
        }
    }
    return NULL;
}

/*
* Calculates mean and std deviation.
*/
void Section::calculateStats()
{
    float meanSum = 0;
    float stdSum = 0;
    unsigned int size = this->students.size();

    for(auto &student : this->students) {
        meanSum += student.getGrade();
    }

    float mean = meanSum / size;

    for(auto &student : this->students) {
        stdSum += pow((student.getGrade() - mean), 2);
    }

    this->mean = mean;
    this->standardDeviation = sqrt(stdSum/size);
}