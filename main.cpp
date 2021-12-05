#include "node.h"
#include "cross_validation.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


void forwardSelection();
double leave_one_out_cross_validation(){
    srand(time(NULL));
    return rand()%100;
};

int main() {
    int input;

    cout << "Welcome to my project 2." << endl;
    string filename = "Ver_2_CS170_Fall_2021_Small_data__28.txt";
    ifstream testfile;
    vector <vector<double>> objects;
    vector <double> features;
    double numerical_data = 0;
    string content;
    string space;
    
    
    testfile.open(filename);
    if (testfile.is_open()){
        while(getline(testfile, space)){

            stringstream line(space);
            while(line >> content) {
                //setprecision(10);
                //cout << content << endl;
                numerical_data = stof(content);
                //cout << numerical_data << endl;
                features.push_back(numerical_data);
            }
            objects.push_back(features);
        }
    }
    cout << setprecision(8);
    cout << features[1] << endl;
    cout << objects[1][0] << endl;

    return 0;
    // cout << "Which data set would you like to test?\n" << "1. Small\n" << "2. Large.\n" << endl;
    // cin >> input;
    
    // if (input == 1) {
    //     forwardSelection();
    // }
    // else if (input == 2) {
    // } else {
    //     cout << "Invalid choice. Will use default choice (small)" << endl;
    // };

};

void forwardSelection() {
    Node root;
    Node best;
    int size = 10;
    vector<double> current_set_of_features;
    vector<double> feature_to_add_at_this_level;

    for (int i = 1; i < size; i++){
        cout << "On the " << i << "th level of the search tree" << endl;
        feature_to_add_at_this_level = {};
        double best_so_far_accuracy = 0;
        for(int j = 1; j < size; j++) {
            if(best.featurePresent(j) == false) {
                cout << "--Considering adding the " << j << " feature" << endl;
                double accuracy = leave_one_out_cross_validation();//data, current_set_of_features, j+1);
                if(accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level.push_back(j);
                }
            }
        };
        cout << "On level " << i << " i added feature " << endl;
    };
};