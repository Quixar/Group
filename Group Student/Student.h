#pragma once
#include <iostream>
using namespace std;

class Student {
    string surname;          /// Фамилия студента
    string name;             /// Имя студента
    string middlename;       /// Отчество студента
    string adress;           /// Адрес студента
    string phonenumber;      /// Номер телефона студента
    unsigned int countpractic = 0;    /// Количество оценок за практику
    unsigned int counthomework = 0;   /// Количество оценок за домашние задания
    unsigned int countexam = 0;       /// Количество оценок за экзамены
    int* grade_of_practic = nullptr;  /// Массив оценок за практику
    int* grade_of_homework = nullptr; /// Массив оценок за домашние задания
    int* grade_of_exam = nullptr;     /// Массив оценок за экзамены

public:
    /// Конструктор для копирования студента
    Student(const Student& original);

    /// Конструктор по умолчанию
    Student();

    /// Конструктор с указанием значений
    Student(string surname, string name, string middlname, string adress, string phonenumber);

    /// Конструктор с указанием значений и номера телефона по умолчанию
    Student(string surname, string name, string middlname, string adress);

    /// Деструктор
    ~Student();

    /// Вывод информации о студенте
    void PrintStudent() const;

    /// Добавление оценки за практику
    void AddPractic(int newcountry);

    /// Вывод оценок за практику
    void PrintPractic() const;

    /// Получение оценки за практику по индексу
    int GePracticRatesCount(unsigned int index) const;

    /// Добавление оценки за домашние задания
    void AddHomeWork(int newcountry);

    /// Рассчитывает средний балл
    double CalculateAverageGrade() const;

    /// Вывод оценок за домашние задания
    void PrintHomeWork() const;

    /// Получение оценки за домашние задания по индексу
    int GetHomeWorkRatesCount(unsigned int index) const;

    /// Добавление оценки за экзамен
    void AddExam(int newcountry);

    /// Вывод оценок за экзамены
    void PrintExam() const;

    /// Получение оценки за экзамен по индексу
    int GetExamRatesCount(unsigned int index) const;

    /// Установка фамилии студента
    void SetSurname(string surname);

    /// Получение фамилии студента
    string GetSurname() const;

    /// Установка имени студента
    void SetName(string name);

    /// Получение имени студента
    string GetName() const;

    /// Установка отчества студента
    void SetMiddlName(string middlname);

    /// Получение отчества студента
    string GetMiddlName() const;

    /// Установка адреса студента
    void SetAdress(string adress);

    /// Получение адреса студента
    string GetAdress() const;

    /// Установка номера телефона студента
    void SetPhone(string phonenumber);

    /// Получение номера телефона студента
    string GetPhone() const;
};
