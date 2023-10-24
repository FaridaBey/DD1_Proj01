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
    getline(cin, expression);cout << endl;
    
    if (validation(expression))
     {
         cout << endl <<"1 1 1 Valid Expression 1 1 1\n";
     }
     else
     {
         cout << endl << "0 0 0 Invalid Expression 0 0 0\n";
     
     }
     if (isSOP(expression))
     {
         cout<< "            SOP\n";
     }
     else
     {
         cout<< "            POS\n";
     }

    PrintTruthTable(expression);
    
     return 0;
 }
