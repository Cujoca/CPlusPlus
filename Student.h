#ifndef STUDENT_H
#define STUDENT_H

#include "Classes.h"
#include <string>

struct Student {
    std::string name;
    int id;
    Class* marks[NUMBER_SUBJECTS];
    float total;
    float average;
    Status status;
};

void inputStudents(Student* students, int n);
void calculateStats(Student& s);
void displayStudents(const Student* students, int n);
void findHighestScorer(const Student* students, int n);
void saveToFile(const Student* students, int n, const std::string& filename);
void loadFromFile(const std::string& filename);

#endif
