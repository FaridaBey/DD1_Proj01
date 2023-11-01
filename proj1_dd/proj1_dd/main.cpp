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
             << "Valid Expression: ";
    }
    else
    {
        cout << endl
             << "Invalid Expression! \n";
    }
    if (isSOP(expression))
    {
        cout << "SOP\n";
    }
    else
    {
        cout << "POS\n";
    }

    if (validation(expression))
    {
        string bool_exp = transform(expression);
        // cout << " \t" << bool_exp << "\n"; // for testing the transform function

//--------------------------------------- Printing the TRUTH TABLE ---------------------------------------------
        cout << "\n\n";
        vector<string> minterms = printTruthTable(bool_exp);
        cout << "\n\n";
        vector<string> Minterms = PrintBinaryMinterms(minterms); // binary
        vector<int> decimalMinterms = PrintDecimalMinterms(Minterms);//decimal

//--------------------------------------- Printing the PI ------------------------------------------------------
        //        vector<string> primeImplicants = generatePrimeImplicants(Minterms);
        //        printPrimeImplicant_1(primeImplicants, Minterms);

        map<string, string> PI = generatePrimeImplicants(Minterms);
        printMintermsCoveredByPrimeImplicant(PI);

//----------------------------------------- Printing the EPI -------------------------------------------------
        vector<string> EPIterms;
        vector<string> EPI = generateEssentialPrimeImplicants(PI);
        // print EPI
        cout << "\n\nEssential Prime Implicants: \n";
        for (int i = 0; i < EPI.size(); i++)
        {
            cout << i+1 << ": " <<EPI[i] << "\n";
        }
//--------------------------------------- Printing non-EPI --------------------------------------------------
         vector<string> nonEPIMinterms = generateMintermsNOTCoveredByEPI(PI, decimalMinterms, EPI);
        cout<<"\n\nMinterms not covered by EPI: \n";
        if(nonEPIMinterms.size()==0)
        {
            cout<<"None";
        }
        else
        {
            for (int i = 0; i < nonEPIMinterms.size(); i++)
            {
                cout << i+1 << ": " << nonEPIMinterms[i] << "\n";
            }
        }
//-------------------------------- Printing Minimized Boolean Expression --------------------------------
        string minimizedExpression = generateMinimizedExpression(EPI, nonEPIMinterms,PI);
        
        cout << "\n\nMinimized Boolean Expression: " << minimizedExpression << endl;
        
//-------------------------------------- Printing the K-MAP ----------------------------------------------------
        cout << "\n\n\t\t\tK-MAP\t\t\n\n";
        vector<char> variables = extractVar(bool_exp);
        vector<string> Kminterms = PrintBinaryMinterms(minterms); // removed the "Minterms in sorted binary form:" from printbinary func
        print_KMap(Kminterms, variables);
        cout << "\n";
    }

    else
    {
        cout << "cant process the truth table ... Expression INVALID" << endl;
    }

    return 0;
}
