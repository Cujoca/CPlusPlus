#include <iostream>
#include "Student.h"

using namespace std;

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student* students = new Student[n];

    inputStudents(students, n);
    displayStudents(students, n);
    findHighestScorer(students, n);
    saveToFile(students, n, "students.txt");
    loadFromFile("students.txt");

    delete[] students;
    return 0;
}
