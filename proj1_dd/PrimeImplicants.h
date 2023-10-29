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
cout<< "\n\nMinterms in sorted binary form: \n";
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


// Function to combine two binary strings
string combineBinaryStrings(const string &a, const string &b) {
    string result = "";
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            result += a[i];
        } else {
            result += '-';
        }
    }
    return result;
}

// Function to list all the minterms ordered by the number of 1's
vector<string> listMintermsOrderedByOnes(const vector<string> &minterms) {
    vector<string> orderedMinterms = minterms;
    sortbyones(orderedMinterms);
    return orderedMinterms;
}

//// Function to generate prime implicants
//vector<string> generatePrimeImplicants(vector<string> &minterms) {
//    vector<string> primeImplicants;
//    vector<string> unusedMinterms = minterms;
//
//    while (!unusedMinterms.empty()) {
//        bool combined = false;
//        vector<string> newUnusedMinterms;
//
//        for (size_t i = 0; i < unusedMinterms.size(); i++) {
//            for (size_t j = i + 1; j < unusedMinterms.size(); j++) {
//                string combinedTerm = combineBinaryStrings(unusedMinterms[i], unusedMinterms[j]);
//                if (combinedTerm.find('-') != string::npos) {
//                    primeImplicants.push_back(combinedTerm);
//                    combined = true;
//                } else {
//                    newUnusedMinterms.push_back(unusedMinterms[i]);
//                }
//            }
//        }
//
//        if (!combined) {
//            primeImplicants.insert(primeImplicants.end(), unusedMinterms.begin(), unusedMinterms.end());
//        }
//
//        unusedMinterms = newUnusedMinterms;
//    }
//
//    return primeImplicants;
//}
// Function to generate prime implicants
vector<string> generatePrimeImplicants(vector<string> &minterms) {
    vector<string> primeImplicants;
    vector<string> unusedMinterms = minterms;

    while (!unusedMinterms.empty()) {
        bool combined = false;
        vector<string> newUnusedMinterms;

        for (size_t i = 0; i < unusedMinterms.size(); i++) {
            for (size_t j = i + 1; j < unusedMinterms.size(); j++) {
                string combinedTerm = combineBinaryStrings(unusedMinterms[i], unusedMinterms[j]);
                if (combinedTerm.find('-') != string::npos) {
                    primeImplicants.push_back(combinedTerm);
                    combined = true;
                } else {
                    newUnusedMinterms.push_back(unusedMinterms[i]);
                }
            }
        }

        if (!combined) {
            primeImplicants.insert(primeImplicants.end(), unusedMinterms.begin(), unusedMinterms.end());
        }

        unusedMinterms = newUnusedMinterms;
    }

    return primeImplicants;
}





#endif /* PrimeImplicants_h */
#pragma clang diagnostic pop

