#include <iostream>
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
    }
}
