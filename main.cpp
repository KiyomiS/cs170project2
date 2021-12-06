#include "node.h"
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


//void forwardSelection();
// double leave_one_out_cross_validation(){
//     srand(time(NULL));
//     return rand()%100;
// };



double leave_one_out_cross_validation(vector<vector<double>> instance, vector<int> current_set, int addFeature);
Node forwardSelection(vector<vector<double>> instance);


int main() {
    int input;

    cout << "Welcome to my project 2." << endl;
    string filename;
    ifstream testfile;
    vector <vector<double>> instance;
    //vector <double> empty;
    vector <double> features;
    double numerical_data = 0;
    string content;
    string space;
    double accuracy = 0;
    Node result;

    cout << "Which data set would you like to test?\n" << "1. Small\n" << "2. Large.\n" << endl;
    cin >> input;
    
    if (input == 1) {
        filename = "Ver_2_CS170_Fall_2021_Small_data__86.txt";
    }
    else if (input == 2) {
        filename = "Ver_2_CS170_Fall_2021_LARGE_data__17.txt";
    } else {
        cout << "Invalid choice. Will use default choice (small)" << endl;
    };

    //loading data
    testfile.open(filename);
    if (testfile.is_open()){
        while(getline(testfile, space)){
            //features = empty;

            stringstream line(space);

            while(line >> content) {
                numerical_data = stof(content);
                //cout << numerical_data << endl;
                features.push_back(numerical_data);
                //cout << features[i] << endl;
            }
            instance.push_back(features);
            features.clear();
        }
    }

    // accuracy = leave_one_out_cross_validation(instance);
    // cout << accuracy << "%" << endl;

    result = forwardSelection(instance);
    result.print();

    return 0;
};

Node forwardSelection(vector<vector<double>> instance) {
    Node best;
    int size = 10;
    bool isHere = false;
    vector<int> current_set_of_features;
    int feature_to_add_at_this_level;
    vector<int> best_overall;
    double best_overall_acc = 0.0;

    for (int i = 0; i < instance[0].size() - 1; i++){
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        feature_to_add_at_this_level = {};
        double best_so_far_accuracy = 0;
        for(int j = 1; j < instance[i].size(); j++) {
            
            for(int l = 0; l < current_set_of_features.size(); l++){
                if (j == current_set_of_features[l]){
                    isHere = true;
                }
            }

            if(isHere == false) {
                // Node node = new Node(best);
                // node.addFeature(j);
                cout << "--Considering adding the " << j << " feature" << endl;
                double accuracy = leave_one_out_cross_validation(instance, current_set_of_features, j); //data, current_set_of_features, j+1);
                //cout << accuracy << endl;
                if(accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = j;
                    
                }
            }
            isHere = false;
        }

        if(best_overall.size() == 0) {
            best_overall.push_back(feature_to_add_at_this_level);
            best.addFeature(feature_to_add_at_this_level);
            best.setAcc(best_so_far_accuracy);
        } else if(best_so_far_accuracy > best_overall_acc){
            best_overall_acc = best_so_far_accuracy;
            best.setAcc(best_so_far_accuracy);
            best_overall.push_back(feature_to_add_at_this_level);
            best.addFeature(feature_to_add_at_this_level);
        }
        current_set_of_features.push_back(feature_to_add_at_this_level);
        // best.addFeature(feature_to_add_at_this_level);
        cout << "On level " << i + 1 << " i added feature " << feature_to_add_at_this_level << endl;
        cout << best_overall_acc << endl;
    }
    return best;
};

double leave_one_out_cross_validation(vector<vector<double>> instance, vector<int> current_set, int addFeature){ //data, current_set_of_features, j+1)
    double nearest_neighbor_dist = 0;
    int nearest_neighbor_loc = 0;
    int nearest_neighbor_label = 0;
    double correct = 0.0;
    double acc = 0;
    bool isThere = false;
    double distance = 0;
    bool first = true;

    for(int i = 0; i < instance.size(); i++){   
        
        for(int j = 0; j < instance.size(); j++){
            //check for nearest neighbor
            if(j != i) {
                for(int k = 1; k < instance[j].size(); k++){
                    //string input;
                    //cout << instance[j][k] << endl;
                    //cout << instance[j + 1][k] << endl;
                    for(int l = 0; l < current_set.size(); l++){  //find out if feature is in current set or not
                        if(k == current_set[l]){
                            isThere = true;
                        }
                    }

                    if((isThere == true) || (k == addFeature)) { //if feature is in current set then calculate distance
                        //double minus = instance[i][k] - instance[j][k];
                        //cout << minus << endl;
                        distance += pow((instance[i][k] - instance[j][k]), 2);
                        isThere = false;
                    }
                    //cout << distance << endl;
                    //cin >> input;
                }
                double square = sqrt(distance);
                distance = square;
                //cout << distance << endl;
                if((distance < nearest_neighbor_dist) || (j == 0) || (first == true)){ //if distance is less than or its the first instance or its the zeroth instance and j = 1 has to be included
                    // cout << "updating distance" << endl;
                    nearest_neighbor_dist = distance;
                    nearest_neighbor_loc = j;
                    nearest_neighbor_label = instance[j][0]; //getting what class nearest neighbor is.
                    first = false;
                }
                distance = 0;
                
                //cout << "Ask if " << i << " is nearest neighbor with " << j << endl;
            }
            //cout << "enter j loop" << endl;
        }
        // cout << "Object " << i << " is class " << instance[i][0] << endl;
        // cout << "It's nearest neighbor is " << nearest_neighbor_loc << " which is in class " << nearest_neighbor_label << endl;
        if (instance[i][0] == nearest_neighbor_label){
            correct += 1;
        }
    }
    acc = correct * 100.0 /instance.size();
    cout << acc << endl;
    return acc;
};