//
// Created by AndreiCojocaru on 2026-07-14.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

struct Employee {
    string name;
    float baseSalary;

    const virtual float calculatePay() = 0;
    const virtual void display() = 0;
    virtual ~Employee() {}
};




#endif //EMPLOYEE_H
