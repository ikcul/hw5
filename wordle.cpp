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
bool wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, int idxFloat, std::set<std::string>& answerBank, std::string& tempString);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> answerBank;
    std::string temp = in; 
    bool tempStr = wordleHelper(in, floating, dict, 0, 0, answerBank, temp);
    return answerBank;
    
}

// Define any helper functions here
bool wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int idxIn, int idxFloat, std::set<std::string>& answerBank, std::string& tempString){
    //base case
    if (idxIn >= in.size()){
        return true;
    }
    //iterate through all possible options
    if (in[idxIn] == '-'){
        if (idxFloat < floating.size()){
            tempString[idxIn] = floating[idxFloat];
            bool status = wordleHelper(in, floating, dict, idxIn++, idxFloat++, answerBank, tempString);
            if (status){
                if (dict.find(tempString) != dict.end()){
                    answerBank.insert(tempString);
                }
                return true;
            }
        }else{
            for (int i = 0; i < 26; i++){
                tempString[idxIn] = i + 'a';
                bool status = wordleHelper(in, floating, dict, idxIn++, idxFloat, answerBank, tempString);
                if (status){
                    //smth smth smth... tbd ig
                    if (dict.find(tempString) != dict.end()){
                        answerBank.insert(tempString);
                    }
                    return true;
                }
            }  
        }
    }else{
        //skips if there is a letter already inserted and green
        bool status = wordleHelper(in, floating, dict, idxIn++, idxFloat, answerBank, tempString);
        if (status){
            if (dict.find(tempString) != dict.end()){
                answerBank.insert(tempString);
            }
            return true;
        }
    }
    //if nothing works T_T hopefully never
    return false;
}
