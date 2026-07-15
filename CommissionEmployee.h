//
// Created by andre on 7/14/2026.
//

#ifndef LABS_COMMISSIONEMPLOYEE_H
#define LABS_COMMISSIONEMPLOYEE_H

#include "Employee.h"
#include <string>
using namespace std;

/*
 * An employee paid on commission: pay = base salary + sales * rate.
 */
class CommissionEmployee : public Employee {
    string name;
    float  salary;   // base salary
    float  sales;
    float  rate;

public:
    CommissionEmployee(string  name, float salary, float sales, float rate);
    ~CommissionEmployee() override = default;

    float  calculatePay() const override;
    void   display()      const override;

    float  getSalary() const override { return salary; }
    string getName()   const override { return name; }

    void setSalary(const float s) override { salary = s; }
    void setName(const string& n) override { name = n; }
};


#endif //LABS_COMMISSIONEMPLOYEE_H