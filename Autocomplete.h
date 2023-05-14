#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H
#include <vector>
#include <string>


class Autocomplete {
    private:
        struct TrieNode{
            bool isEndOfWord;
            std::vector<TrieNode*> children;
            TrieNode() {
                for (int i = 0; i < 26; ++i) {
                    children.push_back(nullptr);
                }
            }

        };
        TrieNode* root;
    public:
        Autocomplete();
        std::vector<std::string> getSuggestions(std::string partialWord);  // return the known words that start with partialWord
        void insert(std::string word); // add a word to the known words
        void search(TrieNode* current, std::string partialWord,std::vector<std::string>& returnedWords);
};

#endif