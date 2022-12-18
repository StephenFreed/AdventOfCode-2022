#include <iostream>
#include <fstream>
#include <string>
#include <vector>


// function to return correct vector based on number parsed from input line
std::vector<char>& GetStack(int num, std::vector<char>& one,
                                     std::vector<char>& two,
                                     std::vector<char>& three,
                                     std::vector<char>& four,
                                     std::vector<char>& five,
                                     std::vector<char>& six,
                                     std::vector<char>& seven,
                                     std::vector<char>& eight,
                                     std::vector<char>& nine);

int main() {

    // starting stacks
    std::vector<char> stack_one = {'B','V','S','N','T','C','H','Q'};
    std::vector<char> stack_two = {'W','D','B','G'};
    std::vector<char> stack_three = {'F','W','R','T','S','Q','B'};
    std::vector<char> stack_four = {'L','G','W','S','Z','J','D','N'};
    std::vector<char> stack_five = {'M','P','D','V','F'};
    std::vector<char> stack_six = {'F','W','J'};
    std::vector<char> stack_seven = {'L','N','Q','B','J','V'};
    std::vector<char> stack_eight = {'G','T','R','C','J','Q','S','N'};
    std::vector<char> stack_nine = {'J','S','Q','C','W','D','M'};

    // parse input file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {
        // iterate over lines in file
        std::string current_line;
        while(std::getline(input_file, current_line)) {

            // to keep record of input | skip stacks starting point
            if (current_line.at(0) == '#') {
                continue;
            }

            // get indexes to parse lines
            int first_space = current_line.find(' ');
            int second_space = current_line.find(' ', first_space + 1);
            int third_space = current_line.find(' ', second_space + 1);
            int fourth_space = current_line.find(' ', third_space + 1);
            int fifth_space = current_line.find(' ', fourth_space + 1);

            // parse numbers from lines
            int num_of_moves = stoi(current_line.substr(first_space+1, (second_space - first_space) -1));
            int from_stack = stoi(current_line.substr(third_space+1, (fourth_space - third_space) -1));
            int to_stack = stoi(current_line.substr(fifth_space+1));
            
            // convert number to name of stack | checking for valid input first (1-9)
            if (from_stack >= 1 && from_stack <= 9 && to_stack >= 1 && to_stack <=9 ) {

                // get stack reference
                std::vector<char>& new_from_stack = GetStack(from_stack,stack_one,stack_two,stack_three,stack_four,
                                                             stack_five,stack_six,stack_seven,stack_eight,stack_nine);
                std::vector<char>& new_to_stack = GetStack(to_stack,stack_one,stack_two,stack_three,stack_four,
                                                           stack_five,stack_six,stack_seven,stack_eight,stack_nine);

                // for each crate that needs to be moved
                // pop "from_stack" and push "to_stack"
                for (int i = 0; i < num_of_moves; i++) {
                    new_to_stack.push_back(new_from_stack.back());
                    new_from_stack.pop_back();
                }
            } 
            else {
                std::cout << "Invalid Number Given To GetStack Function" << std::endl;
                std::exit(1);
            }

        }
    input_file.close();
    }
    // build string answer
    std::string answer;
    answer.push_back(stack_one.back());
    answer.push_back(stack_two.back());
    answer.push_back(stack_three.back());
    answer.push_back(stack_four.back());
    answer.push_back(stack_five.back());
    answer.push_back(stack_six.back());
    answer.push_back(stack_seven.back());
    answer.push_back(stack_eight.back());
    answer.push_back(stack_nine.back());
    std::cout << "Answer: " << answer << std::endl;

}


// this convers int from the input to vector reference to move crates between stacks
std::vector<char>& GetStack(int num, std::vector<char>& one,
                                    std::vector<char>& two,
                                    std::vector<char>& three,
                                    std::vector<char>& four,
                                    std::vector<char>& five,
                                    std::vector<char>& six,
                                    std::vector<char>& seven,
                                    std::vector<char>& eight,
                                    std::vector<char>& nine) {
    if (num == 1) {
        return one;
    }
    else if (num == 2) {
        return two;
    }
    else if (num == 3) {
        return three;
    }
    else if (num == 4) {
        return four;
    }
    else if (num == 5) {
        return five;
    }
    else if (num == 6) {
        return six;
    }
    else if (num == 7) {
        return seven;
    }
    else if (num == 8) {
        return eight;
    }
    else {
        return nine;
    }
}
