#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define x first
#define y second

int main() {

    // for head 9 only
    std::unordered_map<int, std::unordered_set<int>> keep_track;
    keep_track[0].insert(0);

    // head and tail coordinates
    std::unordered_map<int,std::pair<int,int>> head_map;
    head_map[0] = std::make_pair(0,0);
    head_map[1] = std::make_pair(0,0);
    head_map[2] = std::make_pair(0,0);
    head_map[3] = std::make_pair(0,0);
    head_map[4] = std::make_pair(0,0);
    head_map[5] = std::make_pair(0,0);
    head_map[6] = std::make_pair(0,0);
    head_map[7] = std::make_pair(0,0);
    head_map[8] = std::make_pair(0,0);
    head_map[9] = std::make_pair(0,0);

    // init head
    std::pair<int,int>& head = head_map[0];

    // loop through input
    std::ifstream input_file;
    input_file.open("input_file");
    std::string current_line;
    if (input_file.is_open()) {
        while (std::getline(input_file, current_line)) {

            // get letter for direction and number of moves in that direction
            int first_space_idx = current_line.find(' ');
            std::string letter = current_line.substr(0, first_space_idx);
            int moves = stoi(current_line.substr(first_space_idx+1));
            
            // head movement
            // for number of moves in direction
            for (int i = 0; i < moves; i++) {

                // update head coordinates based on input
                // if U: y+<num> | if D: y-<num> | if L: x-<num> | if R: x+<num>
                if (letter == "U") {
                    head.y+=1;
                }
                else if (letter == "D") {
                    head.y-=1;
                }
                else if (letter == "L") {
                    head.x-=1;
                }
                else if (letter == "R") {
                    head.x+=1;
                }
                else {
                    std::cout << "Something Went Wrong" << std::endl;
                }

                // update each head based on the head movement before it
                for (int i = 1; i < 10; i++) {

                    // head movement based on previous head
                    std::pair<int,int>& head = head_map[i-1];
                    std::pair<int,int>& tail = head_map[i];

                    // after head just moved check if x or y coordinates are over 1 diff
                    // if not no move by tail needed | if so need to move tail
                    int head_distance_from_tail_x = head.x > tail.x ? head.x - tail.x : tail.x - head.x;
                    int head_distance_from_tail_y = head.y > tail.y ? head.y - tail.y : tail.y - head.y;
                    if (head_distance_from_tail_x > 1 || head_distance_from_tail_y > 1) {
                        // up
                        if (head.x == tail.x && head.y > tail.y+1) {
                            tail.y+=1;
                        }
                        // down
                        else if (head.x == tail.x && head.y < tail.y-1) {
                            tail.y-=1;
                        }
                        // right
                        else if (head.y == tail.y && head.x > tail.x+1) {
                            tail.x+=1;
                        }
                        // left
                        else if (head.y == tail.y && head.x < tail.x-1) {
                            tail.x-=1;
                        }
                        // diagonal
                        else  {
                            // up
                            if (head.y > tail.y) {
                                tail.y+=1;
                            }
                            // down
                            if (head.y < tail.y) {
                                tail.y-=1;
                            }
                            // right 
                            if (head.x > tail.x) {
                                tail.x+=1;
                            }
                            // left
                            if (head.x < tail.x) {
                                tail.x-=1;
                            }
                        }
                    }
                    // update head 9 coordinates
                    if (i == 9) {
                        keep_track[tail.x].insert(tail.y);
                    }
                }
            }
        }
        input_file.close();
    }
int total_unique_visits = 0;
for (const auto i : keep_track) {
    total_unique_visits+=i.second.size();
}
std::cout << "Number of Coordinates Visited Once By Head 9: " << total_unique_visits << std::endl;
}
