#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// first row A: Rock | B: Paper | C: Scissors
// seconds row X: Rock | Y: Paper | Z: Scissors
// points second row 1 for Rock | 2 for Paper | 3 for Scissors
// plus score for the outcome of round | 0 if you lost, 3 if the round was a draw, and 6 if you won

int ResultOfRound(std::string& my_play, std::string& opponent_play, 
                  std::unordered_map<std::string,std::string>& string_to_play);

int main() {

    // points map for my_play
    std::unordered_map<std::string,int> my_play_score;
    my_play_score["X"] = 1;  // rock
    my_play_score["Y"] = 2;  // paper
    my_play_score["Z"] = 3;  // scissors
                             
    // string to play
    std::unordered_map<std::string,std::string> string_to_play;
    string_to_play["A"] = "rock";
    string_to_play["B"] = "paper";
    string_to_play["C"] = "scissors";
    string_to_play["X"] = "rock";
    string_to_play["Y"] = "paper";
    string_to_play["Z"] = "scissors";
    
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
            std::string my_play = current_line.substr(current_line.find(" ") + 1);

            // add to total based on my_play
            total_score+=my_play_score[my_play];

            // add points for result of round
            total_score+= ResultOfRound(my_play, opponent_play, string_to_play);

        }
    input_file.close();
    }
    std::cout<< "Total Score: " << total_score << std::endl;
}

int ResultOfRound(std::string& my_play, std::string& opponent_play, 
                  std::unordered_map<std::string,std::string>& string_to_play) {

    // draw
    if (string_to_play[my_play] == string_to_play[opponent_play]) {
        return 3;
    }
    // win | rock > scissors | scissors > paper | paper > rock
    else if ((my_play == "X" && opponent_play == "C") || 
             (my_play == "Z" && opponent_play == "B") || 
             (my_play == "Y" && opponent_play == "A")) {
        return 6;
    }
    // lost
    else {
        return 0;
    }
}
