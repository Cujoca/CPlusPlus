#include "Helper.h"
#include <iostream>

using namespace std;

/*
 * Trims leading and trailing whitespace from a string
 */
string trim(const string& text) {
    const auto start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    const auto end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

/*
 * Returns true if the string is empty or contains only whitespace
 */
bool isBlank(const string& text) {
    return trim(text).empty();
}

/*
 * Repeatedly prompts the user until a valid integer in [min, max] is entered.
 * Rejects non-numeric input, floating-point input, and out-of-range values.
 */
int getValidatedInt(const string& prompt, int min, int max) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        const string s = trim(line);
        if (s.empty()) {
            cout << "Input cannot be empty.\n";
            continue;
        }
        try {
            size_t pos;
            const long long val = stoll(s, &pos);
            if (pos != s.size()) {
                cout << "Invalid input. Please enter a whole number.\n";
                continue;
            }
            if (val < min || val > max) {
                cout << "Please enter a number between " << min << " and " << max << ".\n";
                continue;
            }
            return static_cast<int>(val);
        } catch (...) {
            cout << "Invalid input. Please enter a whole number.\n";
        }
    }
}

/*
 * Repeatedly prompts the user until a valid float in [0, 100] is entered.
 * Rejects non-numeric input and values outside the valid mark range.
 */
float getValidatedMark(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        const string s = trim(line);
        if (s.empty()) {
            cout << "Input cannot be empty.\n";
            continue;
        }
        try {
            size_t pos;
            const float val = stof(s, &pos);
            if (pos != s.size()) {
                cout << "Invalid input. Please enter a numeric mark.\n";
                continue;
            }
            if (val < 0.0f || val > 100.0f) {
                cout << "Mark must be between 0 and 100.\n";
                continue;
            }
            return val;
        } catch (...) {
            cout << "Invalid input. Please enter a numeric mark.\n";
        }
    }
}

/*
 * Repeatedly prompts the user until a non-empty, non-whitespace name is entered
 */
string getValidatedName(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        const string name = trim(line);
        if (!name.empty()) return name;
        cout << "Name cannot be empty or whitespace only.\n";
    }
}

/*
 * Splits a string by a single delimiter character and returns the resulting tokens.
 * The final token after the last delimiter is always included.
 */
vector<string> splitLine(const string& s, char delim) {
    vector<string> tokens;
    size_t left = 0, right = 0;
    while ((right = s.find(delim, left)) != string::npos) {
        tokens.push_back(s.substr(left, right - left));
        left = right + 1;
    }
    tokens.push_back(s.substr(left));
    return tokens;
}
