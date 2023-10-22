//
//  main.cpp
//  proj1_dd
//
//  Created by Farida Sherif on 20/10/2023.
//

#include <iostream>
#include <vector>
#include "../functions_1.h"
using namespace std;

int main() {
    //testing the function..
    string input ="a + c+dc')";
    validation (input);

    vector<int> test = {1,2,3,4,5,6,7,8,9,15,16};
    sortbyones(test);
    for(int i=0; i<test.size(); i++){
        cout << test[i] << endl;
    }
    
    return 0;
}
