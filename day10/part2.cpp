#include <iostream>
#include <fstream>
#include <string>

// If the sprite is positioned such that one of its three pixels is the pixel 
// currently being drawn, the screen produces a lit pixel (#); otherwise, the 
// screen leaves the pixel dark (.).

int main(int argc, char* argv[]) {

    // inputs
    int end_of_row = 40;
    int row_increments = 40;
    int max_row = 240;
    int next_end_of_row = end_of_row;

    // totals
    int pixel_location = 0;
    int register_total = 1;

    // rows to print
    std::string current_row = "";

    std::ifstream input_file;
    input_file.open("input_file");
    std::string current_line;
    if (input_file.is_open()) {
        while (std::getline(input_file, current_line)) {

            // parse line for command | if not noop, get number of command
            bool noop = false;
            int current_number;
            if (current_line.find(' ') == std::string::npos) {noop = true;}
            else {
                current_number = stoi(current_line.substr(current_line.find(' ') + 1));
            }
                
            // cycle 1 or 2 times depending one command
            int num_of_cycles = noop ? 1 : 2;
            for (int i = 0; i < num_of_cycles; i++) {

                // get current row idx by modulo
                int current_row_idx = pixel_location % 40;

                // if idx in range of pixel to paint "#", else paint "."
                if (current_row_idx == register_total ||
                    current_row_idx == register_total - 1 ||
                    current_row_idx == register_total + 1) {

                    current_row+="#";
                } else {
                    current_row+=".";
                }

                // if at end of row print and clear for next row
                if (pixel_location == next_end_of_row - 1) {
                    std::cout << current_row << std::endl;
                    current_row.erase();
                    next_end_of_row+=row_increments;
                }

                // only update register after second cycle
                if (i == 1) {
                   register_total+=current_number;
                }

                // move pixel to paint to next location
                pixel_location++;

            }
        }
        input_file.close();
    }
}

