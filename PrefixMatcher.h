#ifndef PREFIXMATCHER_H
#define PREFIXMATCHER_H
#include <vector>
#include <string>

class PrefixMatcher {
    private:
        struct TrieNode{
            bool isEndOfWord;
            int routeNum;
            std::vector<TrieNode*> children;
            TrieNode() {
                for (int i = 0; i < 2; ++i) {
                    children.push_back(nullptr);
                }
            }

        };
        TrieNode* root;
    protected:
        int count=0;
    public:
        PrefixMatcher();
        int selectRouter(std::string networkAddress);  // return the router with the longest matching prefix
        void insert(std::string address, int routerNumber); // add a router address
        void search(TrieNode* current, std::string partialWord,std::vector<int>& routerNum,std::vector<int>& routerCount);
        void printAddresses(TrieNode* current);
};

#endif