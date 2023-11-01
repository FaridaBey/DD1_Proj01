#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#ifndef Printing_h
#define Printing_h
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <stack>
#include <set>
#include <map>
#include <cmath>
#include <iomanip>
#include <ios>
#include <bitset>
#include <unordered_map>
using namespace std;



//----------------------------TESTING-------------------------------------

// Function to extract prime implicants from canonical SoP expression
vector<string> extractPrimeImplicants(const string &sopExpression) {
    vector<string> terms; // Split the SoP expression into terms
    string term = "";
    for (char c : sopExpression) {
        if (c == '+') {
            terms.push_back(term);
            term = "";
        } else {
            term += c;
        }
    }
    terms.push_back(term); // Add the last term

  //  vector<string> primeImplicants;

    //print the prime implicants
    cout << "\n\n\n terms: ";
    for (size_t i = 0; i < terms.size(); i++) {
        cout << terms[i];
        if (i < terms.size() - 1) {
            cout << " ";
        }
    }

   // return primeImplicants;
   return terms;
}
//---------------------------TESTING----------------------------------------







//--------------- Helper functions for Print ------------------

// Function to transform the expression to the standered or, and, not
string transform(string exp)                                                     // needs more check for bugs !!!!
{
    for(int i = 0; i< exp.length(); i++){
        if(exp[i] == '+')
        {
            exp[i] = '|'; // replace every + with the or sign
        }
        else if(exp[i] == '\''){
            exp.erase(i,1);//remove the '
            exp.insert(i-2,1,'!'); // add ! infront of the variabel
            
        }
        else if((isalpha(exp[i]) && (isalpha(exp[i + 1]) || exp[i + 1] == '\'' || exp[i + 1] == '(')) || (exp[i] == ')' && exp[i+1] == '(')) {
            exp.insert(i + 1, 1,'&'); // add & in the correct pos
        }
    }
    for(int i = 0; i< exp.length(); i++){
        if(exp[i] == '&' && exp[i+1] == '|')
        {
            exp.erase(i,1);//remove the &
        }
        else if(exp[i] == '&' && i == exp.length()-1 )
        {
            exp.erase(i,1);//remove the &
        }
        else if(exp[i] == '&' && exp[i+1] == ')')
        {
            exp.erase(i,1);//remove the &
        }
    }
    return exp;

}
// Function to check the operators
bool isOperator(char c) {
    return c == '&' || c == '|' || c == '!';
}
// Function that hepls in handeling the precedence
int getPrecedence(char c) {
    if (c == '!') return 3;
    if (c == '&') return 2;
    if (c == '|') return 1;
    return 0;
}
// Function to convert the expression output to binary
bool convert_exp(const string& expression) {
    stack<bool> operandStack;
    stack<char> operatorStack;
    unordered_map<char, bool> variables;

    for (char c : expression) {
        if (c == '0' || c == '1') {
            operandStack.push(c == '1');
        } else if (c == '!' || c == '&' || c == '|') {
            while (!operatorStack.empty() &&
                   getPrecedence(operatorStack.top()) >= getPrecedence(c)) {
                char op = operatorStack.top();
                operatorStack.pop();

                if (op == '!') {
                    bool operand = operandStack.top();
                    operandStack.pop();
                    operandStack.push(!operand);
                } else {
                    bool operand2 = operandStack.top();
                    operandStack.pop();
                    bool operand1 = operandStack.top();
                    operandStack.pop();

                    if (op == '&') {
                        operandStack.push(operand1 && operand2);
                    } else if (op == '|') {
                        operandStack.push(operand1 || operand2);
                    }
                }
            }
            operatorStack.push(c);
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();

                if (op == '!') {
                    bool operand = operandStack.top();
                    operandStack.pop();
                    operandStack.push(!operand);
                } else {
                    bool operand2 = operandStack.top();
                    operandStack.pop();
                    bool operand1 = operandStack.top();
                    operandStack.pop();

                    if (op == '&') {
                        operandStack.push(operand1 && operand2);
                    } else if (op == '|') {
                        operandStack.push(operand1 || operand2);
                    }
                }
            }
            operatorStack.pop(); // Remove the '('
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();

        if (op == '!') {
            bool operand = operandStack.top();
            operandStack.pop();
            operandStack.push(!operand);
        } else {
            bool operand2 = operandStack.top();
            operandStack.pop();
            bool operand1 = operandStack.top();
            operandStack.pop();

            if (op == '&') {
                operandStack.push(operand1 && operand2);
            } else if (op == '|') {
                operandStack.push(operand1 || operand2);
            }
        }
    }

    return operandStack.top();
}


//------------------------------TRUTH TABLE & Canonical SoP/PoS-------------------------------------

/*
    the output needs more organization --> variables output in alphabetical order
 */
//count var

// funtcion to print the truth table and canonical PoS/SoP, returns the canonical SoP
vector<string> printTruthTable(const string &expression) {
    int numVariables = 0;
    vector<char> variables;
    vector<string> minterms;  // To store minterms
    vector<string> maxterms;  // To store maxterms
    
    // Extract variables from the expression
    for (char c : expression) {
        if (isalpha(c) && find(variables.begin(), variables.end(), c) == variables.end()) {
            variables.push_back(c);
            numVariables++;
        }
    }
    
    //sort(variables.begin(), variables.end()); to sort the truth table header only

    int numRows = pow(2, numVariables);
    
    // Print the header row with variable names
    for (char var : variables) {
        cout << var << " ";
    }
    cout << "| " << expression << endl;
    
    // Print a separator line
    for (int i = 0; i < numVariables; i++) {
        cout << "- ";
    }
    cout << "| ";
    for (int i = 0; i < expression.length(); i++) {
        cout << "-";
    }
    cout << endl;
    
    // Generate and print the truth table
    for (int row = 0; row < numRows; row++) {
        vector<int> variableValues;
        int temp = row;
        for (int i = 0; i < numVariables; i++) {
            variableValues.push_back(temp % 2);
            temp /= 2;
        }
        
        for (int i = 0; i < numVariables; i++) {
            cout << variableValues[i] << " ";
        }
        cout << "| ";
        
        // Evaluate the expression for the current variable values
        string evaluationExpression = expression;
        bool  result = false;
        for (int i = 0; i < numVariables; i++) {
            char var = variables[i];
            char varValue = (variableValues[i] == 0) ? '0' : '1';
            for (size_t pos = evaluationExpression.find(var); pos != string::npos; pos = evaluationExpression.find(var, pos)) {
                evaluationExpression.replace(pos, 1, 1, varValue);
                //                result = convert_exp(evaluationExpression);
            }
        }
        result = convert_exp(evaluationExpression);
        cout << result << endl;

        // Collect terms for SoP and PoS
        if (result) {
            string sopTerm = "";
            for (int i = 0; i < numVariables; i++) {
                char var = variables[i];
                char varValue = (variableValues[i] == 0) ? '\'' : ' ';
                sopTerm += var;
                sopTerm += varValue;
                if (i < numVariables - 1) {
                    sopTerm += "";
                }
            }
            minterms.push_back(sopTerm);
        }else {
            string posTerm = "";
            for (int i = 0; i < numVariables; i++) {
                char var = variables[i];
                char varValue = (variableValues[i] == 0) ? '\'' : ' ';
                posTerm += var;
                posTerm += varValue;
                if (i < numVariables - 1) {
                    posTerm += " + ";
                }
            }
            maxterms.push_back("(" + posTerm + ")");
        }
    }
    
    // Print the canonical SoP and PoS expressions
    cout << "Canonical SoP: ";
    for (size_t i = 0; i < minterms.size(); i++) {
        cout << minterms[i];
        if (i < minterms.size() - 1) {
            cout << " +";
        }
    }
    cout << endl;
    
    cout << "Canonical PoS: " ;
    for (size_t i = 0; i < maxterms.size(); i++) {
        cout << maxterms[i];
        if (i < maxterms.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
    return minterms;

}
//function to extract variables: to be used in Kmap
vector<char> extractVar(const string& boolean_exp) {
    vector<char> variableNames;
    
    for (char character : boolean_exp) {
        if (isalpha(character) && islower(character)) {
            variableNames.push_back(character);
        }
    }
    
    return variableNames;
}

// Function to convert a decimal number to Gray code; to output the headers in correct order
int decimalToGray(int num) {
    return num ^ (num >> 1);
}


void print_KMap(const vector<string>& minterms, const vector<char>& variables) {
    // Calculate the number of rows and columns in the K-Map
    int numRows = pow(2, variables.size() / 2);
    int numCols = pow(2, (variables.size() + 1) / 2);

    // Create a 2D vector to represent the K-Map
    vector<vector<char>> kMap(numRows, vector<char>(numCols, '0'));

    // Fill in the K-Map with '1's based on the minterms
    for (int i = 0; i < minterms.size(); i++) {
        // Convert minterm to binary representation (assuming it's a binary number)
        string binaryMinterm = minterms[i];
        
        
        // ---------------IF THERE IS AN ERROR-----------------
        
        // Validate the binary minterm format
        if (binaryMinterm.size() != variables.size()) {
            cerr << "Invalid minterm format: " << binaryMinterm << endl;
            continue; // Skip this minterm
        }

        for (char c : binaryMinterm) {
            if (c != '0' && c != '1') {
                cerr << "Invalid character in minterm: " << binaryMinterm << endl;
                continue; // Skip this minterm
            }
        }
        // ----------------------END-------------------

        // Convert binary representation to row and column indices
        int binaryValue = stoi(binaryMinterm, nullptr, 2);
        int row = binaryValue / numCols;
        int col = binaryValue % numCols;

        // Bounds checking
        if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
            // Mark the cell in the K-Map as '1'
            kMap[row][col] = '1';
        } else {
            cerr << "Minterm out of bounds: " << binaryMinterm << endl; // if there is an error
        }
    }

    // Determine the maximum number of bits required for column representation
    int maxbits = ceil(log2(numCols));

    // Print the Karnaugh Map with Gray code representations of row and column indices
    cout << " ";
    for (int i = 0; i < variables.size() / 2; i++) {
        cout << variables[i]; // for header identification
    }
    cout << " |";
    for (int j = 0; j < numCols; j++) {
        cout << " " << setw(maxbits) << bitset<2>(decimalToGray(j)) << "  |";
    }
    cout << endl;

    for (int i = variables.size() / 2; i < variables.size(); i++) {
        cout << variables[i]; // for header identification
    }
    cout << " ";
    cout << "|";
    for (int j = 0; j < numCols; j++) {
        cout << "-----|";
    }
    cout << endl;

    for (int i = 0; i < numRows; i++) {
        cout << setw(variables.size() / 2) << bitset<2>(decimalToGray(i)) << " |";
        for (int j = 0; j < numCols; j++) {
            cout << "  " << kMap[i][j] << "  |";
        }
        cout << endl;
        cout << "---|";
        for (int j = 0; j < numCols; j++) {
            cout << "-----|";
        }
        cout << endl;
    }
}
//----------------------------------------------------------------------------------------------------

#endif /* Printing_h */

#pragma clang diagnostic pop

