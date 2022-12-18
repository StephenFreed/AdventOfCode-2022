#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// find char that is in both compartments
char GetPriorityChar(const std::string& compartment_1, const std::string& compartment_2);
// get total of priority char values
int GetTotalOfPriorityChar(const std::vector<char>& in_both, 
                           const std::string& lowercase_letters,
                           const std::string& uppercase_letters,
                           const std::unordered_map<char,int>& lowercase_priority_value, 
                           const std::unordered_map<char,int>& uppercase_priority_value);

int main() {

    // vector to hold chars found in both compartments
    std::vector<char> in_both;

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

    // parse input_file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            // split into two even compartments
            std::string compartment_1 = current_line.substr(0, (current_line.length() / 2));
            std::string compartment_2 = current_line.substr((current_line.length() / 2));

            // get priority char in both compartments and push it into in_both vector
            char priority_char = GetPriorityChar(compartment_1, compartment_2);
            // check priority char was successfully found
            if (priority_char == ';') {
                std::cout << "No Priority Char Was Found" << std::endl;
                std::exit(1);
            }
            in_both.push_back(priority_char);

        }

        // get total of priority char values
        int total_value = GetTotalOfPriorityChar(in_both,lowercase_letters, uppercase_letters, 
                                                 lowercase_priority_value, uppercase_priority_value);
        std::cout << "Total Value: " << total_value << std::endl;

    input_file.close();
    }
}

char GetPriorityChar(const std::string& compartment_1, const std::string& compartment_2) {

    // set to keep track of unique chars in compartment 1
    std::unordered_set<char> current_chars;
    for (char curr_char : compartment_1) {
        current_chars.insert(curr_char);
    }

    // check compartment 2 vs set of char
    for (char curr_char_2 : compartment_2) {
        if (current_chars.count(curr_char_2) > 0) {
            return curr_char_2;
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

