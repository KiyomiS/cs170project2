#include <iostream>
#include <vector>
using namespace std;

class Node{
    private: 
        double number;
        vector<int> features;
    public:
        Node(){};
        //~Node();

        bool featurePresent(int j){
            for (int i = 0; i < features.size(); i++){
                if(features[i] == j){
                    return true;
                }
            }
            return false;
        };
};