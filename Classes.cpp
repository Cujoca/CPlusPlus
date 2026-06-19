//
// Created by Andrei Cojocaru on 2026-06-18.
//

#include "Classes.h"

using namespace std;

/**
 * Given an enum Status, return string for output
 *
 * @param status : Status - enum to stringify
 * @return
 */
std::string statusStringify(const Status status) {
    switch (status) {
        case PASS: { return "Pass"; }
        case FAIL: { return "Fail"; }
        default:   { return "N/A"; }
    }
}

/**
 * Given an enum Grade, return string for output
 *
 * @param grade : Grade - enum to stringify
 * @return
 */
std::string gradeStringify(const Grade grade) {
    switch (grade) {
        case Grade::A: { return "A"; }
        case Grade::B: { return "B"; }
        case Grade::C: { return "C"; }
        case Grade::D: { return "D"; }
        case Grade::F: { return "F"; }
        default: {return "N/A";}
    }
}

/**
 * Given a class mark, return the associated letter grade.
 *
 * @param mark : int - class mark
 * @return : Grade - the appropriate letter grade
 */
Grade markToGrade(const int mark) {
    if (mark < 50) return Grade::F;
    if (mark < 60) return Grade::D;
    if (mark < 70) return Grade::C;
    if (mark < 80) return Grade::B;
    return Grade::A;
}

/**
 *  Returns a tuple of both members of Class stringified.
 *
 * @return : std::tuple<std::string, std::string> - the tuple of strings
 */
tuple<string, string> Class::stringify() const {
    return make_tuple(to_string(this->mark), gradeStringify(this->letter));
}

/**
 * Constructor for Class, needs init list since both members are const
 *
 * @param mark : int - mark for the class
 */
Class::Class (const int mark): mark(mark), letter(markToGrade(mark)) {}

int Class::getMark() const { return this->mark; }

