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
    cout << "Salaried Employee: " << name << "\n"
         << "  Base:       " << salary << "\n"
         << "  Bonus:      " << bonus << "\n"
         << "  Total Pay:  " << calculatePay() << "\n";
}