#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * Prompts user for student info, then takes user input and places into
 * student constructs for later use.
 *
 * @param students  : Student*  - array of students to add data to
 * @param n         : int       - number of students to add
 */
void inputStudents(Student* students, int n) {
    // iterate n times to get n students
    for (int i = 0; i < n; i++) {
        cout << "\nEnter data for student " << (i + 1) << "\n";
        cout << "Enter ID: ";
        while (!(cin >> students[i].id));
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, students[i].name);
        for (int j = 0; j < 3; j++) {
            cout << "Enter marks for subject " << (j + 1) << ": ";
            while (!(cin >> students[i].marks[j]));
        }
        calculateStats(students[i]);
    }
}

/**
 * Calculates student total mark across 3 classes and the average (mean)
 *
 * @param s : Student& - reference to student calculate marks
 */
void calculateStats(Student& s) {
    s.total = s.marks[0] + s.marks[1] + s.marks[2];
    s.average = s.total / 3.0f;
}

/**
 * Given a student, print out all relevant information about said student
 *
 * @param s : const Student& - reference to student to print
 */
static void printStudent(const Student& s) {
    cout << defaultfloat << setprecision(4);
    cout << "ID: " << s.id << ", Name: " << s.name << "\n";
    cout << "Marks: " << s.marks[0] << " " << s.marks[1] << " " << s.marks[2] << "\n";
    cout << "Total: " << s.total << ", Average: " << s.average << "\n";
    cout << "Status: " << (s.average >= 50.0f ? "PASS" : "FAIL") << "\n";
}

/**
 * Displays the array of students
 *
 * @param students  : Student*  - array of students to print
 * @param n         : int       - number of students to print
 */
void displayStudents(const Student* students, int n) {
    cout << "\n--- Student Records ---\n";
    for (int i = 0; i < n; i++) {
        printStudent(students[i]);
        if (i < n - 1) cout << "\n";
    }
}

/**
 * Iterates through student array and finds student with highest total
 *
 * @param students  : Student*  - array of students to iterate through
 * @param n         : int       - number of students
 */
void findHighestScorer(const Student* students, int n) {
    int best = 0;
    for (int i = 1; i < n; i++) {
        if (students[i].total > students[best].total)
            best = i;
    }
    cout << "\nHighest Scorer:\n";
    printStudent(students[best]);
}

/**
 * Saves all information of students inputted to a txt file
 *
 * @param students  : Studnet*      - Array of students to save
 * @param n         : int           - Number of students
 * @param filename  : const string  - filepath to txt file
 */
void saveToFile(const Student* students, int n, const string& filename) {
    // no need to check if file exists since ofstream will create if not exist
    ofstream out(filename);
    out << n << "\n";
    // iterate through and save students
    for (int i = 0; i < n; i++) {
        out << students[i].id << "\n"
            << students[i].name << "\n"
            << students[i].marks[0] << " "
            << students[i].marks[1] << " "
            << students[i].marks[2] << "\n";
    }
    cout << "\nData saved to " << filename << "\n";
}

/**
 * Finds txt file and loads students into system
 *
 * @param filename : const string& - filepath to student txt file
 */
void loadFromFile(const string& filename) {
    // have to check if file exists
    ifstream in(filename);
    if (!in) {
        cout << "Error: could not open " << filename << "\n";
        return;
    }
    // first line of text file is number of students
    int n;
    in >> n;
    in.ignore();
    // temp student holder array for reading from file,
    // load student data into each holder index and run calculations
    Student* loaded = new Student[n];
    for (int i = 0; i < n; i++) {
        in >> loaded[i].id;
        in.ignore();
        getline(in, loaded[i].name);
        in >> loaded[i].marks[0] >> loaded[i].marks[1] >> loaded[i].marks[2];
        in.ignore();
        calculateStats(loaded[i]);
    }

    // iterate through and print students in holder array
    cout << "\nLoading data from file:\n";
    for (int i = 0; i < n; i++) {
        printStudent(loaded[i]);
        if (i < n - 1) cout << "\n";
    }
    // RAII
    delete[] loaded;
}
