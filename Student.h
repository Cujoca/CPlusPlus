#ifndef STUDENT_H
#define STUDENT_H

#include "Subjects.h"
#include "Helper.h"
#include <string>
#include <memory>

constexpr int SUBJECT_COUNT = 3;
constexpr int MAX_STUDENTS  = 1000;
constexpr int MAX_NUM = 9999;
constexpr int MIN_NUM = 1;

extern volatile bool fileWriteInProgress;

/*
 * Represents a single student record, including identity, marks, and derived stats.
 * totalCreated tracks how many students have been added across the program's lifetime.
 */
struct Student {
    std::string name;
    int   id;
    float marks[SUBJECT_COUNT]; // raw subject marks
    float total;                // sum of all marks
    float average;              // mean across subjects
    Status status;              // PASS or FAIL based on average
    Grade  grade;               // letter grade based on average
    static int totalCreated;    // counts total students ever added

    Student() : id(0), marks{}, total(0.0f), average(0.0f), status(FAIL), grade(Grade::F) {}
};

// student validation
bool isDuplicateId(const Student* students, int count, int id);

// student utilities
int  findStudentIndexById(const std::unique_ptr<Student[]>& students, int count, int id);
void copyStudent(Student& destination, const Student& source);

// calculation helpers
float  calculateTotal    (const Student& student);
float  calculateAverage  (float total);
Status determineStatus   (float average);
Grade  determineGrade    (float average);
void   recalculateStudent(Student& student);

// menu Functions
void addStudents        (std::unique_ptr<Student[]>& students, int& count);
void displayStudents    (const std::unique_ptr<Student[]>& students, int count);
void searchStudentById  (const std::unique_ptr<Student[]>& students, int count);
void editStudent        (std::unique_ptr<Student[]>& students, int count);
void deleteStudent      (std::unique_ptr<Student[]>& students, int& count);
void findHighestScorer  (const std::unique_ptr<Student[]>& students, int count);
void displayClassSummary(const std::unique_ptr<Student[]>& students, int count);
void sortStudents       (std::unique_ptr<Student[]>& students, int count);
void saveToFile         (const std::unique_ptr<Student[]>& students, int count);
void loadFromFile       (std::unique_ptr<Student[]>& students, int& count);

#endif
