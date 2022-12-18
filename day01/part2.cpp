#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


void AddToTop3(int calories, std::unordered_map<int,int>& top3_map);

int main () {

    // map to keep track
    std::unordered_map<int,int> top3_map;
    top3_map[1] = 0;
    top3_map[2] = 0;
    top3_map[3] = 0;

    // parse input_file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

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
                current_total_calories+=current_calories;
                // if values is > current 3rd value
                if (current_total_calories > top3_map[3]) {
                    AddToTop3(current_total_calories, top3_map);
                }
            }
        }
        input_file.close();
    }
    // print out total of top 3
    int top3_total = top3_map[1] + top3_map[2] + top3_map[3];
    std::cout << "Top 3 Total: " << top3_total << std::endl;
}

// helper to keep track of top 3
void AddToTop3(int calories, std::unordered_map<int,int>& top3_map) {
    int one = top3_map[1];
    int two = top3_map[2];
    int three = top3_map[3];
    if (calories > one) {
        top3_map[3] = top3_map[2];
        top3_map[2] = top3_map[1];
        top3_map[1] = calories;
    }
    else if (calories > two) {
        top3_map[3] = top3_map[2];
        top3_map[2] = calories;
    }
    else if (calories > three) {
        top3_map[3] = calories;
    }
}
