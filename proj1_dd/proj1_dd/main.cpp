#include <iostream>
#include <vector>
#include "../Printing.h"
#include "../Validation.h"
#include "../PrimeImplicants.h"
using namespace std;

int main()
{

    //---------------------------Intro----------------------------------------
    cout << "🅀 🅄 🄸 🄽 🄴  🄼 🄲 🄲 🄻 🅄 🅂 🄺 🄴 🅈\n";
    cout << "Welcome to the Logic Minimization Tool!\n";
    cout << "\nPlease enter a Boolean expression in SOP or POS form: \n";
    cout << " Example (SOP): ab + bc + ca \n";
    cout << " Example (POS): (a + b + c)(a + b + c') \n";
    cout << "\nYour expression: ";

    //-----------------------User Input and Validation-----------------------

    string expression;
    getline(cin, expression);
    cout << endl;

    if (validation(expression))
    {
        cout << endl
             << "Valid Expression\n";
    }
    else
    {
        cout << endl
             << "Invalid Expression! \n";
    }
    if (isSOP(expression))
    {
        cout << "            SOP\n";
    }
    else
    {
        cout << "            POS\n";
    }

    if (validation(expression))
    {
        string bool_exp = transform(expression);
        cout << " \t" << bool_exp << "\n"; // for testing the transform function
        vector<string> minterms = printTruthTable(bool_exp);
        PrintBinaryMinterms(minterms);
    }
    else
    {
        cout << "cant process the truth table ... Expression INVALID" << endl;
    }
}
