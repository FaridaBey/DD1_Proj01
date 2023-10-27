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
    
// Extract minterms and binary representations
    /*
     ...
     */

//--------------------------------------------------------------------------------------



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
#endif /* PrimeImplicants_h */

#pragma clang diagnostic pop

