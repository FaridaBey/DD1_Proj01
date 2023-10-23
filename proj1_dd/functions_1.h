#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#ifndef functions_1_h
#define functions_1_h
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <stack>
#include <set>
using namespace std;

//-----------------------Helper Functions-----------------------
bool balancedParentheses(const string &expression)
{
    stack<char> s;
    for (char c : expression)
    {
        if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            if (s.empty())
            {
                return false;
            }
            else
            {
                s.pop();
            }
        }
    }
    return s.empty();
}
// function checks whether a given Boolean expression is a valid POS or SOP.
bool validation (string& boolean_exp)
{
      if(empty(boolean_exp)){
            cout << "Empty Expression\n"; // The expression can't be empty
            return false;
        }

         boolean_exp.erase(remove(boolean_exp.begin(), boolean_exp.end(), ' '), boolean_exp.end()); // Remove spaces from the expression

//    Define valid operators and count of variables
    vector<char> Val_operands = {'+', '(', ')', '\''} ;
    int var_count = 0;
    
    for (int i=0; i < boolean_exp.length(); i++) {
        boolean_exp[i] = tolower(boolean_exp[i]); // Convert all variables to lowercase
        
        if(isalpha(boolean_exp[i])){
            var_count ++; // Count the number of variables
        }
        if(var_count > 10){
            cout << "too many variables\n"; // No more than 10 variables
            return false;
        }
//        ----------------------Alphabet Validation----------------------
        
        if (!(isalpha(boolean_exp[i]) || any_of(Val_operands.begin(), Val_operands.end(), [&boolean_exp, i](char v) {
            return v == boolean_exp[i];
        }))) {
            cout << "function invalid1" << endl; // Check if the character at index 'i' is an alphabetic character (letter) OR if it matches any character in the 'Val_operands' vector
            return false;
        }
    }
    
    for(char oper : Val_operands){
        if((boolean_exp[0] == oper && boolean_exp[0] != '(' ) || ((boolean_exp[boolean_exp.length()-1] == oper && boolean_exp[boolean_exp.length()-1] != ')') && boolean_exp[boolean_exp.length()-1] != '\''))
        {
            cout << "function invalid \n"; // if expression starts with an operator other than '(' or ends with an operator other than ')' or ' it is invalid
            return false;
                
        }
        else if((boolean_exp[0] == '(' && boolean_exp[1] == oper) || (boolean_exp[boolean_exp.length()-1] == ')' && (boolean_exp[boolean_exp.length()-2] == oper && boolean_exp[boolean_exp.length()-2] != '\'')) || (boolean_exp[boolean_exp.length()-1] == '\'' && (boolean_exp[boolean_exp.length()-2] == oper && boolean_exp[boolean_exp.length()-2] != '\''))){
            cout << "function invalid \n"; // if expression starts with '(' or ends with [ ')' or '] and the second term is an operator it is invalid or second to last term is operator other than ' it is invalid
            return false;
        }
    }
    cout << boolean_exp << endl;
    if (balancedParentheses(boolean_exp)){
        return true;
    }
    
   
    return true;

};

//---------------To be used for QM------------------
bool compareByOnes(int &a, int &b)
{
    int aOnes = __builtin_popcount(a);
    int bOnes = __builtin_popcount(b);
    return aOnes < bOnes;
}

void sortbyones(vector<int> &x)
{
    sort(x.begin(), x.end(), compareByOnes);

}
//--------------------------------------------------

// Function to generate canonical SoP expression (minterms)
string GenerateCanonicalSoP(const vector<vector<bool>>& truthTable, const set<char>& variableNames) {
    string canonical_SoP = "";

    int numRows = truthTable.size();
    int numVariables = variableNames.size();

    for (int i = 0; i < numRows; ++i) {
        bool output = truthTable[i][numVariables];
        if (output) {
            string minterm = "(";
            for (int j = 0; j < numVariables; ++j) {
                char variable = *next(variableNames.begin(), j);
                if (truthTable[i][j]) {
                    minterm += variable;  // Include the variable if it's true (minterm)
                } else {
                    minterm += "!" + string(1, variable);  // Include the negated variable if it's false (!minterm)
                }
                if (j < numVariables - 1) {
                    minterm += " * ";  // Separate variables with "AND" in the minterm
                }
            }
            minterm += ")";
            canonical_SoP += minterm;  // Add the minterm to the SoP expression
            if (i < numRows - 1) {
                canonical_SoP += " + ";  // Separate minterms with "OR" in the SoP expression
            }
        }
    }

    return canonical_SoP;
}

// Function to generate canonical PoS expression (maxterms)
string GenerateCanonicalPoS(const vector<vector<bool>>& truthTable, const set<char>& variableNames) {
    string canonical_PoS = "";

    int numRows = truthTable.size();
    int numVariables = variableNames.size();

    for (int i = 0; i < numRows; ++i) {
        bool output = truthTable[i][numVariables];
        if (!output) {
            string maxterm = "(";
            for (int j = 0; j < numVariables; ++j) {
                char variable = *next(variableNames.begin(), j);
                if (!truthTable[i][j]) {
                    maxterm += variable;  // Include the variable if it's false (maxterm)
                } else {
                    maxterm += "!" + string(1, variable);  // Include the negated variable if it's true (!maxterm)
                }
                if (j < numVariables - 1) {
                    maxterm += " + ";  // Separate variables with "OR" in the maxterm
                }
            }
            maxterm += ")";
            canonical_PoS += maxterm;  // Add the maxterm to the PoS expression
            if (i < numRows - 1) {
                canonical_PoS += " * ";  // Separate maxterms with "AND" in the PoS expression
            }
        }
    }

    return canonical_PoS;
}

// Function to extract variable names from the Boolean expression
set<char> extractVar(const string& boolean_exp) {
    set<char> variableNames;
    
    for (char character : boolean_exp) {
        if (isalpha(character) && islower(character)) {
            variableNames.insert(character);
        }
    }
    
    return variableNames;
}

// Function to assign values to variables in the Boolean expression
void assignValue(string& expression, char variable, bool value) {
    for (char& character : expression) {
        if (character == variable) {
            character = value ? '1' : '0';
        }
    }
}

// Function to evaluate the Boolean expression
bool EvaluateExpression(const string& boolean_exp) {
    //    evaluate the expression ??
    //    return to test the rest
    return false;
}

// Function to print the truth table
void PrintTruthTable(const string& boolean_exp) {
    // Extract variable names from the Boolean expression
    set<char> variableNames = extractVar(boolean_exp);
    int numberOfVar = variableNames.size();
    string truthTableHeader = "";

    // Create the header row for the truth table
    for (char variable : variableNames) {
        truthTableHeader += variable;
        truthTableHeader += " | ";
    }

    truthTableHeader += "Output";
    cout << truthTableHeader << endl;

    // Calculate the number of rows for the truth table
    int rows = 1 << numberOfVar;

    // Initialize the truth table
    vector<vector<bool>> truthTable(rows, vector<bool>(numberOfVar, false));

    // Generate and print the truth table
    for (int i = 0; i < rows; ++i) {
        string current_exp = boolean_exp;

        // Populate the truth table and update the current expression
        for (int j = 0; j < numberOfVar; ++j) {
            bool value = (i >> j) & 1;
            char variable = *next(variableNames.begin(), j);
            assignValue(current_exp, variable, value);
            truthTable[i][j] = value;
        }

        // Evaluate the current expression and print the values in the row
        bool output = EvaluateExpression(current_exp);
        for (int j = 0; j < numberOfVar; ++j) {
            cout << truthTable[i][j] << " | ";
        }
        cout << output << endl;
    }

    // Implement the functions GenerateCanonicalSoP and GenerateCanonicalPoS to get canonical expressions
    string canonicalSoP = GenerateCanonicalSoP(truthTable, variableNames);
    string canonicalPoS = GenerateCanonicalPoS(truthTable, variableNames);

    cout << "Canonical SoP: " << canonicalSoP << endl;
    cout << "Canonical PoS: " << canonicalPoS << endl;
}


#endif /* functions_1_h */

#pragma clang diagnostic pop
