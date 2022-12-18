#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>

void PrintInfoForRound(std::unordered_map<int, long>& monkey_total_inspected);

// number to operation
enum Operators {
    Add = 0, Multiply= 1, Squared = 2
};

int main() {

    // init vector of maps | idx 0-6
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //   parse input into map
    //   monkey_idx: {
    //      starting_items: <int>, // deque of items
    //      operation: <operator_enum, int>, // operator enum and number to change items | then floor division by 3
    //      test: <int>, // if new floor divided number is divisable by this number true, else false
    //      true: int, // monkey_idx to throw to if test is true
    //      false: int, // monkey_idx to throw to if test is false
    //      } 
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::unordered_map<std::string, std::deque<long> > > directions = {   
               {
                   {"starting_items", {83, 88, 96, 79, 86, 88, 70}},
                   {"operation", {1, 5}}, // multiply by 5
                   {"test", {11}},
                   {"true", {2}},
                   {"false", {3}}
               },
               {
                   {"starting_items", {59, 63, 98, 85, 68, 72}},
                   {"operation", {1, 11}}, // multiply by 11
                   {"test", {5}},
                   {"true", {4}},
                   {"false", {0}}
               },
               {
                   {"starting_items", {90, 79, 97, 52, 90, 94, 71, 70}},
                   {"operation", {0, 2}}, // add 2
                   {"test", {19}},
                   {"true", {5}},
                   {"false", {6}}
               },
               {
                   {"starting_items", {97, 55, 62}},
                   {"operation", {0, 5}}, // add 5
                   {"test", {13}},
                   {"true", {2}},
                   {"false", {6}}
               },
               {
                   {"starting_items", {74, 54, 94, 76}},
                   {"operation", {2}}, // squared
                   {"test", {7}},
                   {"true", {0}},
                   {"false", {3}}
               },
               {
                   {"starting_items", {58}},
                   {"operation", {0, 4}}, // add 4
                   {"test", {17}},
                   {"true", {7}},
                   {"false", {1}}
               },
               {
                   {"starting_items", {66,63}},
                   {"operation", {0, 6}}, // add 6
                   {"test", {2}},
                   {"true", {7}},
                   {"false", {5}}
               },
               {
                   {"starting_items", {56, 56, 90, 96, 68}},
                   {"operation", {0, 7}}, // add 7
                   {"test", {3}},
                   {"true", {4}},
                   {"false", {1}}
               },
           };

    // map to keep track of each monkey total inspected
    std::unordered_map<int, long> monkey_total_inspected;

    // number of rounds
    int num_of_rounds = 10000;
    // least divisible number
    long mod_num = 1;
    for (auto& map : directions) {
        mod_num*=map["test"][0];
    }

    //rounds
    for (int i = 0; i < num_of_rounds; i++) {

        // monkey idx
        for (int j = 0; j < directions.size(); j++) {

            // get info for this round of instructions
            auto current_map_info = directions[j];  // directions for this monkey
            int info_map_operation = current_map_info["operation"][0];
            int info_map_operation_num = current_map_info["operation"][1];
            int info_map_test_num = current_map_info["test"][0];
            int info_map_true_monkey_idx = current_map_info["true"][0];
            int info_map_false_monkey_idx = current_map_info["false"][0];

            // list of items
            std::deque<long> current_items = current_map_info["starting_items"]; 
            for (int k = 0; k < current_items.size(); k++) {

                // keep track of each monkey total inspected
                monkey_total_inspected[j]+=1;

                // get current item
                long current_item = current_items[k];
                
                // number after calculations
                long new_number;
                //add
                if (info_map_operation == Add) {
                    new_number = (current_item + info_map_operation_num);
                }
                // multiply
                else if (info_map_operation == Multiply) {
                    new_number = (current_item * info_map_operation_num);
                }
                // squared
                else if (info_map_operation == Squared) {
                    new_number = (current_item * current_item);
                }
                 
                long num_to_send = new_number % mod_num;
                // test if true
                if (new_number % info_map_test_num == 0) {
                    directions[info_map_true_monkey_idx]["starting_items"].push_back(num_to_send);
                } 
                else {
                    directions[info_map_false_monkey_idx]["starting_items"].push_back(num_to_send);
                }
            }
            directions[j]["starting_items"].clear();
        }   
    }
    PrintInfoForRound(monkey_total_inspected);
}

void PrintInfoForRound(std::unordered_map<int, long>& monkey_total_inspected) {

    // print each monkey total inspected
    for (auto& x : monkey_total_inspected) {
        std::cout << x.first << ": " << x.second << std::endl;
    }

    // get top two most inpsected
    long most_inspected = 0;
    long second_most_inspected = 0;
    for (auto& [monkey_idx, total_inspected] : monkey_total_inspected) {
        if (total_inspected > most_inspected) {
            second_most_inspected = most_inspected;
            most_inspected = total_inspected;
        } 
        else if (total_inspected > second_most_inspected) {
            second_most_inspected = total_inspected;
        }
    }
    std::cout << "Most: " << most_inspected << " Second: " << second_most_inspected << std::endl;
    long total_monkey_business = most_inspected * second_most_inspected;
    std::cout << "Monkey Business Total: " << total_monkey_business << std::endl;
}
