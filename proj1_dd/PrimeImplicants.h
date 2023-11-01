#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#ifndef PrimeImplicants_h
#define PrimeImplicants_h
#include <iostream>
#include <vector>
#include <cctype>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

//----------------------Prime Implicant extraction and utilities----------------------
    
struct Implicants
{
    string combinedMinterm;
    bool isCombined;
    vector<int> coveredMins;
    
    Implicants(string combinedMinterm, bool isCombined, vector<int> coveredMins)
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

//vector<string> generatePrimeImplicants(const vector<string>& minterms) {
//    // Create a copy of the minterms to sort, so the original list remains unaltered
//    vector<string> sortedMinterms = minterms;
//    // Sort minterms ordered by the number of 1's in ascending order using a custom sorting function
//    sortbyones(sortedMinterms);
//
//    // Initialize containers for prime implicants and marked minterms
//    vector<string> primeImplicants;
//    vector<bool> marked(sortedMinterms.size(), false);
//    
//    // Create a map to store the minterms covered by each prime implicant
//    map<string, string> mintermsCoveredByPrimeImplicant;
//
//    bool column = true; // A flag to control the loop
//    while (column) {
//        vector<string> nextColumn; // Create the next column for combination
//        
//        // Loop through each pair of minterms in the current column
//        for (size_t i = 0; i < sortedMinterms.size(); ++i) {
//            for (size_t j = i + 1; j < sortedMinterms.size(); ++j) {
//                const string& term1 = sortedMinterms[i];
//                const string& term2 = sortedMinterms[j];
//                int differingBitCount = 0;
//                string combinedTerm = "";
//
//                // Compare the two terms and create a combined term with differing bits marked as '-'
//                for (size_t k = 0; k < term1.size(); ++k) {
//                    if (term1[k] != term2[k]) {
//                        differingBitCount++;
//                        combinedTerm += '-';
//                    } else {
//                        combinedTerm += term1[k];
//                    }
//                }
//
//                // Check if the terms can be combined (only one differing bit)
//                if (differingBitCount == 1) {
//                    nextColumn.push_back(combinedTerm); // Add the combined term to the next column
//                    marked[i] = marked[j] = true; // Mark the minterms as combined
//                }
//            }
//        }
//
//        // Mark and save uncombined terms as prime implicants
//        for (size_t i = 0; i < sortedMinterms.size(); ++i) {
//            if (!marked[i]) {
//                primeImplicants.push_back(sortedMinterms[i]); // Store the prime implicant
//                
//                    }
//        }
//
//        // If no more combinations are possible, exit the loop
//        if (nextColumn.empty()) {
//            column = false;
//        }
//
//        sortedMinterms = nextColumn; // Move to the next column
//        marked.assign(sortedMinterms.size(), false); // Reset the marked array for the next column
//    }
//
//    // Sort primeImplicants by the number of ones (ascending order)
//    sortbyones(primeImplicants);
//
//    // Remove duplicates from the list of prime implicants
//    primeImplicants.erase(unique(primeImplicants.begin(), primeImplicants.end()), primeImplicants.end());
//
//    return primeImplicants;
//}
int calculateDecimalValue(const string& binaryString) {
    int decimalValue = 0;
    int base = 1;

    for (int i = binaryString.size() - 1; i >= 0; --i) {
        if (binaryString[i] == '1') {
            decimalValue += base;
        }
        base *= 2;
    }

    return decimalValue;
}

map<string, string> generatePrimeImplicants(const vector<string>& minterms) {
    // Create a copy of the minterms to sort, so the original list remains unaltered
    vector<string> sortedMinterms = minterms;
    // Sort minterms ordered by the number of 1's in ascending order using a custom sorting function
    sortbyones(sortedMinterms);

    // Initialize containers for prime implicants and marked minterms
    vector<string> primeImplicants;
    vector<bool> marked(sortedMinterms.size(), false);

    // Create a map to store the minterms covered by each prime implicant
    map<string, string> mintermsCoveredByPrimeImplicant, finalPrimeImplicants;

    // Create a map to store the decimal representation of each minterm
    map<string, string> mintermToDecimal;

    // Calculate the decimal representation for each minterm
    for (const string& minterm : minterms) {
        string decimalValue = to_string(calculateDecimalValue(minterm));
        mintermToDecimal[minterm] = decimalValue;
    }

    bool column = true; // A flag to control the loop
    while (column) {
        vector<string> nextColumn; // Create the next column for combination

        // Loop through each pair of minterms in the current column
        for (size_t i = 0; i < sortedMinterms.size(); ++i) {
            for (size_t j = i + 1; j < sortedMinterms.size(); ++j) {
                const string& term1 = sortedMinterms[i];
                const string& term2 = sortedMinterms[j];
                int differingBitCount = 0;
                string combinedTerm = "";

                // Compare the two terms and create a combined term with differing bits marked as '-'
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
                    nextColumn.push_back(combinedTerm); // Add the combined term to the next column
                    marked[i] = marked[j] = true; // Mark the minterms as combined

                    // Get the decimal representations of both minterms
                    string decimalTerm1 = mintermToDecimal[term1];
                    string decimalTerm2 = mintermToDecimal[term2];

                    // Combine the decimal representations as comma-separated values
                    string combinedDecimal = decimalTerm1 + ", " + decimalTerm2;

                    // Store the combined implicant and its associated decimal values
                    mintermsCoveredByPrimeImplicant[combinedTerm] = combinedDecimal;
                    mintermToDecimal[combinedTerm] = combinedDecimal;
                }
            }
        }

        // Mark and save uncombined terms as prime implicants
        for (size_t i = 0; i < sortedMinterms.size(); ++i) {
            if (!marked[i]) {
                primeImplicants.push_back(sortedMinterms[i]); // Store the prime implicant
                // Store the minterms covered by this prime implicant
                mintermsCoveredByPrimeImplicant[sortedMinterms[i]] = (mintermToDecimal[sortedMinterms[i]]);
                finalPrimeImplicants[sortedMinterms[i]] = (mintermToDecimal[sortedMinterms[i]]);
                
            }
        }

        // If no more combinations are possible, exit the loop
        if (nextColumn.empty()) {
            column = false;
        }

        sortedMinterms = nextColumn; // Move to the next column
        marked.assign(sortedMinterms.size(), false); // Reset the marked array for the next column
    }

    // Sort primeImplicants by the number of ones (ascending order)
    sortbyones(primeImplicants);

    // Remove duplicates from the list of prime implicants
    primeImplicants.erase(unique(primeImplicants.begin(), primeImplicants.end()), primeImplicants.end());

    return finalPrimeImplicants;
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
//  for (int i = 0; i < decimalMinterms.size(); i++) {
//         cout <<decimalMinterms[i] << " \n ";
//     }
    return decimalMinterms;
}
void printMintermsCoveredByPrimeImplicant(const map<string, string>& mintermsCoveredByPrimeImplicant) {
    for (const auto& entry : mintermsCoveredByPrimeImplicant) {
        cout << "Implicant: " << entry.first << " Covers Minterms (Decimal): " << entry.second << endl;
    }
}


vector<string> generateEssentialPrimeImplicants(map<string, string> PI) {
    vector<string> EPI;
    map<string, int> mintermCount;

    // Count how many times each minterm is covered by prime implicants
    for (const auto& pair : PI) {
        string minterms = pair.second;
        string delimiter = ", ";
        size_t pos = 0;
        string token;
        while ((pos = minterms.find(delimiter)) != string::npos) {
            token = minterms.substr(0, pos);
            mintermCount[token]++;
            minterms.erase(0, pos + delimiter.length());
        }
        mintermCount[minterms]++;
    }

    // Check if a minterm is covered by only one prime implicant
    for (const auto& pair : PI) {
        string minterms = pair.second;
        string delimiter = ", ";
        size_t pos = 0;
        string token;
        while ((pos = minterms.find(delimiter)) != string::npos) {
            token = minterms.substr(0, pos);
            if (mintermCount[token] == 1) {
                EPI.push_back(pair.first);
                break;  // Once an essential prime implicant is found, move to the next prime implicant
            }
            minterms.erase(0, pos + delimiter.length());
        }
        if (mintermCount[minterms] == 1) {
            EPI.push_back(pair.first);
        }
    }

    // Remove duplicates
    sort(EPI.begin(), EPI.end());
    EPI.erase(unique(EPI.begin(), EPI.end()), EPI.end());

    return EPI;
}

vector<string> generateMintermsNOTCoveredByEPI(map<string, string> PI, const vector<int>& Minterms, vector<string> EPIs) {
    vector<int> EPIMinterms;
    vector<string> nonEPIMinterms;

    // Loop through the map and extract the minterms that are covered by the Essential Prime Implicants
    for(auto epi : EPIs)
    {
        string minterms = PI[epi];
        string delimiter = ", ";
        size_t pos = 0;
        string token;
        while ((pos = minterms.find(delimiter)) != string::npos) {
            token = minterms.substr(0, pos);
            EPIMinterms.push_back(stoi(token));
            minterms.erase(0, pos + delimiter.length());
        }
        EPIMinterms.push_back(stoi(minterms));
    }

    // Remove the minterms that are covered by the Essential Prime Implicants
    for (int i = 0; i < Minterms.size(); i++) {
        if (find(EPIMinterms.begin(), EPIMinterms.end(), Minterms[i]) == EPIMinterms.end()) {
            nonEPIMinterms.push_back(to_string(Minterms[i])); // Convert the minterm back to a string
        }
    }

    return nonEPIMinterms;
}


#endif /* PrimeImplicants_h */
#pragma clang diagnostic pop

