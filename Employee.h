//
// Created by AndreiCojocaru on 2026-07-14.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <memory>
#include <string>
#include <vector>
using namespace std;

/*
 * Pure abstract interface for every kind of employee.
 * Holds no state and provides no implementation: derived classes supply the
 * data and override every member. Deletion through an Employee* is safe thanks
 * to the public virtual destructor.
 */
class Employee {
public:
    virtual ~Employee() = default;

    // pay / presentation
    virtual float calculatePay() const = 0;
    virtual void  display()      const = 0;

    // getters
    virtual float  getSalary() const = 0;
    virtual string getName()   const = 0;

    // setters
    virtual void setSalary(float s)          = 0;
    virtual void setName(const string& n)    = 0;

    // Compares two employees by their calculated pay. Provided as a basic default.
    // Since concrete classes calculate salary by themselves anyway, prob won't be overidden
    virtual bool operator<(const Employee& other) const {
        return calculatePay() > other.calculatePay();
    }
};

// The roster owns its employees; Employee is abstract, so it is stored by pointer
using EmployeeList = vector<unique_ptr<Employee>>;

// menu actions
void addEmployee            (EmployeeList& employees);
void displayEmployees       (const EmployeeList& employees);
void findHighestPaidEmployee(const EmployeeList& employees);

#endif //EMPLOYEE_H