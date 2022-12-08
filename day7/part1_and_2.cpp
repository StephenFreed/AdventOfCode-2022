#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void GetEachDirTotalSize(std::unordered_map<std::string, int>& dir_totals);
void GetDirSumsWithChildren(std::unordered_map<std::string, int>& dir_totals,
                            std::unordered_map<std::string, int>& dir_sums);

int main () {

    // map of directory file size totals | this is each directory, not the total of directory and child directories
    std::unordered_map<std::string, int> dir_totals;
    // map of directory file size with child file sizes added, for a "total" file size of directory
    std::unordered_map<std::string, int> dir_sums;

    // gets total size of files in each individual directory
    GetEachDirTotalSize(dir_totals);
    // builds map of directory size with child directories added
    GetDirSumsWithChildren(dir_totals, dir_sums);
    
    int total_size_under_100k = 0;
    // size needed to free || min size of dir to choose to delete
    int size_to_free = dir_sums["//"] - 40000000;
    int smallest_over_size_to_free = INT_MAX;
    // loop over dir sums
    for (const auto x : dir_sums) {

        // part one answer
        if (x.second < 100000) {
            total_size_under_100k+=x.second;
        }
        // part two answer
        if (x.second > size_to_free) {
            if (x.second < smallest_over_size_to_free) {
                smallest_over_size_to_free  = x.second;
            }
        }
    }
    std::cout << "Total Size Of All Files: " << dir_sums["//"] << std::endl;
    std::cout << "Total Size To Free: " << size_to_free << std::endl;
    std::cout << "(Answer 1) Total Size Under 100k: " << total_size_under_100k << std::endl;
    std::cout << "(Answer 2) Smallest Dir Over Size Needed To Free: " << smallest_over_size_to_free << std::endl;
 }


void GetEachDirTotalSize(std::unordered_map<std::string, int>& dir_totals) {

    // keeps track of current directory
    std::string current_path = "";

    // iterate through lines
    std::string current_line;
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {
        while (std::getline(input_file, current_line)) {

            // gets idx to parse first section of line
            int first_section_idx = current_line.find(' ');
            std::string first_section = current_line.substr(0,first_section_idx);

            // effectively keeps track of current_directory for else statement
            if (first_section == "$") {

                // gets idx to parse second section of line
                std::string second_section = current_line.substr(first_section_idx + 1, 2);
                
                // if cd add to current_path string
                if (second_section  == "cd") {

                    // gets idx to parse third section of line
                    int second_section_idx = current_line.find(' ', first_section_idx + 1);
                    // int third_section_idx = current_line.find(' ', second_section_idx + 1);
                    std::string third_section = current_line.substr(second_section_idx + 1);

                    // removes the last director if "cd .." | adds if "cd <dir>"
                    if (third_section == "..") {
                        int last_dir_in_path_idx = current_path.find_last_of('/');
                        current_path = current_path.substr(0, last_dir_in_path_idx);
                        if (current_path.empty()) {
                            current_path = "/";
                        }
                    }
                    else {
                        std::string add_dir = "/" + third_section;
                        current_path+=add_dir;
                    }

                }
            }
            // if not "cd" or "dir" command | adds to dir value in map
            else if (first_section != "dir") {
                // uses current path as key | adds section one to value
                dir_totals[current_path]+= stoi(first_section);
            }
        }
        input_file.close();
    }
}


void GetDirSumsWithChildren(std::unordered_map<std::string, int>& dir_totals,
                            std::unordered_map<std::string, int>& dir_sums) {

    // loop through directory totals
    for (const auto x : dir_totals) {

        // iterate over directories | each directory key is full path to directory
        std::string key = x.first;
        std::string current_sub_dir;
        for (int i = 2; i < key.length(); i++) {
            if (key.at(i) == '/' || i == key.length() - 1) {
                if (i == key.length() - 1) {
                    current_sub_dir = key.substr(0, i+1);
                } else {
                    current_sub_dir = key.substr(0, i);
                }
                // init root dir with its files total
                if (current_sub_dir == "//" && dir_sums.count(current_sub_dir) == 0) {
                    dir_sums[current_sub_dir] = dir_totals[current_sub_dir];
                }
                dir_sums[current_sub_dir]+=x.second;
            }
        }
    }
}
