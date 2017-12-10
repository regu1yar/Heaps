//
// Created by Роман Климовицкий on 05.12.2017.
//

#include "BinTree.h"

BinTree::BinTree(int key) : key(key), degree(0), child(nullptr), sibling(nullptr), previousSibling(nullptr) { }

BinTree::BinTree(const BinTree& bTree) : key(bTree.key), degree(bTree.degree), child(bTree.child),
                                         sibling(bTree.sibling), previousSibling(bTree.previousSibling) { }

BinTree& BinTree::operator=(const BinTree &bTree) {
    if(this == &bTree) {
        return *this;
    }
    key = bTree.key;
    degree = bTree.degree;
    child = bTree.child;
    sibling = bTree.sibling;
    previousSibling = bTree.previousSibling;
    return *this;
}

void BinTree::meld(BinTree &bTree) {
    if(key > bTree.key) {
        std::swap(key, bTree.key);
    }
    child->previousSibling = &bTree;
    bTree.sibling = child;
    child = &bTree;
    ++degree;
}

void BinTree::print() const {
    std::cout << key << ' ';
    if(sibling != nullptr) {
        sibling->print();
    }
    if(child != nullptr) {
        child->print();
    }
}

BinTree::~BinTree() {
    if(child != nullptr) {
        delete child;
    }
    if(sibling != nullptr) {
        delete sibling;
    }
}