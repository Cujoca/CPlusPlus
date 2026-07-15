#include <iostream>
#include "Employee.h"
#include "Student.h"

using namespace std;

/*
 * Entry point. Owns the student array via unique_ptr and drives the menu loop.
 * Each iteration displays the menu, reads a validated choice, and dispatches
 * to the corresponding function. Exits when the user selects option 11.
 * Once the student menu exits, the employee menu runs on the same pattern.
 */
int main() {
    auto students = unique_ptr<Student[]>{};
    int count = 0;

    int choice;
    do {
        cout << endl << "===== Enhanced Student Management System =====" << endl;
        cout << " 1. Add student records" << endl;
        cout << " 2. Display all students" << endl;
        cout << " 3. Search student by ID" << endl;
        cout << " 4. Edit student record" << endl;
        cout << " 5. Delete student record" << endl;
        cout << " 6. Find highest scoring student" << endl;
        cout << " 7. Display class summary" << endl;
        cout << " 8. Sort students" << endl;
        cout << " 9. Save records to file" << endl;
        cout << "10. Load records from file" << endl;
        cout << "11. Exit" << endl;

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
                          << Student::getTotalCreated() << endl; break;
        }
    } while (choice != 11);

    EmployeeList employees;

    do {
        cout << endl << "===== Employee Management System =====" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Display all employees" << endl;
        cout << "3. Find highest paid employee" << endl;
        cout << "4. Exit" << endl;

        choice = getValidatedInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addEmployee            (employees); break;
            case 2: displayEmployees       (employees); break;
            case 3: findHighestPaidEmployee(employees); break;
            case 4: cout << "Exiting." << endl; break;
        }
    } while (choice != 4);

    return 0;
}
