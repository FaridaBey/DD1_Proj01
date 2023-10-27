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
#include <map>
#include <cmath>
using namespace std;

//---------------Helper functions for validation------------------
// checks if there is a bracket that doesnt have a sibling
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

// checks if the expression is in SOP form
bool isSOP(string &expression)
{
    for(int i=0; i<expression.length(); i++)
    {
        if(expression[i]==')'&&expression[i+1]=='(')
        {
            return false;
        }
        

    }
    //remove all brackets from expression
    expression.erase(remove(expression.begin(), expression.end(), '('), expression.end()); // Remove ( from the expression
    expression.erase(remove(expression.begin(), expression.end(), ')'), expression.end()); // Remove ) from the expression



    return true;
}



//--------------------------------Input Validation-------------------------------------------------

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
    
    //check if more than 10 variables in expression by making a set of variables and counting the size of the set
    set<char> variables;
    for (int i=0; i < boolean_exp.length(); i++) {
        if(isalpha(boolean_exp[i]))
        {
        boolean_exp[i] = tolower(boolean_exp[i]); // Convert all variables to lowercase
       
        if(variables.find(boolean_exp[i]) == variables.end()) //if not in set, add to set
        {
            variables.insert(boolean_exp[i]);
            var_count++;
        }
        }
    }

if(var_count > 10){
            cout << "too many variables\n"; // No more than 10 variables
            return false;
        }

    for (int i=0; i < boolean_exp.length(); i++) {
        if(boolean_exp[i]=='\''&&boolean_exp[i+1]=='\'')
        {
            boolean_exp.erase(i,2);
            i--;
        }
    }

    for (int i=0; i < boolean_exp.length(); i++) {   
        
        //Alphabet characters or valid operators check
        
        if (!(isalpha(boolean_exp[i]) || any_of(Val_operands.begin(), Val_operands.end(), [&boolean_exp, i](char v) {
            return v == boolean_exp[i];
        }))) {
            cout << "function invalid1" << endl; // Check if the character at index 'i' is an alphabetic character (letter) OR if it matches any character in the 'Val_operands' vector
            return false;
        }
        if(boolean_exp[i] == '+' && boolean_exp[i+1] == '+'){
            cout << "function invalid2.1" << endl; // Check if there are two '+' operators after each other
            return false;
        }
        else if(boolean_exp[i] == '+' && boolean_exp[i+1] == '\''){
            cout << "function invalid2.2" << endl; // Check if there is an apostraphe after a '+' operator
            return false;
        }
        else if((boolean_exp[i]=='('||boolean_exp[i]==')')&&boolean_exp[i+1]=='\'')
        {
            cout << "function invalid2.4" << endl; // Check if there is an apostraphe after a bracket
            return false;
        }
        else if(boolean_exp[i]=='('&&boolean_exp[i+1]=='+')
        {
            cout << "function invalid2.5" << endl; // Check if there is a '+' operator after a bracket
            return false;
        }
       
    }
    
    for(char oper : Val_operands){
        if((boolean_exp[0] == oper && boolean_exp[0] != '(' ) || ((boolean_exp[boolean_exp.length()-1] == oper && boolean_exp[boolean_exp.length()-1] != ')') && boolean_exp[boolean_exp.length()-1] != '\''))
        {
            cout << "function invalid4 \n"; // if expression starts with an operator other than '(' or ends with an operator other than ')' or ' it is invalid
            return false;
                
        }
        else if((boolean_exp[0] == '(' && boolean_exp[1] == oper) || (boolean_exp[boolean_exp.length()-1] == ')' && (boolean_exp[boolean_exp.length()-2] == oper && boolean_exp[boolean_exp.length()-2] != '\'')) || (boolean_exp[boolean_exp.length()-1] == '\'' && (boolean_exp[boolean_exp.length()-2] == oper && boolean_exp[boolean_exp.length()-2] != '\''))){
            cout << "function invalid5 \n"; // if expression starts with '(' or ends with [ ')' or '] and the second term is an operator it is invalid or second to last term is operator other than ' it is invalid
            return false;
        }
    }
    
    if (!balancedParentheses(boolean_exp)){
        cout<<"function invalid6\n";
        return false;
    }
    

    if (!isSOP(boolean_exp)){
        //check valid POS structure with + in between terms in their brackets
       for(int i=0; i<boolean_exp.length()-1; i++)
       {
            if(isalpha(boolean_exp[i]) && isalpha(boolean_exp[i+1]))
            {
                cout<<"function invalid7\n";
                return false;
                
            }
            
       }
      
    }

    cout<<"Valid Function: " << boolean_exp <<"\n";
    return true;
};
//--------------- Helper functions for Print ------------------

// Function to transform the expression to the standered or, and, not
string transform(string exp) // needs more check for bugs !!!!
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

// funtcion to print the truth table and canonical PoS/SoP
void printTruthTable(const string &expression) {
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

    
// Extract minterms and binary representations
    /*
     ...
     */
}

//----------------------------------------------------------------------------------------------------



//---------------To be used for QM------------------
bool compareByOnes(int &a, int &b)
{
    int aOnes = __builtin_popcount(a);
    int bOnes = __builtin_popcount(b);
    return aOnes < bOnes;
};

void sortbyones(vector<int> &x)
{
    sort(x.begin(), x.end(), compareByOnes);

};
#endif /* functions_1_h */

#pragma clang diagnostic pop

