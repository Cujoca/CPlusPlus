#include "Subjects.h"

using namespace std;

/*
 * Returns the string representation of a Status enum value
 */
std::string statusToString(const Status status) {
    switch (status) {
        case PASS: return "PASS";
        case FAIL: return "FAIL";
        default:   return "N/A";
    }
}

/*
 * Returns the letter string representation of a Grade enum value
 */
std::string gradeToString(const Grade grade) {
    switch (grade) {
        case Grade::A: return "A";
        case Grade::B: return "B";
        case Grade::C: return "C";
        case Grade::D: return "D";
        case Grade::F: return "F";
        default:       return "N/A";
    }
}

/*
 * Converts a numeric mark to its corresponding letter Grade enum value
 */
Grade markToGrade(const int mark) {
    if (mark < 50) return Grade::F;
    if (mark < 60) return Grade::D;
    if (mark < 70) return Grade::C;
    if (mark < 80) return Grade::B;
    return Grade::A;
}
