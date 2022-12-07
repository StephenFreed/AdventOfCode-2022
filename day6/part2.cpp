#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int GetStartOfMessage(const std::string& all_lines_string);

int main() {

    // not needed, but build one big string if multiple lines 
    std::string all_lines_string;

    // parse input file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file to build one string
        std::string current_line;
        while (std::getline(input_file, current_line)) {
            all_lines_string+=current_line;
        }

    input_file.close();
    }

    // 14 unique char | last index of 14 is how many processed to find message
    int start_of_message_idx = -1;
    start_of_message_idx = GetStartOfMessage(all_lines_string);
    if (start_of_message_idx == -1){
        std::cout << "Something Went Wrong" << std::endl;
    }
    else {
        std::cout << "Start of Message IDX: " << start_of_message_idx << std::endl;
    }
}


// 14 unique chars in string marks the start of message
int GetStartOfMessage(const std::string& all_lines_string) {
    std::unordered_set<char> unique_chars;
    for (int c = 13; c < all_lines_string.size(); c++) {
        for (int i = c - 13; i <= c; i++) {
            unique_chars.insert(all_lines_string.at(i));
        }
        if (unique_chars.size() == 14) {
            return c + 1;
        }
    unique_chars.clear();
    }
    // if length of string < 14 and/or not 14 unique chars in a row
    return -1;
}




