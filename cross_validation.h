#include <iostream>
using namespace std;

class cross_validation{
    private:
    public:
        void leave_one_out_cross_validation(vector<vector<double>> instance){ //data, current_set_of_features, j+1)
            for(int i = 0; i < instance.size(); i++){
                for(int j = 0; j < instance.size(); j++){
                    //check for nearest neighbor
                    cout << "Ask if " << i << " is nearest neighbor with " << j << endl;
                }
            }
        };
};