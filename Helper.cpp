#include "Helper.h"
#include <cstdlib>
#include <iostream>

using namespace std;

constexpr float MINIMUM_WAGE = 17.95f;
constexpr float MAX_WAGE     = 1000000.0f;

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
 * Terminates the program if the input stream closes: there is no value left to
 * return and no way to re-prompt, so looping would spin forever.
 */
int getValidatedInt(const string& prompt, const int min, const int max) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            cout << "\nInput stream closed with no value entered "
                    "(end of input, or Ctrl+Z / Ctrl+D). Nothing left to read, so exiting.\n";
            exit(0);
        }
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
 * Repeatedly prompts the user until a valid float in [min, max] is entered.
 * Rejects non-numeric input and values outside the given range.
 */
float getValidatedFloat(const string& prompt, const float min, const float max) {
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
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (val < min || val > max) {
                cout << "Please enter a number between " << min << " and " << max << ".\n";
                continue;
            }
            return val;
        } catch (...) {
            cout << "Invalid input. Please enter a number.\n";
        }
    }
}

/*
 * Repeatedly prompts the user until an hourly rate at or above minimum wage is
 * entered. Rejects non-numeric input and any rate below MINIMUM_WAGE.
 */
float getValidatedWage(const string& prompt) {
    while (true) {
        const float rate = getValidatedFloat(prompt, 0.0f, MAX_WAGE);
        if (rate >= MINIMUM_WAGE) return rate;
        cout << "Minimum wage is $" << MINIMUM_WAGE
             << " buddy. Try paying your workers an actual wage\n";
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
vector<string> splitLine(const string& s, const char delim) {
    vector<string> tokens;
    size_t left = 0, right = 0;
    while ((right = s.find(delim, left)) != string::npos) {
        tokens.push_back(s.substr(left, right - left));
        left = right + 1;
    }
    tokens.push_back(s.substr(left));
    return tokens;
}
