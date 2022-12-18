#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// first row A: Rock | B: Paper | C: Scissors
// seconds row X: Rock | Y: Paper | Z: Scissors
// points second row 1 for Rock | 2 for Paper | 3 for Scissors
// plus score for the outcome of round | 0 if you lost, 3 if the round was a draw, and 6 if you win
// X lost | Y draw | Z win

std::string GetMyPlay(std::string& opponent_play, std::string& ending, 
                      std::unordered_map<std::string,std::string>& lost_map, 
                      std::unordered_map<std::string,std::string>& draw_map, 
                      std::unordered_map<std::string,std::string>& win_map);

int main() {

    // points map for round result
    std::unordered_map<std::string,int> round_result;
    round_result["X"] = 0;  // lost
    round_result["Y"] = 3;  // draw
    round_result["Z"] = 6;  // win

    // points map for my_play
    std::unordered_map<std::string,int> my_play_score;
    my_play_score["X"] = 1;  // rock
    my_play_score["Y"] = 2;  // paper
    my_play_score["Z"] = 3;  // scissors
                             
    // get play if lost
    std::unordered_map<std::string,std::string> lost_map;
    lost_map["A"] = "Z";
    lost_map["B"] = "X";
    lost_map["C"] = "Y";

    // get play if draw
    std::unordered_map<std::string,std::string> draw_map;
    draw_map["A"] = "X";
    draw_map["B"] = "Y";
    draw_map["C"] = "Z";

    // get play if win 
    std::unordered_map<std::string,std::string> win_map;
    win_map["A"] = "Y";
    win_map["B"] = "Z";
    win_map["C"] = "X";
    
    int total_score = 0;
    
    // parse input_file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            // get plays by splitting line
            std::string opponent_play = current_line.substr(0, current_line.find(" "));
            std::string ending = current_line.substr(current_line.find(" ") + 1);

            // add points for result of round
            total_score+=round_result[ending];
            
            // get my_play
            std::string my_play = GetMyPlay(opponent_play, ending, lost_map, draw_map, win_map);
            // add points for my_play
            total_score+=my_play_score[my_play];

        }
    input_file.close();
    }
    std::cout << "Total Score: " << total_score << std::endl;
}

std::string GetMyPlay(std::string& opponent_play, std::string& ending,
                      std::unordered_map<std::string,std::string>& lost_map, 
                      std::unordered_map<std::string,std::string>& draw_map, 
                      std::unordered_map<std::string,std::string>& win_map) {

    if (ending == "X") {
        return lost_map[opponent_play];
    }
    else if (ending == "Y") {
        return draw_map[opponent_play];
    }
    else {
        return win_map[opponent_play];
    }
}
