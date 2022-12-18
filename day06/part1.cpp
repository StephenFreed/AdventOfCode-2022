#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int GetEndOfPacket(const std::string& all_lines_string);

int main() {

    // not needed, but build one big string if multiple lines 
    std::string all_lines_string;

    // parse input file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {
            all_lines_string+=current_line;
        }

    input_file.close();
    }

    // 4 unique char | last index of 4 is how many processed to find packet
    int end_of_packet_idx = -1;
    end_of_packet_idx = GetEndOfPacket(all_lines_string);
    if (end_of_packet_idx == -1){
        std::cout << "Something Went Wrong" << std::endl;
    }
    else {
        std::cout << "End of Packed IDX: " << end_of_packet_idx << std::endl;
    }
}


int GetEndOfPacket(const std::string& all_lines_string) {

    std::unordered_set<char> unique_chars;
    for (int i = 3; i < all_lines_string.length(); i++) {

        // get window of 4 chars
        char one = all_lines_string.at(i-3);
        char two = all_lines_string.at(i-2);
        char three = all_lines_string.at(i-1);
        char four = all_lines_string.at(i);

        // insert chars into set 
        unique_chars.insert(one);
        unique_chars.insert(two);
        unique_chars.insert(three);
        unique_chars.insert(four);

        // check if set has 4 unique chars
        if (unique_chars.size() == 4) {
            return i + 1;
        }

        unique_chars.clear();
    }
    // if length of string < 4 and/or not 4 unique chars in a row
    return -1;
}




