#include <iostream>
#include <fstream>
#include <string>

int main () {

    // parse input_file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        int largest_total_calories = 0;
        int current_total_calories = 0;

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            // reset on blank lines
            if (current_line.length() == 0) {
                current_total_calories = 0;
            }
            else {
                int current_calories = std::stoi(current_line);
                // add to current count
                current_total_calories+=current_calories;
                // check if new largest
                if (current_total_calories > largest_total_calories) {
                    largest_total_calories = current_total_calories;
                }
            }
        }
        input_file.close();
        // print out largest total 
        std::cout << "Largest Total: " << largest_total_calories << std::endl;
    }
}
