#include <iostream>
#include <fstream>
#include <string>

int main() {

    int fully_contain_total = 0;

    // parse input_file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            // get index of ',' to split each assignment pair
            int comma_idx = current_line.find(',');
            // split into assigment pairs
            std::string assignment_1 = current_line.substr(0, comma_idx);
            std::string assignment_2 = current_line.substr(comma_idx + 1);

            // get index for hyphen in assignments
            int hyphen_idx_1 = assignment_1.find('-');
            int hyphen_idx_2 = assignment_2.find('-');
            // split assignment pairs into left and right number
            int left_assignment_1 = stoi(assignment_1.substr(0, hyphen_idx_1));
            int right_assignment_1 = stoi(assignment_1.substr(hyphen_idx_1 + 1));
            int left_assignment_2 = stoi(assignment_2.substr(0, hyphen_idx_2));
            int right_assignment_2 = stoi(assignment_2.substr(hyphen_idx_2 + 1));

            // logic to find if a range is contained in the other
            if (left_assignment_1 >= left_assignment_2 && right_assignment_1 <= right_assignment_2) {
                fully_contain_total++;
            }
            else if (left_assignment_2 >= left_assignment_1 && right_assignment_2 <= right_assignment_1) {
                fully_contain_total++;
            }

        }
    input_file.close();
    }
    std::cout << "Fully Contained Total: " << fully_contain_total << std::endl;
}

