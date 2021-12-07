#include <iostream>
#include <vector>
using namespace std;

class Node{
    private: 
        double accuracy;
        vector<int> features;
    public:
        Node(){
            features = {};
            accuracy = 0;
        };

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

        void addFeature(int n) {
            features.push_back(n);
        }

        void print() {
            for(int i = 0; i < features.size(); i++) {
                cout << features[i] << " ";
            }
        }

        double getAcc (){
            return accuracy;
        }

        void remove(int j){
            int index; 
            for(int i = 0; i < features.size(); i++){
                if(features[i] == j) {
                    index = i;
                }
            }
            if(index == features.size() - 1) {
                features.pop_back();
            } else {
                swap(features[index], features[features.size() - 1]);
                features.pop_back();
            }
        }

        void setfeature(vector<int> feat){
            this->features = feat;
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