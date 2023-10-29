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
        vector<string> orderedMinterms = PrintBinaryMinterms(minterms);

            // Step 1: List all the minterms ordered by the number of 1's
//            vector<string> orderedMinterms = listMintermsOrderedByOnes(minterms);

            cout << "Minterms Ordered by Number of 1's: ";
            for (const string &minterm : orderedMinterms) {
                cout << minterm << " " << endl;
            }
            cout << endl;

            // Step 2: Generate prime implicants
            vector<string> primeImplicants = generatePrimeImplicants(orderedMinterms);

            cout << "Prime Implicants: ";
            for (const string &implicant : primeImplicants) {
                cout << implicant << " " << endl;
            }
            cout << endl;
    }
    else
    {
        cout << "cant process the truth table ... Expression INVALID" << endl;
    }
    
    return 0;
}
