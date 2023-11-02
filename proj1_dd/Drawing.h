#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#ifndef Drawing_h
#define Drawing_h

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

// Function to parse the SOP expression and extract the products into a vector of strings
vector<string> parseMinExp(string minexp)
{
    vector<string> products;
    string temp;
    if(minexp == "")
    {
        return products;
    }
    for (int i = 0; i < minexp.length(); i++)
    {
        if (minexp[i] == '+')
        {
            products.push_back(temp);
            temp = "";
        }
        else
        {
            temp += minexp[i];
        }
    }
    products.push_back(temp);
    return products;
}


// Function to convert terms to WaveDrom JSON
string termsToWaveDromJSON(vector<string> terms)
{
    string wavedromJSON;

    if(terms.size() == 0){
        wavedromJSON = R"({ "assign":[ ["out", "1")";
        
    }
    //if one product, and the terms
    else if(terms.size()==1)
    {
        if(terms[0].size()==1)
        {
            wavedromJSON = R"({ "assign":[ ["out", ")";
            wavedromJSON += terms[0][0];
            wavedromJSON += R"(")";
        }
        else{
        wavedromJSON = R"({ "assign":[ ["out", ["&", )";
        for(int i = 0; i < terms[0].length(); i++)
        {
            if(terms[0][i] == '\'')
            {
                wavedromJSON += R"(["~", ")";
                wavedromJSON += terms[0][i-1];
                wavedromJSON += R"("],)";
            }
            else if(i == terms[0].length() - 1 || terms[0][i+1] != '\'')
            {
                wavedromJSON += R"(")";
                wavedromJSON += terms[0][i];
                wavedromJSON += R"(")";
                if(i != terms[0].length()-1)
                {
                    wavedromJSON += ", ";
                }
            }
        }
        }
    }
    else{
    wavedromJSON = R"({ "assign":[ ["out", ["|", )";
    for(int i = 0; i < terms.size(); i++)
    {
        // Check if the term is a single variable
        if (terms[i].length() == 1 || (terms[i].length() == 2 && terms[i][1] == '\''))
        {
            if(terms[i].length() == 2 && terms[i][1] == '\'') {
                wavedromJSON += R"(["~", ")";
                wavedromJSON += terms[i][0];
                wavedromJSON += R"("])";
            } else {
                wavedromJSON += R"(")";
                wavedromJSON += terms[i][0];
                wavedromJSON += R"(")";
            }
        }
        else
        {
            wavedromJSON += R"(["&", )";
            for(int j = 0; j < terms[i].length(); j++)
            {
                if(terms[i][j] == '\'')
                {
                    wavedromJSON += R"(["~", ")";
                    wavedromJSON += terms[i][j-1];
                    wavedromJSON += R"("],)";
                }
                else if(j == terms[i].length() - 1 || terms[i][j+1] != '\'')
                {
                    wavedromJSON += R"(")";
                    wavedromJSON += terms[i][j];
                    wavedromJSON += R"(")";
                    if(j != terms[i].length()-1)
                    {
                        wavedromJSON += ", ";
                    }
                }
            }
            wavedromJSON += "]";
        }

        if(i != terms.size()-1)
        {
            wavedromJSON += ", ";
        }
    }
    }

    // Close the JSON structure
    if(terms.size() == 1 && terms[0].size() == 1 || terms.size() == 0)
    {
        wavedromJSON += R"(]]})";
    }
    else{
    wavedromJSON += R"(]]]})";
    }
    
    return wavedromJSON;
}

void printDrawing(string minexp)
{
    vector<string> products = parseMinExp(minexp);
    string wavedromJSON = termsToWaveDromJSON(products);
    
    string scripts = R"s(<script
 src="https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/skins/default.js" type="text/javascript"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/wavedrom.min.js" type="text/javascript"></script><script src="https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/skins/default.js" type="text/javascript"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/wavedrom.min.js" type="text/javascript"></script>

<body onload="WaveDrom.ProcessAll()">
<script type="WaveDrom">
)s" + wavedromJSON + R"s(

</script>
)s";



    string htmlContent = "<html>" + scripts + "</body></html>";
    string htmlFilePath = "output.html";

    // Write the HTML content to a file
    ofstream htmlFile(htmlFilePath);
    htmlFile << htmlContent;
    htmlFile.close();

    // Open the HTML file in the default web browser
    string command = "open " + htmlFilePath; // Use "start" on Windows, "xdg-open" on Linux
    system(command.c_str());
}

#endif /* Drawing_h */

#pragma clang diagnostic pop
