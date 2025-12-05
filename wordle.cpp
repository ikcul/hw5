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
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, std::map<char, int> floatingUsage, std::set<std::string>& answerBank, std::string& tempString);

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
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, std::map<char, int> floatingUsage, std::set<std::string>& answerBank, std::string& tempString){
    //base case
    if (idxIn >= in.size() && dict.find(tempString) != dict.end()){
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
        return;
    }
    //iterate through all possible options
    if (in[idxIn] == '-'){
        for (int i = 0; i < 26; i++){
            tempString[idxIn] = i + 'a';
            bool used = false;
            if (floatingUsage.count(i+'a') && floatingUsage[i + 'a'] > 0){
                floatingUsage[i + 'a']--;
                used = true;
            }
            wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString);
            tempString[idxIn] = in[idxIn];
            if (used){
                floatingUsage[i + 'a']++;
            }
        }
    }else{
        //skips if there is a letter already inserted and green
        wordleHelper(in, floating, dict, idxIn + 1, floatingUsage, answerBank, tempString);
    }
    //if nothing works T_T hopefully never
    return;
}
