#include <iostream>
#include <fstream>
#include <string>


int main() {

    // inputs
    int starting_of_cycle = 20;
    int cycle_increments = 40;
    int max_cycle_num = 220;
    int next_cycle_number = starting_of_cycle;

    // totals
    int total_num_of_executions = 0;
    int register_total = 1;
    int total_signal_strength = 0;

    std::ifstream input_file;
    input_file.open("input_file");
    std::string current_line;
    if (input_file.is_open()) {
        while (std::getline(input_file, current_line)) {

            // parse line for command | if not noop, get number of command
            bool noop = false;
            int current_number;
            if (current_line.find(' ') == std::string::npos) {
                noop = true;
            }
            else {
                current_number = stoi(current_line.substr(current_line.find(' ') + 1));
            }
                
            // cycle 1 or two times depending one command
            int num_of_cycles = noop ? 1 : 2;
            for (int i = 0; i < num_of_cycles; i++) {

                // keep track of executions
                total_num_of_executions++;

                // calculate signal strength based on rules
                if (total_num_of_executions == next_cycle_number && total_num_of_executions <= max_cycle_num) {
                    // get signal strength and add it to total
                    int current_signal_strength = total_num_of_executions * register_total;
                    total_signal_strength+=current_signal_strength;
                    // create next cycle number
                    next_cycle_number+=cycle_increments;
                }

                // only update register after second cycle
                if (i == 1) {register_total+=current_number;}
            }
        }
        input_file.close();
    }
std::cout << "Sum of Six Signal Strengths: " << total_signal_strength <<  std::endl;
}

