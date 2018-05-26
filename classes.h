#ifndef CLASSES_H
#define CLASSES_H

using namespace std;

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

class Section {
    public:
        Section(){size = 0;};
        void addStudent(string studentNumber, float grade);
        void changeGrade(string studentNumber, float newGrade);
        void printStudents();
        void printStats();
    private:
        void calculateStats();
        bool validateGrade(float grade) { return grade < 0 || grade > 100 ? false : true;};
        Student* binarySearch(Student* arrOfStudents[], int first, int last, string student);
        Student* section[1000];
        unsigned int size;
        float minGrade;
        float maxGrade;
        float mean;
        float standardDeviation;
};

void Section::addStudent(string studentNumber, float grade)
{
    if (!validateGrade(grade))
    {
        cout << "Invalid grade." << endl;
        return;
    }

    Student *newStudent = new Student(studentNumber, grade);

    if(size == 0)
    {
        section[0] = newStudent;
        minGrade = newStudent->getGrade();
        maxGrade = newStudent->getGrade();
    }
    else
    {
        Student *checkDup = binarySearch(section, 0, size-1, studentNumber);
        if (checkDup != NULL)
        {
            cout << "Student " << studentNumber << " found. Not adding." << endl;
            return;
        }

        if(newStudent->getGrade() < minGrade) minGrade = newStudent->getGrade();
        if(newStudent->getGrade() > maxGrade) maxGrade = newStudent->getGrade();

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

void Section::changeGrade(string studentNumber, float newGrade)
{
    Student *studentToUpdate = binarySearch(section, 0, size-1, studentNumber);
    if (studentToUpdate == NULL) cout << "Student " << studentNumber << " not found. Grade not updated." << endl;
    else
    {
        if (!validateGrade(newGrade))
        {
            cout << "Invalid grade." << endl;
            return;
        }

        float oldGrade = studentToUpdate->getGrade();
        studentToUpdate->updateGrade(newGrade);
        calculateStats();
        if(studentToUpdate->getGrade() < minGrade) minGrade = studentToUpdate->getGrade();
        if(studentToUpdate->getGrade() > maxGrade) maxGrade = studentToUpdate->getGrade();
        cout << "Student " << studentNumber << " grade updated from " << oldGrade << " to " << studentToUpdate->getGrade() << "." << endl;
    }
}

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

void Section::printStudents()
{
    cout << "Student Number, Grade" << endl;
    cout << "---------------------" << endl;
    for(unsigned int i = 0; i < size; i++)
    {
        cout << section[i]->getStudentNumber() << ", " << section[i]->getGrade() << endl;
    }
}

void Section::printStats()
{
    cout << "Minimum Grade: " << minGrade << endl;
    cout << "Maximum Grade: " << maxGrade << endl;
    cout << "Mean: " << mean << endl;
    cout << "Standard Deviation: " << standardDeviation << endl;
}

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
