#ifndef STUDENT_H
#define STUDENT_H

#include "Subjects.h"
#include <string>

constexpr int MAX_STUDENTS = 1000;
constexpr int NUM_SUBJECTS = 3;

struct Student {
    std::string name;
    int id;
    float marks[NUM_SUBJECTS];
    float total;
    float average;
    Status status;
};

void inputStudents(Student* students);
std::string marksToString(Student* student);
void calculateStats(Student& s);
void displayStudents(const Student* students, int n);
void findHighestScorer(const Student* students, int n);
void saveToFile(const Student* students, int n, const std::string& filename);
void loadFromFile(const std::string& filename);

#endif
