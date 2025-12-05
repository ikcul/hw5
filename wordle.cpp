#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, std::map<char, int>& floatingUsage, std::set<std::string>& answerBank, std::string& tempString);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> answerBank;
    std::string temp = in;
    std::map<char, int> floatingUsage;
    for (char c : floating){
        floatingUsage[c]++;
    }

    wordleHelper(in, floating, dict, 0, floatingUsage, answerBank, temp);
    return answerBank;
    
}

// Define any helper functions here
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, std::map<char, int>& floatingUsage, std::set<std::string>& answerBank, std::string& tempString){
    //prune before even doing anything
    int floatingCount = 0;
    int posLeft = in.size() - idxIn;
    for (auto it = floatingUsage.begin(); it != floatingUsage.end(); ++it){
        floatingCount+= it->second;
    }if (floatingCount > posLeft){
        return;
    }
    //base case
    if (idxIn >= in.size()){
        //checks if it is a valid word
        if (dict.find(tempString) != dict.end()){
            bool used = true;
            for (auto it = floatingUsage.begin(); it != floatingUsage.end(); ++it){
                if (it->second != 0){
                    used = false;
                    break;
                }
            }
            if (used){
                answerBank.insert(tempString);
            }
        }
        return;
    }
    //iterate through all possible options
    if (in[idxIn] == '-'){
        for (int i = 0; i < 26; i++){
            char c = i + 'a';
            tempString[idxIn] = c;
            if (floatingUsage.count(c) && floatingUsage[c] > 0){
                floatingUsage[c]--;
                wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString);
                floatingUsage[c]++;
            }else{
                if (floatingCount <= posLeft - 1){
                    wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString);
                }
            }
        }
    }else{
        //skips if there is a letter already inserted and green
        wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString);
    }
    //if nothing works T_T hopefully never
    return;
}
