#include <iostream>
#include <string>
#include <regex>

bool isBmpFile(const std::string& fileName) {
    // Regular expression to check if the file name ends with .bmp (case insensitive) and does not contain invalid characters
    std::regex bmpRegex("^[^<>:\"/\\|?*]+\\.bmp$", std::regex_constants::icase);
    return std::regex_match(fileName, bmpRegex);
}

bool containsUnsafeCharacters(const std::string& fileName) {
    // List of characters and patterns considered unsafe for file names
    std::string unsafeCharacters = "<>:\"/\\|?*";
    for (char c : unsafeCharacters) {
        if (fileName.find(c) != std::string::npos) {
            return true;
        }
    }

    // Check for directory traversal attempts
    if (fileName.find("..") != std::string::npos) {
        return true;
    }

    return false;
}


void firstInteraction() {
    std::cout << "SWHL_Module Comparison";
    std::cout << "Hello, user!";
    std::cout << "Please, enter the file name and its extension without additional characters and spaces";
    std::cout << "Enter the first file";
}

int main() {
    int 
}