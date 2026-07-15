#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <span>
#include <vector>
#include <set>

#include "Functional.h"

using namespace std;

// definitions for the Student static counter and the volatile file-write flag
int Student::totalCreated = 0;
volatile bool fileWriteInProgress = false;

/*
 * Returns true if the given ID is already present in the student array
 */
bool isDuplicateId(const Student* students, const int count, const int id) {
    // poopy array iterator, has to check whole array every time.
    // should probably change to a set but I'm lazy
    for (int i = 0; i < count; i++) {
        if (students[i].getId() == id) return true;
    }
    return false;
}

/*
 * Searches the student array for a matching ID using iterator-based traversal.
 * Returns the index of the student, or -1 if not found.
 */
int findStudentIndexById(const unique_ptr<Student[]>& students, const int count, const int id) {
    const Student* begin = students.get();
    const Student* end   = begin + count;
    auto it = find_if(begin, end, [id](const Student& s) { return s.getId() == id; });
    if (it == end) return -1;
    return static_cast<int>(it - begin);
}

/*
 * Copies all fields from one Student struct to another
 */
void copyStudent(Student& dst, const Student& src) {
    dst.setName(src.getName());
    dst.setId(src.getId());

    for (int i = 0; i < SUBJECT_COUNT; i++) dst.setMark(i, src.getMark(i));

    dst.recalculate();
}

/*
 * Compares left student to right student by average
 * left average less than right
 */
bool Student::operator< ( const Student& rhs) const {
    if (average < rhs.average) return true;
    return false;
}

/*
 * Sums all subject marks for the given student
 */
float Student::calculateTotal() const {
    float total = 0.0f;
    for (int i = 0; i < SUBJECT_COUNT; i++) total += marks[i];
    return total;
}

/*
 * Computes the average mark from the total across all subjects.
 * Uses static_cast to avoid integer division.
 */
float Student::calculateAverage() const {
    return total / static_cast<float>(SUBJECT_COUNT);
}

/*
 * Checks if student's average is above or below pass threshold
 */
Status Student::determineStatus() const {
    return (average >= PASS_THRESHOLD) ? PASS : FAIL;
}

/*
 * Assigns a letter grade based on the average mark:
 */
Grade Student::determineGrade() const {
    if (average >= 80.0f) return Grade::A;
    if (average >= 70.0f) return Grade::B;
    if (average >= 60.0f) return Grade::C;
    if (average >= 50.0f) return Grade::D;
    return Grade::F;
}

/*
 * Recalculates and updates the total, average, status, and grade for a student.
 * Called whenever a student's marks are changed.
 */
void Student::recalculate() {
    total   = calculateTotal();
    average = calculateAverage();   // uses the just-updated member total
    status  = determineStatus();
    grade   = determineGrade();
}

/*
 * Prints the column header row and separator line for the student table
 */
void printTableHeader() {
    cout << left  << setw(6)  << "ID"
         << setw(20) << "Name"
         << right << setw(8)  << "M1"
                  << setw(8)  << "M2"
                  << setw(8)  << "M3"
                  << setw(10) << "Total"
                  << setw(8)  << "Avg"
                  << setw(7)  << "Grade"
                  << setw(8)  << "Status" << endl;
    cout << string(83, '-') << endl;
}

/*
 * Prints a single student as one formatted row in the table
 */
void printStudentRow(const Student& s) {
    cout << fixed << setprecision(2);
    cout << left  << setw(6)  << s.getId()
         << setw(20) << s.getName()
         << right << setw(8)  << s.getMark(0)
                  << setw(8)  << s.getMark(1)
                  << setw(8)  << s.getMark(2)
                  << setw(10) << s.getTotal()
                  << setw(8)  << s.getAverage()
                  << setw(7)  << gradeToString(s.getGrade())
                  << setw(8)  << statusToString(s.getStatus()) << endl;
}

/*
 * Prompts the user to enter one or more new students and appends them to the array.
 * Allocates a new unique_ptr array large enough for existing and new records,
 * copies existing students (index-based), then collects input for each new entry.
 */
void addStudents(unique_ptr<Student[]>& students, int& count) {
    const int maxNew = MAX_STUDENTS - count;
    // check if limit reached and update count for new students if not
    if (maxNew <= 0) {
        cout << "Maximum student limit (" << MAX_STUDENTS << ") reached." << endl;
        return;
    }
    const int newCount = getValidatedInt("Enter number of students to add: ", 1, maxNew);

    // allocate new array with space for new students
    auto newStudents = make_unique<Student[]>(count + newCount);

    // index-based loop: copy existing students into the expanded array
    for (int i = 0; i < count; i++) {
        copyStudent(newStudents[i], students[i]);
    }

    // index-based loop: collect and validate input for each new student
    for (int i = count; i < count + newCount; i++) {
        cout << endl << "Student " << (i - count + 1) << endl;

        newStudents[i].setName(getValidatedName("Name: "));

        // takes id from user input and set new student id once obtained
        int id;
        while (true) {
            id = getValidatedInt("ID: ", 1, 999999);
            if (!isDuplicateId(newStudents.get(), i, id)) break;
            cout << "Duplicate ID. Please enter a unique ID." << endl;
        }
        newStudents[i].setId(id);

        // get marks from user and set new student marks once obtained
        for (int j = 0; j < SUBJECT_COUNT; j++) {
            newStudents[i].setMark(j, getValidatedMark(
                "Mark " + to_string(j + 1) + ": "));
        }
        newStudents[i].recalculate();
    }

    Student::addTotalCreated(newCount);
    count += newCount;
    // old array freed automatically by unique_ptr
    students = std::move(newStudents);
}

/*
 * Displays all student records in a formatted table using a range-based loop.
 * Prints a warning if no students exist.
 */
void displayStudents(const unique_ptr<Student[]>& students, const int count) {
    // edge case checking
    if (count == 0) {
        cout << "No students available." << endl;
        return;
    }
    cout << endl << "===== Student Records =====" << endl;
    printTableHeader();
    // range-based loop via std::span over the raw array
    for (const auto& s : span<const Student>(students.get(), count)) {
        printStudentRow(s);
    }
    cout << endl;
}

/*
 * Prompts for a student ID and displays the matching record if found.
 * Uses iterator-based traversal internally via findStudentIndexById.
 */
void searchStudentById(const unique_ptr<Student[]>& students, const int count) {
    // edge case checking
    if (count == 0) {
        cout << "No students to search." << endl;
        return;
    }
    // grab id from user then searches
    const int id  = getValidatedInt("Enter student ID to search: ", 1, 999999);
    const int idx = findStudentIndexById(students, count, id);
    if (idx == -1) {
        cout << "No student found with ID " << id << "." << endl;
        return;
    }
    cout << endl << "===== Student Found =====" << endl;
    printTableHeader();
    printStudentRow(students[idx]);
    cout << endl;
}

/*
 * Allows the user to update the name and/or marks of an existing student.
 * Pressing Enter on any field keeps the current value.
 * Recalculates derived fields after any change.
 */
void editStudent(unique_ptr<Student[]>& students, const int count) {
    // edge case checking
    if (count == 0) {
        cout << "No students to edit." << endl;
        return;
    }
    // get student id to edit, exits prematurely if id not found
    const int id  = getValidatedInt("Enter student ID to edit: ", 1, 999999);
    const int idx = findStudentIndexById(students, count, id);
    if (idx == -1) {
        cout << "No student found with ID " << id << "." << endl;
        return;
    }

    // grab student to be edited
    Student& s = students[idx];
    cout << "Editing: " << s.getName() << " (ID " << s.getId() << "). Press Enter to keep current value." << endl;

    string input;
    cout << "Name [" << s.getName() << "]: ";
    getline(cin, input);
    if (!isBlank(input)) s.setName(trim(input));

    // let user input new marks then set student's marks
    for (int j = 0; j < SUBJECT_COUNT; j++) {
        cout << fixed << setprecision(2);
        cout << "Mark " << j + 1 << " [" << s.getMark(j) << "]: ";
        getline(cin, input);
        const string t = trim(input);
        if (!t.empty()) {
            try {
                size_t pos;
                const float m = stof(t, &pos);
                if (pos == t.size() && m >= 0.0f && m <= 100.0f)
                    s.setMark(j, m);
                else
                    cout << "Invalid mark, keeping previous value." << endl;
            } catch (...) {
                cout << "Invalid mark, keeping previous value." << endl;
            }
        }
    }
    s.recalculate();
    cout << "Student record updated." << endl;
}

/*
 * Removes a student from the array by ID.
 * Rebuilds the array without the deleted entry using an index-based loop.
 * The old unique_ptr array is freed automatically on reassignment.
 */
void deleteStudent(unique_ptr<Student[]>& students, int& count) {
    // edge case checking
    if (count == 0) {
        cout << "No students to delete." << endl;
        return;
    }
    // get student id from user for deletion, end prematurely if not found
    const int id  = getValidatedInt("Enter student ID to delete: ", 1, 999999);
    const int idx = findStudentIndexById(students, count, id);
    if (idx == -1) {
        cout << "No student found with ID " << id << "." << endl;
        return;
    }

    // just delete array if only student left
    if (count == 1) {
        students.reset(); // releases the array, leaving students as nullptr
        count = 0;
        cout << "Student deleted. No students remaining." << endl;
        return;
    }

    // adjust count for removed student and allocate to new array
    const int oldCount = count;
    count -= 1;
    auto newStudents = make_unique<Student[]>(count);

    // index-based loop: copy all entries except the one being deleted
    int dest = 0;
    for (int i = 0; i < oldCount; i++) {
        if (i != idx) copyStudent(newStudents[dest++], students[i]);
    }

    // old array freed automatically
    students = std::move(newStudents);
    cout << "Student with ID " << id << " deleted." << endl;
}

/*
 * Finds and displays the student with the highest average mark.
 * Uses iterator-based traversal via std::max_element over the raw pointer range.
 * If two students share the highest average, the first one found is displayed.
 */
void findHighestScorer(const unique_ptr<Student[]>& students, const int count) {
    // edge case checking
    if (count == 0) {
        cout << "No students available." << endl;
        return;
    }
    // iterator-based: std::max_element over raw pointer range
    const Student* begin = students.get();
    const Student* end   = begin + count;
    // use max_element which takes iterator and grabs maximum element of the collection
    auto it = max_element(begin, end, [](const Student& a, const Student& b) {
        // use average as comparison for max_element
        return a.getAverage() < b.getAverage();
    });
    cout << endl << "===== Highest Scoring Student =====" << endl;
    printTableHeader();
    printStudentRow(*it);
    cout << endl;
}

/*
 * Displays aggregate class statistics: total students, class average,
 * pass/fail counts, highest average, and pass rate.
 * Uses a range-based loop via std::span for summary processing.
 */
void displayClassSummary(const unique_ptr<Student[]>& students, const int count) {
    // edge case checking
    if (count == 0) {
        cout << "No students available for summary." << endl;
        return;
    }

    float totalAvg   = 0.0f;
    float highestAvg = 0.0f;
    int   passed     = 0;

    // range-based loop via std::span for accumulating summary stats
    for (const auto& s : span<const Student>(students.get(), count)) {
        totalAvg += s.getAverage();
        if (s.getStatus() == PASS) ++passed;
        if (s.getAverage() > highestAvg) highestAvg = s.getAverage();
    }

    const float classAvg = totalAvg / static_cast<float>(count);
    const int   failed   = count - passed;
    const float passRate = (static_cast<float>(passed) / static_cast<float>(count)) * 100.0f;

    cout << fixed << setprecision(2);
    cout << endl << "===== Class Summary =====" << endl;
    cout << left << setw(18) << "Total Students" << ": " << count      << endl;
    cout << left << setw(18) << "Class Average"  << ": " << classAvg   << endl;
    cout << left << setw(18) << "Passed"         << ": " << passed     << endl;
    cout << left << setw(18) << "Failed"         << ": " << failed     << endl;
    cout << left << setw(18) << "Highest Avg"    << ": " << highestAvg << endl;
    cout << left << setw(18) << "Pass Rate"      << ": " << passRate   << "%" << endl << endl;
}

/*
 * Sorts the student array in-place by name (ascending) or average (descending)
 * based on the user's choice. Uses std::sort with raw pointer iterators.
 */
void sortStudents(unique_ptr<Student[]>& students, const int count) {
    // edge case checking
    if (count < 2) {
        cout << "Not enough students to sort." << endl;
        return;
    }
    // see how to sort
    cout << "Sort by:" << endl << "1. Name (ascending)" << endl << "2. Average (descending)" << endl;
    const int choice = getValidatedInt("Choice: ", 1, 2);

    // init iterators
    Student* begin = students.get();
    Student* end   = begin + count;

    // is just a 2 branch possibility so no need for case
    if (choice == 1) {
        sort(begin, end, [](const Student& a, const Student& b) {
            // sort using student name
            return a.getName() < b.getName();
        });
        cout << "Sorted by name (ascending)." << endl;
    } else {
        sort(begin, end, [](const Student& a, const Student& b) {
            // sort using student average
            return a.getAverage() > b.getAverage();
        });
        cout << "Sorted by average (descending)." << endl;
    }
}

/*
 * Writes all student records to students.txt in pipe-delimited format.
 * Sets the volatile fileWriteInProgress flag for the duration of the write.
 * Displays a warning if there are no students to save.
 */
void saveToFile(const unique_ptr<Student[]>& students, const int count) {
    // edge case checking
    if (count == 0) {
        cout << "No students to save." << endl;
        return;
    }
    // let program know file is being used
    fileWriteInProgress = true;
    ofstream file("students.txt");
    // check that file exists
    if (!file.is_open()) {
        cout << "Error: Could not open students.txt for writing." << endl;
        fileWriteInProgress = false;
        return;
    }
    file << fixed << setprecision(2);
    file << "ID|Name|Mark1|Mark2|Mark3|Total|Average|Grade|Status" << endl;
    for (const auto& s : span<const Student>(students.get(), count)) {
        file << s.getId()        << "|" << s.getName()    << "|"
             << s.getMark(0)     << "|" << s.getMark(1)   << "|" << s.getMark(2) << "|"
             << s.getTotal()     << "|" << s.getAverage() << "|"
             << gradeToString(s.getGrade())   << "|"
             << statusToString(s.getStatus()) << endl;
    }
    file.close();
    fileWriteInProgress = false;
    cout << "Records saved to students.txt successfully." << endl;
}

/*
 * Loads student records from students.txt, replacing any existing in-memory data.
 * Skips the header line and validates each record before accepting it:
 * incomplete lines, invalid IDs, duplicate IDs, empty names, and out-of-range
 * marks are all silently warned about and skipped.
 */
void loadFromFile(unique_ptr<Student[]>& students, int& count) {
    ifstream file("students.txt");
    // check that the file exists
    if (!file.is_open()) {
        cout << "Warning: students.txt not found." << endl;
        return;
    }

    string line;
    // skip the header line
    if (!getline(file, line)) {
        cout << "No records available." << endl;
        return;
    }

    vector<Student> temp;
    set<int> seenIds;
    int lineNum = 1;

    while (getline(file, line)) {
        ++lineNum;
        if (isBlank(line)) continue;

        const auto tokens = splitLine(line, '|');
        if (tokens.size() < 9) {
            cout << "Warning: line " << lineNum << " is incomplete, skipping." << endl;
            continue;
        }

        Student s;

        // validate and parse the student ID
        try {
            size_t pos;
            const long long rawId = stoll(tokens[0], &pos);
            if (pos != tokens[0].size() || rawId <= 0) throw invalid_argument("id");
            s.setId(static_cast<int>(rawId));
        } catch (...) {
            cout << "Warning: invalid ID on line " << lineNum << ", skipping." << endl;
            continue;
        }

        if (seenIds.count(s.getId())) {
            cout << "Warning: duplicate ID " << s.getId() << " on line " << lineNum << ", skipping." << endl;
            continue;
        }

        s.setName(trim(tokens[1]));
        if (s.getName().empty()) {
            cout << "Warning: empty name on line " << lineNum << ", skipping." << endl;
            continue;
        }

        // validate and parse each subject mark
        bool marksOk = true;
        for (int j = 0; j < SUBJECT_COUNT; j++) {
            try {
                size_t pos;
                const float m = stof(tokens[2 + j], &pos);
                if (pos != tokens[2 + j].size() || m < 0.0f || m > 100.0f)
                    throw out_of_range("mark");
                s.setMark(j, m);
            } catch (...) {
                cout << "Warning: invalid mark on line " << lineNum << ", skipping." << endl;
                marksOk = false;
                break;
            }
        }
        if (!marksOk) continue;

        s.recalculate();
        seenIds.insert(s.getId());
        temp.push_back(s);
    }
    file.close();

    if (temp.empty()) {
        cout << "No records available." << endl;
        return;
    }

    // index-based loop: transfer validated records into the new unique_ptr array
    auto newStudents = make_unique<Student[]>(temp.size());
    for (int i = 0; i < static_cast<int>(temp.size()); i++) {
        copyStudent(newStudents[i], temp[i]);
    }

    students = std::move(newStudents); // existing in-memory data replaced safely
    count = static_cast<int>(temp.size());
    cout << "Loaded " << count << " student(s) from students.txt." << endl;
}
