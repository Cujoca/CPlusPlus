//
// Created by AndreiCojocaru on 2026-06-18.
//

#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <tuple>

constexpr int NUMBER_SUBJECTS = 3;

enum Status {PASS, FAIL};
enum class Grade {A, B, C, D, F};

class Class {
    const int mark;
    const Grade letter;

public:
    explicit Class(int mark);
    int getMark() const;
    std::tuple<std::string, std::string> stringify() const;
    ~Class();
};

std::string statusStringify(Status status);
std::string gradeStringify(Grade grade);
Grade markToGrade(int mark);

#endif //CLASS_H
