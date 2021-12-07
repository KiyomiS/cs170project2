#include "node.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


//void forwardSelection();
// double leave_one_out_cross_validation(){
//     srand(time(NULL));
//     return rand()%100;
// };



double leave_one_out_cross_validation(vector<vector<double>> instance, vector<int> current_set, int addFeature, bool rem);
Node forwardSelection(vector<vector<double>> instance);
Node backwardElimination(vector<vector<double>> instance);

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
        filename = "Ver_2_CS170_Fall_2021_Small_data__28.txt";
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

    cout << "What algorithm?" << endl;
    cin >> input;
    clock_t tStart = clock();
    if(input == 1) {
        result = forwardSelection(instance);
    } else if (input == 2){
        result = backwardElimination(instance);
    } else {
        cout << "wrong input try again" << endl;
    }
    result.print();
    cout << endl << "Time taken was: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
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
        feature_to_add_at_this_level = 0;
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
                double accuracy = leave_one_out_cross_validation(instance, current_set_of_features, j, false); //data, current_set_of_features, j+1);
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

Node backwardElimination(vector<vector<double>> instance){
    vector<int> current_set_of_features;
    int feature_to_add_at_this_level;
    bool isHere = false;
    Node best;
    //vector<int> best_overall;
    double best_overall_acc = 0.0;

    for(int m = 1; m < instance[0].size(); m++){ //populate all features ignore 0 cause that holds class
        current_set_of_features.push_back(m);
        best.addFeature(m);
    }

    for(int i = 0; i < instance[0].size() - 1; i++){
        cout << "On the " << i << "th level of the search tree" << endl;
        feature_to_add_at_this_level = 0;
        double best_so_far_accuracy = 0;

        for(int j = 1; j < instance[i].size(); j++) {
            
            for(int l = 0; l < current_set_of_features.size(); l++){
                if (j == current_set_of_features[l]){
                    isHere = true;
                }
            }

            if(isHere == true) {
                // Node node = new Node(best);
                // node.addFeature(j);
                cout << "--Considering removing the " << j << " feature" << endl;
                // for(int lm = 0; lm < current_set_of_features.size(); lm++){
                //     cout << current_set_of_features[lm] << " ";
                // }
                // cout << endl;
                int index; 
                vector<int> temp = current_set_of_features;
                for(int o = 0; o < temp.size(); o++){
                    if(temp[o] == j) {
                        index = o;
                    }
                }
                
                if(index == temp.size() - 1){ //if its at the back just remove it
                    temp.pop_back();
                } else {
                    swap(temp[index], temp[temp.size() - 1]);
                    temp.pop_back();
                }
                double accuracy = leave_one_out_cross_validation(instance, temp, j, true); //data, current_set_of_features, j+1);
                //cout << accuracy << endl;
                if(accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = j;
                    
                }
            }
            isHere = false;
        }

        int index; 
        for(int o = 0; o < current_set_of_features.size(); o++){
            if(current_set_of_features[o] == feature_to_add_at_this_level) {
                index = o;
            }
        }        
        if(index == current_set_of_features.size() - 1){ //if its at the back just remove it
            current_set_of_features.pop_back();
        } else {
            swap(current_set_of_features[index], current_set_of_features[current_set_of_features.size() - 1]);
            current_set_of_features.pop_back();
        }

        if(best.getfeatures().size() == instance[0].size()) {
            
            best.remove(feature_to_add_at_this_level);
            best.setAcc(best_so_far_accuracy);
            //best_overall.remove(feature_to_add_at_this_level)

        } else if(best_so_far_accuracy > best_overall_acc){
            best_overall_acc = best_so_far_accuracy;
            best.setAcc(best_so_far_accuracy);
            best.setfeature(current_set_of_features);
            //cout << endl << feature_to_add_at_this_level << endl;
        }


        // cout << "current set shit ";
        // cout << current_set_of_features.size() << endl;
        // cout << "best set " << endl;
        // best.print();
        // cout << endl;
        // for(int lm = 0; lm < current_set_of_features.size(); lm++){
        //     cout << current_set_of_features[lm] << " ";
        // }
        //  cout << endl;
        // best.addFeature(feature_to_add_at_this_level);
        cout << "On level " << i + 1 << " i removed feature " << feature_to_add_at_this_level << endl;
        cout << best_overall_acc << endl;
    }
    //best.remove(2);
    return best;
}


double leave_one_out_cross_validation(vector<vector<double>> instance, vector<int> current_set, int addFeature, bool rem){ //data, current_set_of_features, j+1)
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
                    if(rem == false){//forward selection
                        if((isThere == true) || (k == addFeature)) { //if feature is in current set then calculate distance
                            //double minus = instance[i][k] - instance[j][k];
                            //cout << minus << endl;
                            distance += pow((instance[i][k] - instance[j][k]), 2);
                            isThere = false;
                        }
                    } else { //backward elim
                        if((isThere == true)) { //if feature is in current set then calculate distance
                            distance += pow((instance[i][k] - instance[j][k]), 2);
                            isThere = false;
                        }
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