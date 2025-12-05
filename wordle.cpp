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
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, std::map<char, int>& floatingUsage, std::set<std::string>& answerBank, std::string& tempString, std::set<char>& usedChars);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> answerBank;
    std::string temp = in;
    std::set<char> usedChars;
    std::map<char, int> floatingUsage;
    for (char c : floating){
        floatingUsage[c]++;
    }

    wordleHelper(in, floating, dict, 0, floatingUsage, answerBank, temp, usedChars);
    return answerBank;
    
}

// Define any helper functions here
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, std::map<char, int>& floatingUsage, std::set<std::string>& answerBank, std::string& tempString, std::set<char>& usedChars){
    //prune before even doing anything
    int floatingCount = 0;
    int posLeft = in.size() - idxIn;
    for (auto it = floatingUsage.begin(); it != floatingUsage.end(); ++it){
        if (it->second != 0){
            floatingCount+= it->second;
        }
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
        //loops through all possibilites i think i need to edit this loop in particular
        for (auto it = floatingUsage.begin(); it != floatingUsage.end(); ++it){
            char c = it->first;
            if (floatingUsage[c] > 0){
                usedChars.insert(c);
                tempString[idxIn] = c;
                floatingUsage[c]--;
                wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString, usedChars);
                tempString[idxIn] = '-';
                floatingUsage[c]++;
            }
        }
        for (int i = 0; i < 26; i++){
            if (usedChars.count(i + 'a') == 0){
                tempString[idxIn] = i + 'a';
                wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString, usedChars);
                tempString[idxIn] = in[idxIn];
            }
        }
    }else{
        //skips if there is a letter already inserted and green
        wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString, usedChars);
    }
    //if nothing works T_T hopefully never
    return;
}
