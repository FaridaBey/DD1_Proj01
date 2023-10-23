#include <iostream>
#include <vector>
#include "../functions_1.h"
using namespace std;

int main() {

//---------------------------Intro----------------------------------------
    cout<< "Welcome to the Logic Minimization Tool!\n";
    cout<< "\nPlease enter a Boolean expression in SOP or POS form: \n";
    cout<< " Example (SOP): ab + bc + ca \n";
    cout<< " Example (POS): (a + b + c)(a + b + c') \n";
    cout<< "\nYour expression: ";
    
//-----------------------User Input and Validation-----------------------

    string expression;
    getline(cin, expression);
    validation(expression);
    PrintTruthTable(expression);
    return 0;
}
