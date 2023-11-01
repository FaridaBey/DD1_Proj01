#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#ifndef PrimeImplicants_h
#define PrimeImplicants_h
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

//----------------------Prime Implicant extraction and utilities----------------------
    
struct combination
{
    string combinedMinterm;
    bool isCombined;
    vector<string> coveredMins;

    combination(string combinedMinterm, bool isCombined, vector<string> coveredMins)
    {
        this->combinedMinterm = combinedMinterm;
        this->isCombined = isCombined;
        this->coveredMins = coveredMins;
    }
};

//---------------To be used for QM------------------
int countOnes(const string &binaryString) {
    return count(binaryString.begin(), binaryString.end(), '1');
}

bool compareByOnes(const string & a, const string & b)
{
    return countOnes(a) < countOnes(b);
};

void sortbyones(vector<string> &x)
{
    sort(x.begin(), x.end(), compareByOnes);

};

vector<string> PrintBinaryMinterms(vector<string> minterms)
{
    //---------------------------------------Print Minterms in Binary form----------------------------------

sortbyones(minterms);
vector<string> binary;
string temp = "";
//binary representation
for (int i = 0; i < minterms.size(); i++) {
   
    for (int j = 0; j < minterms[i].length(); j++) {
        if (isalpha(minterms[i][j])&& minterms[i][j+1]=='\'')
        {
            temp += '0';
            j++;
        }
            
        else if (isalpha(minterms[i][j]))
            temp += '1';
    }
          
    binary.push_back(temp);
    temp = "";
    
}
//for (int j = 0; j < binary.size(); j++) {
//        cout << binary[j]<<endl;
//    }
//
//    cout<<"\n";

    return binary;
};

// Function to convert a minterm (e.g., "a'b'c") to its binary representation (e.g., "010")
string convertToBinary(const string& minterm) {
    string binaryMinterm;
    for (char c : minterm) {
        if (c == '0' || c == '1') {
            binaryMinterm += c;
        } 
         else {
            // Handle variables (e.g., a, b, c)
            // You need to map your variables to positions in the binary representation
            // For example, if a, b, c correspond to 0, 1, 2, you can use:
            // binaryMinterm += to_string(variableToPosition(c));
        }
    }
    return binaryMinterm;
}
//------------------------------------------Prime Implicants------------------------------------------
/*
 For each PI show the minterms it covers as well as its
 binary representation.
 */
void printPrimeImplicants(const vector<string>& primeImplicants, const map<string, vector<string>>& mintermsCoveredByPrimeImplicant) {
    for (const auto& implicant : primeImplicants) {
        cout << "Prime Implicant: " << implicant << " covers Minterms: ";
        for (const string& minterm : mintermsCoveredByPrimeImplicant.at(implicant)) {
            cout << minterm << " ";
        }
//        cout << " Binary Representation: " << implicant << endl;
    }
}
vector<string> generatePrimeImplicants(const vector<string>& minterms) {
    // Sort minterms ordered by the number of 1's in ascending order using your custom sorting function
    vector<string> sortedMinterms = minterms;
    sortbyones(sortedMinterms);

    vector<string> primeImplicants;
    vector<bool> marked(sortedMinterms.size(), false);
    // Create a map to store the minterms covered by each prime implicant
    map<string, vector<string>> mintermsCoveredByPrimeImplicant;

    while (true) {
        vector<string> nextColumn;

        for (size_t i = 0; i < sortedMinterms.size(); ++i) {
            for (size_t j = i + 1; j < sortedMinterms.size(); ++j) {
                const string& term1 = sortedMinterms[i];
                const string& term2 = sortedMinterms[j];
                int differingBitCount = 0;
                string combinedTerm = "";

                for (size_t k = 0; k < term1.size(); ++k) {
                    if (term1[k] != term2[k]) {
                        differingBitCount++;
                        combinedTerm += '-';
                    } else {
                        combinedTerm += term1[k];
                    }
                }

                // Check if the terms can be combined (only one differing bit)
                if (differingBitCount == 1) {
                    nextColumn.push_back(combinedTerm);
                    marked[i] = marked[j] = true; // Mark as combined
                }
            }
        }

        // Mark and save uncombined terms as prime implicants
        for (size_t i = 0; i < sortedMinterms.size(); ++i) {
            if (!marked[i]) {
                primeImplicants.push_back(sortedMinterms[i]);
                // Store the minterms covered by this prime implicant
                for (size_t k = 0; k < minterms.size(); ++k) {
                    if (sortedMinterms[i] == minterms[k]) {
                        mintermsCoveredByPrimeImplicant[sortedMinterms[i]].push_back(minterms[k]);
                    }
                }
            }
        }

        // If no more combinations are possible, exit the loop
        if (nextColumn.empty()) {
            break;
        }

        sortedMinterms = nextColumn; // Move to the next column
        marked.assign(sortedMinterms.size(), false); // Reset the marked array
    }
    // Sort primeImplicants by the number of ones (ascending order)
    sortbyones(primeImplicants);

    // Remove duplicates
    primeImplicants.erase(unique(primeImplicants.begin(), primeImplicants.end()), primeImplicants.end());

    return primeImplicants;
}
// Function to print a prime implicant along with the minterms it covers*(NOT CORRECT)*
void printPrimeImplicant_1(const vector<string>& primeImplicant, const vector<string>& minterms) {
    cout << "Prime Implicant: " ;
    for (const string& pi : primeImplicant) {
        cout << pi << " \n";
    }
    cout << endl;
    cout << "Covered Minterms: ";
    for (const string& minterm : minterms) {
        cout << minterm << " ";
    }
    cout << endl;
}

vector<int> PrintDecimalMinterms( vector<string> Minterms)
{
    vector<int> decimalMinterms;
    for (int i = 0; i < Minterms.size(); i++) {
        decimalMinterms.push_back(stoi(Minterms[i], nullptr, 2));
    }
    //print minterms
 for (int i = 0; i < decimalMinterms.size(); i++) {
        cout <<decimalMinterms[i] << " \n ";
    }
    return decimalMinterms;
}

#endif /* PrimeImplicants_h */
#pragma clang diagnostic pop

