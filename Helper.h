#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

// text util
std::string trim(const std::string& text);
bool        isBlank(const std::string& text);

// input validation
int         getValidatedInt  (const std::string& prompt, int min, int max);
float       getValidatedMark (const std::string& prompt);
float       getValidatedFloat(const std::string& prompt, float min, float max);
float       getValidatedWage (const std::string& prompt);
std::string getValidatedName (const std::string& prompt);

// string manipulation
std::vector<std::string> splitLine(const std::string& s, char delim);

#endif
