#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// find char that is in all three lines
char GetPriorityChar(const std::vector<std::string> current_three_group);
// get total of priority char values
int GetTotalOfPriorityChar(const std::vector<char>& in_both, 
                           const std::string& lowercase_letters,
                           const std::string& uppercase_letters,
                           const std::unordered_map<char,int>& lowercase_priority_value, 
                           const std::unordered_map<char,int>& uppercase_priority_value);

int main() {

    // helpers
    std::string lowercase_letters = "abcdefghijklmnopqrstuvwxyz";
    std::string uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // build map for lowercase priority value
    std::unordered_map<char,int> lowercase_priority_value;
    int lowercase_counter = 1;
    for (char i : lowercase_letters) {
        lowercase_priority_value[i] = lowercase_counter;
        lowercase_counter++;
    }

    // build map for uppercase priority value
    std::unordered_map<char,int> uppercase_priority_value;
    int uppercase_counter = 27;
    for (char i : uppercase_letters) {
        uppercase_priority_value[i] = uppercase_counter;
        uppercase_counter++;
    }

    // lines from file
    std::vector<std::string> file_lines;

    // parse input_file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {
            // build vector of file lines
            file_lines.push_back(current_line);
        }
        input_file.close();
    }

    // vector to hold priority char found in group of 3
    std::vector<char> in_three;

    // for loop for every 3 lines in file_lines vector
    for (int i = 3; i < file_lines.size() + 1; i+=3) {

        // iterator to get groups of 3 lines from file_lines vector
        std::vector<std::string>::const_iterator first = file_lines.begin() + (i - 3);
        std::vector<std::string>::const_iterator last = file_lines.begin() + i;
        std::vector<std::string> current_three_group(first, last);

        // get priority char in group of 3 lines and push it into in_three vector
        char priority_char = GetPriorityChar(current_three_group);
        // check priority char was successfully found
        if (priority_char == ';') {
            std::cout << "No Priority Char Was Found" << std::endl;
            std::exit(1);
        }
        in_three.push_back(priority_char);

    }

    // get total of priority char values
    int total_value = GetTotalOfPriorityChar(in_three,lowercase_letters, uppercase_letters, 
                                             lowercase_priority_value, uppercase_priority_value);
    std::cout << "Total Value: " << total_value << std::endl;
}

char GetPriorityChar(const std::vector<std::string> current_three_group) {

    // set to keep track of unique chars in line 1
    std::unordered_set<char> line_1_set;
    for (char curr_char : current_three_group[0]) {
        line_1_set.insert(curr_char);
    }

    // set to keep track of unique chars in line 2
    std::unordered_set<char> line_2_set;
    for (char curr_char : current_three_group[1]) {
        line_2_set.insert(curr_char);
    }

    // set to keep track of unique chars in line 3
    std::unordered_set<char> line_3_set;
    for (char curr_char : current_three_group[2]) {
        line_3_set.insert(curr_char);
    }

    // check set one vs set two, then confirm with set three
    for (char curr_char : line_1_set) {
        if (line_2_set.count(curr_char) > 0) {
            if (line_3_set.count(curr_char) > 0) {
                return curr_char;
            }
        }
    }
    return ';';
}

int GetTotalOfPriorityChar(const std::vector<char>& in_both, 
                           const std::string& lowercase_letters,
                           const std::string& uppercase_letters,
                           const std::unordered_map<char,int>& lowercase_priority_value, 
                           const std::unordered_map<char,int>& uppercase_priority_value) {

    int total_value = 0;
    for (char i : in_both) {
        if (lowercase_letters.find(i) != std::string::npos) {
            // look up in lowercase map
            total_value+=lowercase_priority_value.at(i);
        }
        else {
            //look up in upercase map
            total_value+=uppercase_priority_value.at(i);
        }
    }   
    return total_value;
}

