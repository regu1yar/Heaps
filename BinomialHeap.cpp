//
// Created by Роман Климовицкий on 07.12.2017.
//

#include "BinomialHeap.h"
#include <cassert>

BinomialHeap::BinomialHeap() { }

BinomialHeap::BinomialHeap(int key) {
    BinomialTree firstTree(key);
    trees.push_back(firstTree);
}

BinomialHeap::BinomialHeap(BinomialTree& tree) {
    trees.clear();
    trees.push_back(tree);
}

void BinomialHeap::insert(int key) {
    BinomialHeap heap(key);
    meld(heap);
}

int BinomialHeap::getMin() const {
    assert(!trees.empty());
    int min = trees.front().key;
    for(auto iter = trees.begin(); iter != trees.end(); ++iter) {
        if(min > iter->key) {
            min = iter->key;
        }
    }
    return min;
}

void BinomialHeap::extractMin() {
    assert(!trees.empty());
    auto iter = trees.begin();
    auto min = iter;
    while(iter != trees.end()) {
        if(min->key > iter->key) {
            min = iter;
        }
        ++iter;
    }
    BinomialHeap minChildsHeap;
    for(size_t i = 0; i < min->childs.size(); ++i) {
        minChildsHeap.trees.push_back(min->childs[i]);
    }
    trees.erase(min);
    meld(minChildsHeap);
}

void BinomialHeap::meld(IHeap& heap) {
    BinomialHeap& binHeap = dynamic_cast<BinomialHeap&>(heap);
    if(this == &binHeap || binHeap.empty()) {
        return;
    }
    if(empty()) {
        trees = binHeap.trees;
        return;
    }
    trees.merge(binHeap.trees);
    auto curr = trees.end();
    --curr;
    auto prev = curr--;
    while(prev != trees.begin()) {
        while(prev != trees.end() && curr->childs.size() == prev->childs.size()) {
            *curr = BinomialTree::meld(*curr, *prev);
            trees.erase(prev);
            prev = std::next(curr);
        }
        prev = curr--;
    }
}

void BinomialHeap::clear() { trees.clear(); }

void BinomialHeap::print() const {
    for(auto iter = trees.begin(); iter != trees.end(); ++iter) {
        std::cout << "TREE ";
        iter->print();
    }
    std::cout << std::endl;
}

bool BinomialHeap::empty() const { return trees.empty(); }

BinomialHeap::~BinomialHeap() { }