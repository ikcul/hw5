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
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, size_t idxIn, std::map<char, int>& floatingUsage, std::set<std::string>& answerBank, std::string& tempString, int floatingRemaining, int blanks);

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
    int blanks = 0;
    for (char c : in){
        if (c == '-'){
            blanks++;
        }
    }

    wordleHelper(in, floating, dict, 0, floatingUsage, answerBank, temp, floating.size(), blanks);
    return answerBank;
    
}

// Define any helper functions here
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, size_t idxIn, std::map<char, int>& floatingUsage, std::set<std::string>& answerBank, std::string& tempString, int floatingRemaining, int blanks){
    //prune before even doing anything
    if (floatingRemaining > blanks){
        return;
    }
    //base case
    if (idxIn >= in.size()){
        //checks if it is a valid word
        if (dict.find(tempString) != dict.end()){
            answerBank.insert(tempString);
        }
        return;
    }
    //iterate through all possible options
    if (in[idxIn] == '-'){
        std::set<char> usedChars;
        //loops through all possibilites i think i need to edit this loop in particular
        for (auto it = floatingUsage.begin(); it != floatingUsage.end(); ++it){
            char c = it->first;
            if (floatingUsage[c] > 0){
                usedChars.insert(c);
                tempString[idxIn] = c;
                floatingUsage[c]--;
                wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString, floatingRemaining - 1, blanks - 1);
                tempString[idxIn] = '-';
                floatingUsage[c]++;
            }
        }
        //uses the set to see if its not in the set and then continues the branch
        if(floatingRemaining <= blanks - 1){
            for (int i = 0; i < 26; i++){
                //checks to see if the char was not used yet
                if (usedChars.count(i + 'a') == 0){
                    tempString[idxIn] = i + 'a';
                    wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString, floatingRemaining, blanks - 1);
                    tempString[idxIn] = '-';
                }
            }
        }
    }else{
        //skips if there is a letter already inserted and green
        wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString, floatingRemaining, blanks);
    }
    //if nothing works T_T hopefully never
    return;
}
