//
//  functions_1.h
//  proj1_dd
//
//  Created by Farida Sherif on 20/10/2023.
//

#ifndef functions_1_h
#define functions_1_h
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

// function checks whether a given Boolean expression is a valid POS or SOP.
bool validation (string& boolean_exp)
{
    // Define valid operators and count of variables
    vector<char> Val_operands = {'+', '(', ')', '.',' ', '\''} ;
    int var_count = 0;
    
    for (int i=0; i < boolean_exp.length(); i++) {
        boolean_exp[i] = tolower(boolean_exp[i]); // Convert all variables to lowercase
        
        if(boolean_exp[i] == ' ')
            boolean_exp.erase(remove(boolean_exp.begin(), boolean_exp.end(), ' '), boolean_exp.end()); // Remove spaces
        if(empty(boolean_exp)){
            cout << "no expression\n"; // The expression can't be empty
            return false;
        }
        if(isalpha(boolean_exp[i])){
            var_count ++; // Count the number of variables
        }
        if(var_count > 10){
            cout << "too many variables\n"; // No more than 10 variables
            return false;
        }
    }
    
    for(char oper : Val_operands){
        
        if((boolean_exp[0] == oper && boolean_exp[0] != '(' ) || (boolean_exp[boolean_exp.length()-1] == oper && boolean_exp[boolean_exp.length()-1] != ')'))
        {
            cout << "function invalid \n"; // if expression starts with an operator other than '(' or ends with an operator other than ')'it is invalid
            return false;
        }
        else if((boolean_exp[0] == '(' && boolean_exp[1] == oper) || (boolean_exp[boolean_exp.length()-1] == ')' && boolean_exp[boolean_exp.length()-2] == oper) ){
            cout << "function invalid \n"; // if expression starts with '(' or ends with ')' and the second or second to last term is an operator it is invalid
            return false;
        }
    }

    
   
    cout << boolean_exp << endl;
    return true;
};

#endif /* functions_1_h */

