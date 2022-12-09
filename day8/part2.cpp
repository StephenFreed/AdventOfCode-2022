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

    int highest_scenic_score = 0;
    // for loop through 2d vector | check all 4 directons
    // count how many trees in each direction can be seen
    for (int i = 0; i < trees.size(); i++) {
        for (int j = 0; j < trees[i].size(); j++) {

            // total trees visible per side
            int right_trees = 0;
            int left_trees = 0;
            int up_trees = 0;
            int down_trees= 0;

            // check right 
            int right_trees_visible = 0;
            int go_right_idx = j + 1;
            while (go_right_idx < trees[i].size()) {
                right_trees_visible++;
                if (trees[i][j] <= trees[i][go_right_idx]) {
                    break;
                } 
                go_right_idx++;
            }
            right_trees = right_trees_visible;

            // check left
            int left_trees_visible = 0;
            int go_left_idx = j - 1;
            while (go_left_idx >= 0) {
                left_trees_visible++;
                if (trees[i][j] <= trees[i][go_left_idx]) {
                    break;
                }
                go_left_idx--;
            }
            left_trees = left_trees_visible;

            // check up
            int up_trees_visible = 0;
            int go_up_idx = i - 1;
            while (go_up_idx >= 0) {
                up_trees_visible++;
                if (trees[i][j] <= trees[go_up_idx][j]) {
                    break;
                }
                go_up_idx--;
            }
            up_trees = up_trees_visible;

            // check down
            int down_trees_visible = 0;
            int go_down_idx = i + 1;
            while (go_down_idx <= trees.size() - 1) {
                down_trees_visible++;
                if (trees[i][j] <= trees[go_down_idx][j]) {
                    break;
                }
                go_down_idx++;
            }
            down_trees = down_trees_visible;

            // add up scenic score
            int current_scenic_score = left_trees * right_trees * up_trees * down_trees;
            if (current_scenic_score > highest_scenic_score) {
                highest_scenic_score = current_scenic_score;
            }
        }
    }
    std::cout << "Highest Scenic Score: " << highest_scenic_score << std::endl;
}


