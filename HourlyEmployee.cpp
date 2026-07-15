//
// Created by andre on 7/14/2026.
//

#include "HourlyEmployee.h"
#include <iostream>
#include <iomanip>
#include <utility>
using namespace std;

HourlyEmployee::HourlyEmployee(string  name, const float hours, const float rate)
    : name(std::move(name)), hours(hours), rate(rate), salary(hours*rate) {}

float HourlyEmployee::calculatePay() const {
    return hours * rate;
}

void HourlyEmployee::display() const {
    cout << fixed << setprecision(2);
    cout << "Hourly Employee: " << name << "\n"
         << "  Hours:      " << hours << "\n"
         << "  Rate:       " << rate << "\n"
         << "  Base:       " << salary << "\n"
         << "  Total Pay:  " << calculatePay() << "\n";
}