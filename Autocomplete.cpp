#include "Autocomplete.h"

using namespace std;

Autocomplete::Autocomplete(){
    root=new TrieNode();
}

void Autocomplete::insert(string word){
    TrieNode* CurrNode=root;
    for(int i=0;i<word.length();i++){
        int index=word.at(i)-'a';
        if(!CurrNode->children[index]){
            CurrNode->children[index]=new TrieNode();
            CurrNode->children[index]->isEndOfWord=false;
        }
        CurrNode=CurrNode->children[index];
    }
    CurrNode->isEndOfWord = true;
}

void Autocomplete::search(TrieNode* current, string partialWord, vector<string>& returnedWords){
    if(current->isEndOfWord){ //base case;
       returnedWords.push_back(partialWord); //if reaches the end means that partialWord is a word
    }
    for(int i=0;i<26;i++){ //goes through all possible alphabet
        TrieNode* nextNode=current->children[i];
        if(nextNode){ //if found go through search again for the next alphabet
            search(nextNode,partialWord+(char)('a'+i), returnedWords);
        }
    }
}

vector<string> Autocomplete::getSuggestions(string partialWord){
    vector<string> returnedWords;
    TrieNode* CurrNode=root;
    TrieNode* nextNode;
    if(CurrNode==nullptr){
        return returnedWords;
    }

    for(int i=0;i<partialWord.length();i++){
        int index=partialWord.at(i)-'a';
        if(!CurrNode->children[index]){
            return returnedWords;
        }
        CurrNode=CurrNode->children[index];
    }//This will go up to partialWord in the Trie
    search(CurrNode,partialWord,returnedWords);
    return (returnedWords);
}
