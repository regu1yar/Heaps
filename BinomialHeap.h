//
// Created by Роман Климовицкий on 07.12.2017.
//

#ifndef IHEAP_BINOMIALHEAP_H
#define IHEAP_BINOMIALHEAP_H


#include <list>
#include <cassert>
#include "IHeap.h"

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

class BinomialHeap : public IHeap {
private:
    std::list<BinomialTree> trees;

public:
    BinomialHeap();
    explicit BinomialHeap(int key);
    explicit BinomialHeap(BinomialTree& tree);
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
    virtual ~BinomialHeap();
};

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


#endif //IHEAP_BINOMIALHEAP_H
