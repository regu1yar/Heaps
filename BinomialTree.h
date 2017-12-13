//
// Created by Роман Климовицкий on 05.12.2017.
//

#ifndef IHEAP_BINOMIALTREE_H
#define IHEAP_BINOMIALTREE_H

#include <vector>
#include <iostream>

class BinomialTree {
public:
    int key;
    std::vector<BinomialTree> childs;

    explicit BinomialTree(int key);
    BinomialTree(const BinomialTree& bTree);
    BinomialTree& operator=(const BinomialTree& bTree);
    bool operator<(const BinomialTree& b) const;
    static BinomialTree& meld(BinomialTree& bTree1, BinomialTree& bTree2);
    void print() const;
};


#endif //IHEAP_BINOMIALTREE_H
