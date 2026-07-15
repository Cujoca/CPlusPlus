//
// Created by AndreiCojocaru on 2026-07-15.
//

#include <iostream>
#include <string>
#include <sstream>
#include "Functional.h"
using namespace std;


string digits(const int x) {
    if (abs(x) < 10) return "Too small, only one digit";
    int temp = abs(x);
    string tempOut;

    while (temp > 9) {
        const int digit = temp % 10;
        tempOut += " " + to_string(digit);
        temp = temp / 10;
    }
    tempOut += " " + to_string(temp);
    return tempOut;
}

int main() {

    cout << "making a vector of some numbers:" << endl;

    vector<int> v;
    for (int i = 0; i < 10; i++) { v.push_back(i); }

    string temp = "";

    for (const auto i : v) { temp += ", " + to_string(i); }

    cout << "we now have a vector:" << endl
         << temp << endl;

    cout << "Now we're going to map it to a square function" << endl;

    vector<int> v2 = map(v, [](int x) { return x*x; });

    temp = "";

    for (const auto i : v2) { temp += ", " + to_string(i); }

    cout << temp << endl;

    cout << "Now I'm going to make a small little function which will print each digit individually" << endl;

    vector<string> yeehaw = map(v2, digits);

    temp = "";

    for (const auto i : yeehaw) { temp += ", " + (i); }

    cout << temp << endl;




}



