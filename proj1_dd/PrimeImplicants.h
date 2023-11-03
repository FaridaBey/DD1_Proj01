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
#include <sstream>

using namespace std;

//----------------------Prime Implicant extraction and utilities----------------------

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
    return binary;
};
//------------------------------------------Prime Implicants------------------------------------------

//----------------------------Part 3--------------------------------------
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

vector<int> PrintDecimalMinterms( vector<string> Minterms)
{
    vector<int> decimalMinterms;
    for (int i = 0; i < Minterms.size(); i++) {
        decimalMinterms.push_back(stoi(Minterms[i], nullptr, 2));
    }
    return decimalMinterms;
}
void printMintermsCoveredByPrimeImplicant(const map<string, string>& mintermsCoveredByPrimeImplicant) {
    int i=1;
            for (const auto &pair : mintermsCoveredByPrimeImplicant)
            {
                cout << "Prime Implicant [" << i <<"] : "<< pair.first << " , Minterms Covered: " << pair.second << endl;
                i++;
            }
}

//----------------------------Part 4--------------------------------------
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
//----------------------------Part 5--------------------------------------
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
//----------------------------Part 6--------------------------------------
//helpers

vector<string> splitMinterms(const string& minterms) {
    vector<string> result;
    istringstream iss(minterms);
    string minterm;
    while (getline(iss, minterm, ',')) {
        result.push_back(minterm);
    }
    return result;
}

int countCoveredMinterms(const vector<string>& coveredMinterms, const vector<string>& mintermsNotCovered) {
    int count = 0;
    for (const string& minterm : mintermsNotCovered) {
        if (find(coveredMinterms.begin(), coveredMinterms.end(), minterm) != coveredMinterms.end()) {
            count++;
        }
    }
    return count;
}

void removeCoveredMinterms(vector<string> coveredMinterms, vector<string> mintermsNotCovered) {
    vector<string> newMintermsNotCovered;
    for (const string& minterm : mintermsNotCovered) {
        if (find(coveredMinterms.begin(), coveredMinterms.end(), minterm) == coveredMinterms.end()) {
            newMintermsNotCovered.push_back(minterm);
        }
    }
    mintermsNotCovered = newMintermsNotCovered; // Update the mintermsNotCovered vector
}
//end helpers

// Function to Get Minimized Boolean exp (binary)
string generateMinimizedExpression(const vector<string>& essentialPrimeImplicants, const vector<string>& mintermsNotCovered, map<string, string>& primeImplicants) {
    string minimizedExpression = "";

    // Copy essential prime implicants to the result
    vector<string> selectedPrimeImplicants = essentialPrimeImplicants;

    vector<string> remainingMinterms = mintermsNotCovered;

    // Continue selecting prime implicants until all minterms are covered
    while (!remainingMinterms.empty()) {
        string bestCandidate;  // The prime implicant that covers the most remaining non-covered minterms
        int maxCovered = 0;  // The number of remaining non-covered minterms covered by the best candidate

        for (const auto& pi : primeImplicants) {
            if (find(selectedPrimeImplicants.begin(), selectedPrimeImplicants.end(), pi.first) == selectedPrimeImplicants.end()) {
                vector<string> coveredMinterms = splitMinterms(pi.second);

                // Count how many of the remaining minterms are covered by this candidate
                int coveredCount = countCoveredMinterms(coveredMinterms, remainingMinterms);

                if (coveredCount > maxCovered) {
                    maxCovered = coveredCount;
                    bestCandidate = pi.first;
                }
            }
        }

        if (!bestCandidate.empty()) {
            selectedPrimeImplicants.push_back(bestCandidate);

            // Remove the minterms covered by the selected prime implicant from the remaining minterms
            vector<string> coveredMinterms = splitMinterms(primeImplicants[bestCandidate]);
            removeCoveredMinterms(coveredMinterms, remainingMinterms);
        } else {
            break;  // No more prime implicants can cover additional minterms
        }
    }

    // Construct the minimized expression using the selected prime implicants
    for (const string& pi : selectedPrimeImplicants) {
        minimizedExpression += (minimizedExpression.empty() ? "" : " + ") + pi;
    }

    return minimizedExpression;
}
string final_answer(string boolexp, const vector<char>& variables) {
    string finalexp;
    size_t varIndex = 0;

    for (size_t i = 0; i < boolexp.length(); i++) {
        if (boolexp[i] == '1') {
            finalexp += variables[varIndex];
            varIndex++;
        } else if (boolexp[i] == '0') {
            finalexp += variables[varIndex];
            finalexp += "'";
            varIndex++;
        } else if (boolexp[i] == '-') {
            varIndex++;
        } else if (boolexp[i] == '+') {
            finalexp += " + ";
            varIndex = 0; // Reset the variable index to the beginning
        }

    }
    if(finalexp == "")
    {
        finalexp = "1";
    }
    return finalexp;
}
//-------------FOR K-MAP COVERS-------------
vector<string> get_mints(const map<string, string>& mintermsCoveredByPrimeImplicant){
    vector<string> allmints;
    for (const auto &pair : mintermsCoveredByPrimeImplicant)
    {
        allmints.push_back(pair.second);
    }
    return allmints;
}
int countpi(const map<string, string>& mintermsCoveredByPrimeImplicant){
    int count = 0;
    for (const auto &pair : mintermsCoveredByPrimeImplicant)
    {
        count++;
    }
    return count;
}
vector<int> convertStringVectorToInt(const vector<string>& stringVector) {
    vector<int> intVector;
    
    for (const string& str : stringVector) {
  
            int intValue = stoi(str);
            intVector.push_back(intValue);
    }

    return intVector;
}

#endif /* PrimeImplicants_h */
#pragma clang diagnostic pop

