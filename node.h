#include <iostream>
#include <vector>
using namespace std;

class Node{
    private: 
        double accuracy;
        vector<int> features;
    public:
        Node(){};
        Node(Node * parent) {
            this->features = parent->getfeatures();
        }

        vector<int> getfeatures(){
            return features;
        }
        //~Node();

        void setAcc (double acc) {
            this->accuracy = acc;
        }

        bool featurePresent(int j){
            for (int i = 0; i < features.size(); i++){
                if(features[i] == j){
                    return true;
                }
            }
            return false;
        }
};