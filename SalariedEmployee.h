//
// Created by andre on 7/14/2026.
//

#ifndef LABS_SALARIEDEMPLOYEE_H
#define LABS_SALARIEDEMPLOYEE_H

#include "Employee.h"
#include <string>
using namespace std;

constexpr float MINIMUM_WAGE = 17.95f;

/*
 * A salaried employee that may or may not have a bonus: pay = base salary + bonus.
 */
class SalariedEmployee : public Employee {
    string name;
    float  salary;   // base salary
    float  bonus;

public:
    SalariedEmployee(string  name, float salary, float bonus);
    ~SalariedEmployee() override = default;

    float  calculatePay() const override;
    void   display()      const override;

    float  getSalary() const override { return salary; }
    string getName()   const override { return name; }

    void setSalary(const float s) override { salary = s; }
    void setName(const string& n) override { name = n; }
};

#endif //LABS_SALARIEDEMPLOYEE_H