#ifndef STUDENT_H
#define STUDENT_H

#include "Subjects.h"
#include <string>
#include <vector>

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

void inputStudents          (const std::vector<Student>& students);
void calculateStats         (Student& s);
void displayStudents        (const std::vector<Student>& students);
void findHighestScorer      (const std::vector<Student>& students);
void saveToFile             (const std::vector<Student>& students, const std::string& filename);
void loadFromFile           (const std::string& filename);

#endif
