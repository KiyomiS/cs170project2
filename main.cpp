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
// double leave_one_out_cross_validation(){
//     srand(time(NULL));
//     return rand()%100;
// };

double leave_one_out_cross_validation(vector<vector<double>> instance){ //data, current_set_of_features, j+1)
    for(int i = 0; i < instance.size(); i++){
        double nearest_neighbor_dist = 0;
        int nearest_neighbor_loc = 0;
        int nearest_neighbor_label = 0;
        bool first = true;
        for(int j = 0; j < instance.size(); j++){
            //check for nearest neighbor
            if(j != i) {
                double distance = 0;
                for(int k = 1; k < instance[j].size(); k++){
                    //string input;
                    //cout << instance[j][k] << endl;
                    //cout << instance[j + 1][k] << endl;
                    double minus = instance[j][k] - instance[j + 1][k];
                    //cout << minus << endl;
                    distance += pow(minus, 2);
                    //cout << distance << endl;
                    //cin >> input;
                }
                double square = sqrt(distance);
                distance = square;
                //cout << distance << endl;
                if((distance < nearest_neighbor_dist) || (first == true)){ //if distance is less than or its the first instance
                    cout << "updating distance" << endl;
                    nearest_neighbor_dist = distance;
                    nearest_neighbor_loc = j;
                    nearest_neighbor_label = instance[j][0]; //getting what class nearest neighbor is.
                }
                
                cout << "Ask if " << i << " is nearest neighbor with " << j << endl;
            }
            cout << "enter j loop" << endl;
        }
        cout << "hello?" << endl;
        cout << "Object " << i << " is class " << instance[i][0] << endl;
        cout << "It's nearest neighbor is " << nearest_neighbor_loc << " which is in class " << nearest_neighbor_label << endl;
    }
};

int main() {
    int input;

    cout << "Welcome to my project 2." << endl;
    string filename = "Ver_2_CS170_Fall_2021_Small_data__28.txt";
    ifstream testfile;
    vector <vector<double>> instance;
    //vector <double> empty;
    double numerical_data = 0;
    string content;
    string space;
    
    
    testfile.open(filename);
    if (testfile.is_open()){
        int j = 0;
        while(getline(testfile, space)){
            //features = empty;
            vector <double> features {};
            stringstream line(space);
            int i = 0;
            while(line >> content) {
                if( i == 11){
                     i = 0;
                }
                numerical_data = stof(content);
                //cout << numerical_data << endl;
                features.push_back(numerical_data);
                //cout << features[i] << endl;
                i++;
            }
            instance.push_back(features);
            //cout << instance[i][j] << endl;
            j++;
        }
    }
    //cout << setprecision(8);
    //cout << features[1] << endl;
    //cout << instance[1][1] << endl;
    //cout << instance[2][1] << endl;
    cout << instance.size();
    double d = leave_one_out_cross_validation (instance);


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
               double accuracy;// = leave_one_out_cross_validation(instance);//data, current_set_of_features, j+1);
                if(accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level.push_back(j);
                }
            }
        };
        cout << "On level " << i << " i added feature " << endl;
    };
};