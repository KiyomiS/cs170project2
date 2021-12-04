#include "node.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int input;

    cout << "Welcome to my project 2." << endl;
    
    cout << "Which data set would you like to test?\n" << "1. Small\n" << "2. Large.\n" << endl;
    cin >> input;
    
    if (input == 1) {
    }
    else if (input == 2) {
    } else {
        cout << "Invalid choice. Will use default choice (small)" << endl;
    };

};

Node forwardSelection() {
    Node root;
    Node best;
    int size;
    vector<double> current_set_of_features;
    vector<double> feature_to_add_at_this_level;

    for (int i = 0; i < size; i++){
        cout << "On the " << i << "th level of the search tree" << endl;
        feature_to_add_at_this_level = {};
        double best_so_far_accuracy = 0;
        for(int j = 0; j < size; j++) {
            if(best.featurePresent(j) == false) {
                cout << "--Considering adding the " << j << " feature" << endl;
                double accuracy = leave_one_out_cross_validation(data, current_set_of_features, j+1);
                if(accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level.push_back(j);
                }
            }
        };
        cout << "On level " << i << " i added feature " << endl;
    };
};