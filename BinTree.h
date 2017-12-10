//
// Created by Роман Климовицкий on 05.12.2017.
//

#ifndef IHEAP_BINTREE_H
#define IHEAP_BINTREE_H

#include <vector>
#include <iostream>

class BinTree {
public:
    int key;
    int degree;
    BinTree* child;
    BinTree* sibling;
    BinTree* previousSibling;

    explicit BinTree(int key);
    BinTree(const BinTree& bTree);
    BinTree& operator=(const BinTree& bTree);
    void meld(BinTree& bTree);
    void print() const;
    ~BinTree();
};


#endif //IHEAP_BINTREE_H
