#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#ifndef PrimeImplicants_h
#define PrimeImplicants_h
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <stack>
#include <set>
#include <map>
#include <cmath>
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

void PrintBinaryMinterms(vector<string> minterms)
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
for (int j = 0; j < binary.size(); j++) {
        cout << binary[j]<<endl;
    }

    cout<<"\n";

    
};




#endif /* PrimeImplicants_h */
#pragma clang diagnostic pop

