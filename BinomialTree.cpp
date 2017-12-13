//
// Created by Роман Климовицкий on 05.12.2017.
//

#include "BinomialTree.h"

BinomialTree::BinomialTree(int key) : key(key) { }

BinomialTree::BinomialTree(const BinomialTree& bTree) : key(bTree.key), childs(bTree.childs) { }

BinomialTree& BinomialTree::operator=(const BinomialTree &bTree) {
    if(this == &bTree) {
        return *this;
    }
    key = bTree.key;
    childs = bTree.childs;
    return *this;
}

bool BinomialTree::operator<(const BinomialTree &b2) const {
    return childs.size() < b2.childs.size();
}

BinomialTree& BinomialTree::meld(BinomialTree &bTree1, BinomialTree &bTree2) {
    if(&bTree1 == &bTree2) {
        return bTree1;
    }
    if(bTree1.key > bTree2.key) {
        bTree2.childs.push_back(bTree1);
        return bTree2;
    } else {
        bTree1.childs.push_back(bTree2);
        return bTree1;
    }
}

void BinomialTree::print() const {
    std::cout << key << ' ';
    for(size_t i = 0; i < childs.size(); ++i) {
        childs[i].print();
    }
}