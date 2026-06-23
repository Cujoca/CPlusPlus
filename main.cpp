#include <iostream>
#include "Student.h"

using namespace std;

/*
 * Entry point. Owns the student array via unique_ptr and drives the menu loop.
 * Each iteration displays the menu, reads a validated choice, and dispatches
 * to the corresponding function. Exits when the user selects option 11.
 */
int main() {
    auto students = unique_ptr<Student[]>{};
    int count = 0;

    int choice;
    do {
        cout << "\n===== Enhanced Student Management System =====\n";
        cout << " 1. Add student records\n";
        cout << " 2. Display all students\n";
        cout << " 3. Search student by ID\n";
        cout << " 4. Edit student record\n";
        cout << " 5. Delete student record\n";
        cout << " 6. Find highest scoring student\n";
        cout << " 7. Display class summary\n";
        cout << " 8. Sort students\n";
        cout << " 9. Save records to file\n";
        cout << "10. Load records from file\n";
        cout << "11. Exit\n";

        choice = getValidatedInt("Enter your choice: ", 1, 11);

        switch (choice) {
            case 1:  addStudents        (students, count); break;
            case 2:  displayStudents    (students, count); break;
            case 3:  searchStudentById  (students, count); break;
            case 4:  editStudent        (students, count); break;
            case 5:  deleteStudent      (students, count); break;
            case 6:  findHighestScorer  (students, count); break;
            case 7:  displayClassSummary(students, count); break;
            case 8:  sortStudents       (students, count); break;
            case 9:  saveToFile         (students, count); break;
            case 10: loadFromFile       (students, count); break;
            case 11: cout << "Exiting. Total students created: "
                          << Student::totalCreated << "\n"; break;
        }
    } while (choice != 11);

    return 0;
}
