#include <iostream>
#include <vector>
#include "../Printing.h"
#include "../Validation.h"
#include "../PrimeImplicants.h"
#include "../Drawing.h"
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
        vector<char> variables = extractVar(bool_exp);
        // cout << " \t" << bool_exp << "\n"; // for testing the transform function

//--------------------------------------- Printing the TRUTH TABLE --------------------------------
        cout << "\n\n";
        vector<string> minterms = printTruthTable(bool_exp);
        cout << "\n\n";
        vector<string> Minterms = PrintBinaryMinterms(minterms);      // binary
        vector<int> decimalMinterms = PrintDecimalMinterms(Minterms); // decimal


//--------------------------------------- Printing the PI -----------------------------------------

        map<string, string> PI = generatePrimeImplicants(Minterms);
        printMintermsCoveredByPrimeImplicant(PI);

//----------------------------------------- Printing the EPI --------------------------------------
        vector<string> EPIterms;
        vector<string> EPI = generateEssentialPrimeImplicants(PI);
        // print EPI
        cout << "\n\nEssential Prime Implicants: \n";
        for (int i = 0; i < EPI.size(); i++)
        {
            cout << i + 1 <<": "<< final_answer(EPI[i],variables) << " (" << EPI[i] << ") " <<"\n";
        }
//--------------------------------------- Printing non-EPI --------------------------------------
        vector<string> nonEPIMinterms = generateMintermsNOTCoveredByEPI(PI, decimalMinterms, EPI);
        cout << "\n\nMinterms not covered by EPI: \n";
        if (nonEPIMinterms.size() == 0)
        {
            cout << "None";
        }
        else
        {
            for (int i = 0; i < nonEPIMinterms.size(); i++)
            {
                cout << i + 1 << ": " << nonEPIMinterms[i] << "\n";
            }
        }
//-------------------------------- Printing Minimized Boolean Expression --------------------------
        string minimizedExpression = generateMinimizedExpression(EPI, nonEPIMinterms, PI);
        sort(variables.begin(), variables.end());
        cout << "\n\nMinimized Boolean Expression: " << final_answer(minimizedExpression, variables) << endl;

//--------------------------------- Printing the K-MAP --------------------------------------------
        
       
        cout << "\n\n\t\t\tK-MAP\t\t\n";
        print_KMap(decimalMinterms,variables);
        cout << "\n";
        cout << "===============Covers==============\n\n";
        // Loop through each prime implicant and print a K-map
        int i= 0;
        for (const auto &pi : PI) {
            vector<string> minterms = splitMinterms(PI[pi.first]);
            vector<int> mintermIntegers = convertStringVectorToInt(minterms);
            cout << "-----------Cover " << i+1<< "-------------\n";
            print_KMap(mintermIntegers, variables);
            i++;
        }
        cout << "\n";

//------------------------------ Drawing Logic Circuit --------------------------------------------
       string minexp = final_answer(minimizedExpression, variables);
       minexp = removeSpaces(minexp);
        printDrawing(minexp);

    }

    else
    {
        cout << "cant complete processing ... Expression INVALID" << endl;
    }

    return 0;
}
