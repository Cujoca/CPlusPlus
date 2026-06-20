//
// Created by AndreiCojocaru on 2026-06-18.
//

#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <tuple>

constexpr float PASS_THRESHOLD = 50.0;

enum Status {PASS, FAIL};
enum class Grade {A, B, C, D, F};

std::string statusStringify(Status status);
std::string gradeStringify(Grade grade);
Grade markToGrade(int mark);

#endif //CLASS_H
