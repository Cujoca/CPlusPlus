//
// Created by AndreiCojocaru on 2026-07-14.
//

#include "Employee.h"
#include "CommissionEmployee.h"
#include "HourlyEmployee.h"
#include "SalariedEmployee.h"
#include "Helper.h"
#include <iostream>
#include <iomanip>
using namespace std;

constexpr float MAX_MONEY = 1000000.0f;

/*
 * Prompts for an employee type, then for only the fields that type needs, and
 * appends the new employee to the roster.
 */
void addEmployee(EmployeeList& employees) {
    cout << "\n--- Add Employee ---\n";
    cout << "1. Salaried\n";
    cout << "2. Hourly\n";
    cout << "3. Commission\n";

    const int type = getValidatedInt("Select employee type: ", 1, 3);
    const string name = getValidatedName("Enter name: ");

    switch (type) {
        case 1: {
            const float salary = getValidatedFloat("Enter base salary: ", 0.0f, MAX_MONEY);
            const float bonus  = getValidatedFloat("Enter bonus: ",       0.0f, MAX_MONEY);
            employees.push_back(make_unique<SalariedEmployee>(name, salary, bonus));
            break;
        }
        case 2: {
            const float hours = getValidatedFloat("Enter hours worked: ", 0.0f, 168.0f);
            const float rate  = getValidatedWage("Enter hourly rate: ");
            employees.push_back(make_unique<HourlyEmployee>(name, hours, rate));
            break;
        }
        case 3: {
            const float salary = getValidatedFloat("Enter base salary: ",  0.0f, MAX_MONEY);
            const float sales  = getValidatedFloat("Enter total sales: ",  0.0f, MAX_MONEY);
            const float rate   = getValidatedFloat("Enter commission rate (0-1): ", 0.0f, 1.0f);
            employees.push_back(make_unique<CommissionEmployee>(name, salary, sales, rate));
            break;
        }
        default: break;
    }

    cout << "Employee added successfully.\n";
}

/*
 * Displays every employee on the roster using each one's own display() override.
 */
void displayEmployees(const EmployeeList& employees) {
    cout << "\n--- All Employees ---\n";
    if (employees.empty()) {
        cout << "No employees to display.\n";
        return;
    }

    int index = 1;
    for (const auto& employee : employees) {
        cout << "\n[" << index++ << "] ";
        employee->display();
    }
}

/*
 * Finds and displays the employee with the greatest calculated pay.
 * Ties are broken by whichever was added first.
 */
void findHighestPaidEmployee(const EmployeeList& employees) {
    cout << "\n--- Highest Paid Employee ---\n";
    if (employees.empty()) {
        cout << "No employees on record.\n";
        return;
    }

    const Employee* highest = employees.front().get();
    for (const auto& employee : employees) {
        if (employee->comparePay(*highest)) highest = employee.get();
    }

    highest->display();
}