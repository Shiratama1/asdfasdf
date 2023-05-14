#include "PrefixMatcher.h"
#include <string>
#include <vector>
using namespace std;

PrefixMatcher::PrefixMatcher() {
    root = new TrieNode();
}

void PrefixMatcher::insert(string address, int routerNumber) {
    TrieNode* CurrNode = root;
    for(int i=0;i<address.length();i++) {
        int index=address.at(i)-'0';
        if(!CurrNode->children[index]) {
            CurrNode->children[index] = new TrieNode();
        }
        CurrNode = CurrNode->children[index];
    }
    CurrNode->isEndOfWord=true;
    CurrNode->routeNum=routerNumber;
}

void PrefixMatcher::search(TrieNode* current, string partialNum, vector<int>& returnedAddress, vector<int>& routerCount) {
    if(current->isEndOfWord) {
        returnedAddress.push_back(current->routeNum);
        routerCount.push_back(count);
    }
    for(int i=0; i<2;i++) { 
        TrieNode* nextNode = current->children[i];
        if(nextNode) {
            count++;
            search(nextNode, partialNum+(char)(i+'0'), returnedAddress, routerCount);
            count--;
        }
    }
}

int PrefixMatcher::selectRouter(string address) {
    vector<int> routerNum;
    vector<int> routerCount;
    TrieNode* CurrNode=root;

    for(int i=0; i<address.length();i++) {
        int index=address.at(i)-'0';
        if(!CurrNode->children[index]) {
            break;
        }
        CurrNode = CurrNode->children[index];
    }

    search(CurrNode,address,routerNum,routerCount);

    if (routerCount.empty()) {
        return -1; // No matching router found.
    }

    int big=routerCount.at(0);
    int index=0;
    for(int i= 0;i<routerCount.size();i++) {
        if(big>routerCount.at(i)) {
            big=routerCount.at(i);
            index=i;
        }
    }
    return routerNum.at(index);
}
