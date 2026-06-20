#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <set>

using namespace std;

/*
 * Prompts user for student info, then takes user input and places into
 * student constructs for later use.
 *
 * @param students  : Student*  - array of students to add data to
 */
void inputStudents(Student* students) {

    int i = 0;
    // set to check if user inputted ID has been used or not
    set<int> usedID;

    for (Student s : students) {
        cout << "Input information for student: " << i+1 << "\n";

        string tempName = "";
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
                if (tempMark < 0 || usedID.contains(tempMark)) { cout << "\nOops, that was not a valid mark, try again"; }
                cin.clear();
            } while (tempMark < 0 || tempMark > 100);
        }
        i++;
    }
}

/*
 * Calculates student total mark across 3 classes and the average (mean)
 *
 * @param s : Student& - reference to student calculate marks
 */
void calculateStats(Student& s) {

}

/*
 * Given a student, print out all relevant information about said student
 *
 * @param s : const Student& - reference to student to print
 */
static void printStudent(const Student& s) {
}

/*
 * Displays the array of students
 *
 * @param students  : Student*  - array of students to print
 * @param n         : int       - number of students to print
 */
void displayStudents(const Student* students, int n) {
}

/*
 * Iterates through student array and finds student with highest total
 *
 * @param students  : Student*  - array of students to iterate through
 * @param n         : int       - number of students
 */
void findHighestScorer(const Student* students, int n) {
}

/*
 * Saves all information of students inputted to a txt file
 *
 * @param students  : Studnet*      - Array of students to save
 * @param n         : int           - Number of students
 * @param filename  : const string  - filepath to txt file
 */
void saveToFile(const Student* students, int n, const string& filename) {
}

/*
 * Finds txt file and loads students into system
 *
 * @param filename : const string& - filepath to student txt file
 */
void loadFromFile(const string& filename) {
}

std::string marksToString(Student *student) {
}
