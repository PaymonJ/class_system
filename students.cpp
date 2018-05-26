#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Student {
    public:
        Student(std::string studentNo, unsigned int percent)
        {
            studentNumber = studentNo;
            grade = percent;
        };
        std::string getStudentNumber() { return studentNumber; }
        unsigned int getGrade() { return grade; }
    private:
        std::string studentNumber;
        unsigned int grade;
};

class Section {
    public:
        Section(){size = 0;};
        void addStudent(std::string studentNumber, unsigned int grade)
        {
            Student *newStudent = new Student(studentNumber, grade);
            if(size == 0)
            {
                section[0] = newStudent;
                minGrade = newStudent->getGrade();
                maxGrade = newStudent->getGrade();
            }
            else
            {
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
            calculateMean();
            calculateSD();
        };
        void printStudents()
        {
            cout << "Student Number, Grade" << endl;
            cout << "---------------------" << endl;
            for(unsigned int i = 0; i < size; i++)
            {
                cout << section[i]->getStudentNumber() << ", " << section[i]->getGrade() << endl;
            }
        };
        void calculateMean()
        {
            float sum = 0;
            for(unsigned int i = 0; i < size; i++)
            {
                sum += section[i]->getGrade();
            }
            mean = sum/size;
        };
        void calculateSD()
        {
            float sum = 0.0;
            for(unsigned int i = 0; i < size; i++)
            {
                sum += pow((section[i]->getGrade() - mean), 2);
            }
            standardDeviation = sqrt(sum/size);
        };
        void printStats();
    private:
        Student* section[100];
        unsigned int size;
        unsigned int minGrade;
        unsigned int maxGrade;
        float mean;
        float standardDeviation;
};

void Section::printStats()
{
    cout << "Minimum Grade: " << minGrade << endl;
    cout << "Maximum Grade: " << maxGrade << endl;
    cout << "Mean: " << mean << endl;
    cout << "Standard Deviation: " << standardDeviation << endl;
}

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
