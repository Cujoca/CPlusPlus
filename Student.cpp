#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <set>

using namespace std;

/*
 * Function to intake student data from user and build them.
 *
 */
void inputStudents(const vector<Student>& students) {

    int i = 0;
    // set to check if user inputted ID has been used or not
    set<int> usedID;

    for (Student s : students) {
        cout << "Input information for student: " << i+1 << "\n";

        string tempName;
        // regex to ensure that the name inputted has first last with:
        //  - must be alpha only
        //  - must have at least one letter in first and one in last
        //  - must have no whitespace before or after names
        auto properName = regex("^[A-Za-z]+ [A-Za-z]+$");


        do {
            cout << "Name (first last): ";
            getline(cin, tempName);
            if (!regex_match(tempName, properName)) { cout << "\nOops, that was not a valid name, try again"; }
        } while (!regex_match(tempName, properName));
        cin.clear();

        int tempID = 0;

        // checks if id is positive or if it has been used already
        do {
            cout << "\nInput student ID: ";
            while (!(cin >> tempID));
            if (tempID < 0 || usedID.contains(tempID)) {
                cout << "\nOops, that student ID is not valid, please try again\n";
            }
        } while (tempID < 0 || usedID.contains(tempID));
        // place id into set for later checking
        usedID.insert(tempID);
        cin.clear();

        for (int j = 0; j < NUM_SUBJECTS; j++) {
            int tempMark = 0;

            do {
                cout << "\nInput mark for class " << j+1 << ": ";
                while (!(cin >> tempMark));
                if (tempMark < 0 || usedID.contains(tempMark)) {
                    cout << "\nOops, that was not a valid mark, try again";
                }
                cin.clear();
            } while (tempMark < 0 || tempMark > 100);
        }
        i++;
    }
}

/*
 * Calculates student total mark across 3 classes and the average (mean)
 * Then also sets the student's status based on the average.
 */
void calculateStats(Student& s) {
    float total = 0.0, average = 0.0;
    for (int i = 0; i < NUM_SUBJECTS; i++) { total += s.marks[i]; }
    average = total/NUM_SUBJECTS;
    // check for status and set student values
    if (average < 50) s.status = FAIL;
    else s.status = PASS;
    s.average = average;
}

/*
 * Given a student, print out all relevant information about said student
 *
 * @param s : const Student& - reference to student to print
 */
static void printStudent(const Student& s) {
    cout << "\n" << s.name << "\n";
    cout << "ID: " << s.id << "\n";
    cout << "Average: " << s.average << "\n";
    cout << "Status: " << statusStringify(s.status) << "\n";
    cout << "Marks: ";
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        cout << "Class "   << i+1  << ": "
             << s.marks[i] << ": " << gradeStringify(markToGrade(s.marks[i])) << " ";
    }
    cout << "\n";
}

/*
 * Displays the vector of students
 */
void displayStudents(const vector<Student>& students) {
    //iterator for loop
    int i = 0;
    for (auto s = students.begin(); s != students.end(); ++s, i++) {
        cout << "\nStudent #" << i << ": \n";
        printStudent(*s);
    }
}

/*
 * Iterates through student array and finds student with highest total
 */
void findHighestScorer(const vector<Student>& students) {
    float highest = 0.0;
    int highestInd = 0;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].total > highest) {
            highest = students[i].total;
            highestInd = i;
        }
    }
    cout << "\nHighest Scorer: \n";
    printStudent(students[highestInd]);
}

/*
 * Saves all information of students inputted to a txt file
 */
void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file;
    file.open(filename);
    for (const auto& s : students) {
        file << s.name << " " << s.id << " ";
        for (const float mark : s.marks) {
            file << mark << " ";
        }
        file << "\n";
    }
    file.close();
}

/*
 * Finds txt file and loads students into system
 */
void loadFromFile(const string& filename) {
    ifstream file;
    file.open(filename);
    vector<Student> students;
    string tempName;
    int tempID;
    float tempMark;
    while (file >> tempName >> tempID) {
        Student s;
        s.name = tempName;
        s.id = tempID;
    }
}