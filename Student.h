#ifndef STUDENT_H
#define STUDENT_H

#include <string>

struct Student {
    std::string name;
    int id;
    float marks[3];
    float total;
    float average;
};

void inputStudents(Student* students, int n);
void calculateStats(Student& s);
void displayStudents(const Student* students, int n);
void findHighestScorer(const Student* students, int n);
void saveToFile(const Student* students, int n, const std::string& filename);
void loadFromFile(const std::string& filename);

#endif
