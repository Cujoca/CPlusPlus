//
// Created by andre on 7/14/2026.
//

#include "CommissionEmployee.h"
#include <iostream>
#include <iomanip>
#include <utility>
using namespace std;

CommissionEmployee::CommissionEmployee(string  name, const float salary, const float sales, const float rate)
    : name(std::move(name)), salary(salary), sales(sales), rate(rate) {}

float CommissionEmployee::calculatePay() const { return salary + (sales * rate); }

void CommissionEmployee::display() const {
    cout << fixed << setprecision(2);
    cout << "Commission Employee: " << name << endl
         << "  Sales:      " << sales << endl
         << "  Rate:       " << rate << endl
         << "  Base:       " << salary << endl
         << "  Total Pay:  " << calculatePay() << endl;
}