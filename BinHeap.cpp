//
// Created by Роман Климовицкий on 07.12.2017.
//

#include "BinHeap.h"

void BinHeap::addTree(BinTree *bTree) {

}

BinHeap::BinHeap() : firstTree(nullptr) {}

BinHeap::BinHeap(int key) { firstTree = new BinTree(key); }

BinHeap::BinHeap(BinTree *tree) : firstTree(tree) { }

void BinHeap::insert(int key) {
    BinHeap* heap = new BinHeap(key);
    meld(*heap);
}

int BinHeap::getMin() const {
    BinTree* minTree = firstTree;
    int min = minTree->key;
    while(minTree != nullptr) {
        if(min > minTree->key) {
            min = minTree->key;
        }
        minTree = minTree->sibling;
    }
    return min;
}

void BinHeap::extractMin() {
    BinTree* minTree = firstTree;
    BinTree* previous = nullptr;
    int min = getMin();
    while(minTree->key != min) {
        previous = minTree;
        minTree = minTree->sibling;
    }
    if(previous != nullptr) {
        previous->sibling = minTree->sibling;
        minTree->sibling->previousSibling = previous;
    } else {
        firstTree = minTree->sibling;
        minTree->sibling->previousSibling = nullptr;
    }
    BinHeap* newHeap = new BinHeap(minTree->child);
    meld(*newHeap);
    minTree->child = nullptr;
    minTree->sibling = nullptr;
    delete minTree;
}

void BinHeap::meld(IHeap& heap) {
    if(this == &heap) {
        return;
    }
    BinHeap& newHeap = dynamic_cast<BinHeap&>(heap);
    if(newHeap.empty()) {
        return;
    }
    if(empty()) {
        firstTree = newHeap.firstTree;
        return;
    }
    BinTree* tree1 = firstTree;
    BinTree* tree2 = newHeap.firstTree;
    BinTree* tree;
    while(tree1 != nullptr && tree2 != nullptr) {
        if(tree1->degree > tree2->degree) {
            tree1->previousSibling = tree2->previousSibling;
            
        }
    }
}

void BinHeap::clear() { trees.clear(); }

void BinHeap::print() const {
    for(auto i = trees.begin(); i != trees.end(); ++i) {
        i->print();
    }
    std::cout << std::endl;
}

bool BinHeap::empty() const { return firstTree == nullptr; }