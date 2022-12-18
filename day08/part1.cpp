#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main () {

    // 2d vector from input file
    std::vector<std::vector<int>> trees;

    // build 2d vector of nums from input file
    std::ifstream input_file;
    input_file.open("input_file");
    std::string current_line;
    if (input_file.is_open()) {
        while (std::getline(input_file, current_line)) {

            std::vector<int> current_line_vector;
            for (int i = 0; i < current_line.length(); i++) {
                int current_num = stoi(current_line.substr(i,1));
                current_line_vector.push_back(current_num);
            }
            trees.push_back(current_line_vector);
        }
        input_file.close();
    }

    int total_can_see = 0;
    // for loop through 2d vector | check all 4 directons
    // reaching last element before out of bounds with no tree >= == visible tree
    for (int i = 0; i < trees.size(); i++) {
        for (int j = 0; j < trees[i].size(); j++) {

            bool can_see = false;

            // check if on perimeter | stops + 1 idx out of bounds in right,left,up,down checks
            if (i == 0 || i == trees.size() - 1 || j == 0 || j == trees[i].size() - 1) {
                can_see = true;
            }

            // check right 
            int go_right_idx = j + 1;
            while (go_right_idx <= trees[i].size() - 1 && can_see != true) {
                if (trees[i][j] <= trees[i][go_right_idx]) {
                    break;
                }
                if (go_right_idx == trees[i].size() - 1) {
                    can_see = true;
                }
                go_right_idx++;
            }

            // check left
            int go_left_idx = j - 1;
            while (go_left_idx >= 0  && can_see != true) {
                if (trees[i][j] <= trees[i][go_left_idx]) {
                    break;
                }
                if (go_left_idx == 0) {
                    can_see = true;
                }
                go_left_idx--;
            }

            // check up
            int go_up_idx = i - 1;
            while (go_up_idx >= 0  && can_see != true) {
                if (trees[i][j] <= trees[go_up_idx][j]) {
                    break;
                }
                if (go_up_idx == 0) {
                    can_see = true;
                }
                go_up_idx--;
            }

            // check down
            int go_down_idx = i + 1;
            while (go_down_idx <= trees.size() - 1  && can_see != true) {
                if (trees[i][j] <= trees[go_down_idx][j]) {
                    break;
                }
                if (go_down_idx == trees.size() - 1) {
                    can_see = true;
                }
                go_down_idx++;
            }

            // if can_see was set to true add to total_can_see
            if (can_see) {
                total_can_see++;
            }
        }
    }
    std::cout << "Visible From Outside The Grid: " << total_can_see << std::endl;
}


