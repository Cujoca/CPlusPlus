#ifndef CLASS_H
#define CLASS_H
#include <string>

constexpr float PASS_THRESHOLD = 50.0f;

enum Status { FAIL, PASS };

enum class Grade { A, B, C, D, F };

std::string statusToString(Status status);
std::string gradeToString(Grade grade);
Grade       markToGrade(int mark);

#endif
