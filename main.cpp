#include <iostream>
#include <vector>

#include "Student.h"

using namespace std;

int main() {
    cout << "Enter number of students: ";

    int n = 0;
    // keep looping until user inputs valid number of students
    while (n < 1 || n > MAX_STUDENTS) { while (!(cin >> n)); }

    //auto* students = new Student[n];
    const vector<Student> students(n);

    inputStudents       (students);
    displayStudents     (students);
    findHighestScorer   (students);
    saveToFile          (students, "students.txt");
    loadFromFile        ("students.txt");

    // no need to destroy vector of students since is on stack and destructor is called automatically

    return 0;
}
