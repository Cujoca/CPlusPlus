#include <iostream>
#include "Student.h"

using namespace std;

int main() {
    cout << "Enter number of students: ";

    int n = 0;
    // keep looping until user inputs valid number of students
    while (n < 1 || n > MAX_STUDENTS) { while (!(cin >> n)); }

    auto* students = new Student[n];

    inputStudents(students);
    displayStudents(students, n);
    findHighestScorer(students, n);
    saveToFile(students, n, "students.txt");
    loadFromFile("students.txt");

    delete[] students;
    return 0;
}
