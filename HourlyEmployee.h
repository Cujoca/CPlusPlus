//
// Created by andre on 7/14/2026.
//

#ifndef LABS_HOURLYEMPLOYEE_H
#define LABS_HOURLYEMPLOYEE_H

#include "Employee.h"
#include <string>
using namespace std;

/*
 * An employee paid by the hour: pay = base salary + hours * rate.
 */
class HourlyEmployee : public Employee {
    string name;
    float  hours;
    float  rate;
    float  salary;   // derived pay: hours * rate

public:
    HourlyEmployee(string  name, float hours, float rate);
    ~HourlyEmployee() override = default;

    float  calculatePay() const override;
    void   display()      const override;

    float  getSalary() const override { return salary; }
    string getName()   const override { return name; }

    void setSalary(const float s) override { salary = s; }
    void setName(const string& n) override { name = n; }
};

#endif //LABS_HOURLYEMPLOYEE_H