//
// Created by andre on 7/14/2026.
//

#include "SalariedEmployee.h"
#include <iostream>
#include <iomanip>
#include <utility>
using namespace std;

SalariedEmployee::SalariedEmployee(string  name, const float salary, const float bonus)
    : name(std::move(name)), salary(salary), bonus(bonus) {}

float SalariedEmployee::calculatePay() const {
    return salary + bonus;
}

void SalariedEmployee::display() const {
    cout << fixed << setprecision(2);
    cout << "Salaried Employee: " << name << endl
         << "  Base:       " << salary << endl
         << "  Bonus:      " << bonus << endl
         << "  Total Pay:  " << calculatePay() << endl;
}