#include <iostream>
#include <ctime>
#include <string>
#include "Student.h"
using namespace std;

class Date {
    unsigned short day;
    unsigned short month;
    long long year;
public:
    Date() : Date(23, 12, 2023) {}

    Date(unsigned short day, unsigned short month, long long year)
    {
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }
    Date(unsigned short day, unsigned short month) : Date(day, month, 2005) {}


    void PrintDate() const
    {
        cout << day << "." << month << "." << year << "\n";
    }
    void SetDay(unsigned short day)
    {
        if (day == 0 || day > 31) throw "ERROR!!! The day must be from 0 to 31 !!!";
        this->day = day;
    }
    unsigned short GetDay() const
    {
        return day;
    }
    void SetMonth(unsigned short month)
    {
        if (month == 0 || month > 12) throw "ERROR!!! The day must be from 1 to 12 !!!";
        this->month = month;
    }
    unsigned short GetMonth() const
    {
        return month;
    }
    void SetYear(long long year)
    {
        this->year = year;
    }
    long long GetYear() const
    {
        return year;
    }

    operator string()
    {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }
};

class Group {
private:
    int studentCount = 0;
    Student** students = nullptr;
    string groupName;
    string groupSpecialization;
    int classNumber = 2;
    int passingGrade = 7;
public:

    Group() : Group("P26", "Prog") {}

    Group(string groupName, string groupSpecialization)
    {
        //cout << "GROUP CONSTRUCTOR" << "\n";
        SetGroupName(groupName);
        SetGroupSpecialization(groupSpecialization);
    }

    Group(const Group& original)
    {
        //cout << "COPY GROUP" << "\n";
        this->groupName = original.groupName;
        this->groupSpecialization = original.groupSpecialization;
        this->students = new Student * [original.studentCount];
        for (int i = 0; i < studentCount; i++)
        {
            this->students[i] = new Student(*original.students[i]);
        }
    }

    void ShowGroup()
    {
        
        for (int i = 0; i < studentCount; i++)
        {
            cout << i << " " << &students[i] << "\n";
        }
    }

    void AddStudent(Student& student)
    {
        //cout << "Add Student \n";
        Student** temp = new Student * [studentCount + 1];
        for (int i = 0; i < studentCount; i++)
        {
            temp[i] = students[i];
        }
        temp[studentCount] = new Student(student);
        studentCount++;
        delete[] students;
        students = temp;
    }

    void MergeGroup(Group& g2)
    {
        int otherStudentCount = g2.studentCount;

        Student** temp = new Student * [studentCount + otherStudentCount];
        for (int i = 0; i < studentCount; i++)
        {
            temp[i] = students[i];
        }

        for (int i = 0; i < otherStudentCount; i++)
        {
            temp[studentCount + i] = new Student(*g2.students[i]);
        }
        studentCount += otherStudentCount;
        delete[] students;
        students = temp;
    }

    void TransferStudent(int index, Group& g2)
    {
        if (index >= 0 && index < studentCount)
        {
            Student* transfer = students[index];
            Student** temp = new Student * [studentCount - 1];
            int tempIndex = 0;
            for (int i = 0; i < studentCount; i++)
            {
                if (i != index)
                {
                    temp[tempIndex++] = students[i];
                }
            }
            delete students[index];
            delete[] students;
            students = temp;
            studentCount--;
            g2.AddStudent(*transfer);
        }
    }

    void ExpelStudents()
    {
        Student** temp = new Student * [studentCount];
        int index = 0;

        for (int i = 0; i < studentCount; ++i)
        {
            bool passedExam = false;

            for (int j = 0; j < students[i]->GetExamRatesCount(1); ++j)
            {
                if (students[i]->GetExamRatesCount(j) >= passingGrade)
                {
                    passedExam = true;
                    break;
                }
            }

            if (!passedExam)
            {
                cout << "Expelling student " << students[i]->GetName() << " for failing exam.\n";
                delete students[i];
            }
            else
            {
                temp[index++] = students[i];
            }
        }

        delete[] students;
        students = temp;
        studentCount = index;
    }

    void ExpelBadStudent()
    {
        if (studentCount == 0)
        {
            cout << "No students in the group to expel.\n";
            return;
        }

        int minIndex = 0;
        double minAverageGrade = students[0]->CalculateAverageGrade();
        for (int i = 1; i < studentCount; ++i)
        {
            double averageGrade = students[i]->CalculateAverageGrade();
            if (averageGrade < minAverageGrade)
            {
                minIndex = i;
                minAverageGrade = averageGrade;
            }
        }

        cout << "Expelling the least performing student " << students[minIndex]->GetName() << "\n";
        delete students[minIndex];

        for (int i = minIndex; i < studentCount - 1; ++i)
        {
            students[i] = students[i + 1];
        }
        studentCount--;
    }

    void SetGroupName(string groupName)
    {
        this->groupName = groupName;
    }

    string GetGroupName() const
    {
        return groupName;
    }

    void SetGroupSpecialization(string groupSpecialization)
    {
        this->groupSpecialization = groupSpecialization;
    }

    string GetGroupSpecialization() const
    {
        return groupSpecialization;
    }

    void SetPassingGrade(int passingGrade)
    {
        this->passingGrade = passingGrade;
    }

    int GetPassingGrade() const
    {
        return passingGrade;
    }


    ~Group() {
        for (int i = 0; i < studentCount; i++)
        {
            delete students[i];
        }
        delete[] students;
    }
};

istream& operator >> (const istream& i, Student s)
{
    string answer;
    cout << "Какая у тебя фамилия: ";
    cin >> answer;
    s.SetSurname(answer);
    cout << "Как тебя зовут: ";
    cin >> answer;
    s.SetName(answer);
    cout << "Какое у тебя отчество: ";
    cin >> answer;
    s.SetMiddlName(answer);
    return cin;
}

ostream& operator << (ostream& o, Student s)
{
    s.PrintStudent();
    return cout;
}

int main()
{
    Student s;
    Student s2;
    Student s3;

    s.AddExam(8);
    s2.AddExam(7);
    s3.AddExam(9);
    s.AddHomeWork(6);
    s2.AddHomeWork(6);
    s3.AddHomeWork(8);

    Group g;
    Group g2;
    g.AddStudent(s);
    g.AddStudent(s2);
    //g.TransferStudent(1, g2);
    //g.ExpelStudents();
    g.ExpelBadStudent();
    g.ShowGroup();

    g2.AddStudent(s);
    g2.AddStudent(s2);
    g2.ShowGroup();
}