#ifndef STUDENT_H
#define STUDENT_H

#include "Subjects.h"
#include "Helper.h"
#include <string>
#include <memory>
using namespace std;

constexpr int SUBJECT_COUNT = 3;
constexpr int MAX_STUDENTS  = 1000;
constexpr int MAX_NUM = 9999;
constexpr int MIN_NUM = 1;

extern volatile bool fileWriteInProgress;

/*
 * Represents a single student record, including identity, marks, and derived stats.
 * totalCreated tracks how many students have been added across the program's lifetime.
 */
class Student {
    string name;
    int   id;
    float marks[SUBJECT_COUNT];
    float total;
    float average;
    Status status;
    Grade  grade;
    static int totalCreated;

public:
    Student() : id(0), marks{}, total(0.0f), average(0.0f), status(FAIL), grade(Grade::F) {}

    // getters
    int           getId()        const { return id; }
    const string& getName()      const { return name; }
    float         getMark(const int j) const { return marks[j]; }
    float         getTotal()     const { return total; }
    float         getAverage()   const { return average; }
    Status        getStatus()    const { return status; }
    Grade         getGrade()     const { return grade; }
    static int    getTotalCreated()    { return totalCreated; }

    // setters
    void setName(const string& n)      { name = n; }
    void setId(const int i)                        { id = i; }
    void setMark(const int j, const float val)     { marks[j] = val; }
    static void addTotalCreated(const int n)       { totalCreated += n; }

    // per-student operations (operate on *this*, direct member access)
    bool   operator<       (const Student& rhs) const;
    float  calculateTotal  () const;
    float  calculateAverage() const;
    Status determineStatus () const;
    Grade  determineGrade  () const;
    void   recalculate     ();
};


// student validation / utilities (free functions, use public getters/setters)
bool isDuplicateId(const Student* students, int count, int id);
int  findStudentIndexById(const unique_ptr<Student[]>& students, int count, int id);
void copyStudent(Student& dst, const Student& src);

// table rendering
void printTableHeader();
void printStudentRow(const Student& s);


// menu functions
void addStudents         (unique_ptr<Student[]>& students, int& count);
void displayStudents     (const std::unique_ptr<Student[]>& students, int count);
void searchStudentById   (const std::unique_ptr<Student[]>& students, int count);
void editStudent         (unique_ptr<Student[]>& students, int count);
void deleteStudent       (unique_ptr<Student[]>& students, int& count);
void findHighestScorer   (const std::unique_ptr<Student[]>& students, int count);
void displayClassSummary (const std::unique_ptr<Student[]>& students, int count);
void sortStudents        (unique_ptr<Student[]>& students, int count);
void saveToFile          (const std::unique_ptr<Student[]>& students, int count);
void loadFromFile        (unique_ptr<Student[]>& students, int& count);

#endif
