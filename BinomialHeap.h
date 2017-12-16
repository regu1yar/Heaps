//
// Created by Роман Климовицкий on 07.12.2017.
//

#ifndef IHEAP_BINOMIALHEAP_H
#define IHEAP_BINOMIALHEAP_H


#include <list>
#include <vector>
#include <cassert>
#include "IHeap.h"

class BinomialTree {
private:
    int key;
    std::vector<BinomialTree> children;

public:
    explicit BinomialTree(int key);
    BinomialTree(const BinomialTree& bTree);
    BinomialTree& operator=(const BinomialTree& bTree);
    bool operator<(const BinomialTree& b) const;
    void print() const;

    friend class BinomialHeap;
    friend BinomialTree& meldTrees(BinomialTree &bTree1, BinomialTree &bTree2);
};

BinomialTree::BinomialTree(int key) : key(key) { }

BinomialTree::BinomialTree(const BinomialTree& bTree) : key(bTree.key), children(bTree.children) { }

BinomialTree& BinomialTree::operator=(const BinomialTree &bTree) {
    if(this == &bTree) {
        return *this;
    }
    key = bTree.key;
    children = bTree.children;
    return *this;
}

bool BinomialTree::operator<(const BinomialTree &b2) const {
    return children.size() < b2.children.size();
}

void BinomialTree::print() const {
    std::cout << key << ' ';
    for(size_t i = 0; i < children.size(); ++i) {
        children[i].print();
    }
}

BinomialTree& meldTrees(BinomialTree &bTree1, BinomialTree &bTree2) {
    if(&bTree1 == &bTree2) {
        return bTree1;
    }
    if(bTree1.key > bTree2.key) {
        bTree2.children.push_back(bTree1);
        return bTree2;
    } else {
        bTree1.children.push_back(bTree2);
        return bTree1;
    }
}

class BinomialHeap : public IHeap {
private:
    std::list<BinomialTree> trees;
    std::list<BinomialTree>::const_iterator getMinIter() const;

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

std::list<BinomialTree>::const_iterator BinomialHeap::getMinIter() const {
    std::list<BinomialTree>::const_iterator iter = trees.begin();
    std::list<BinomialTree>::const_iterator min = iter;
    while(iter != trees.end()) {
        if(min->key > iter->key) {
            min = iter;
        }
        ++iter;
    }
    return min;
}

void BinomialHeap::insert(int key) {
    BinomialHeap heap(key);
    meld(heap);
}

int BinomialHeap::getMin() const {
    return getMinIter()->key;
}

void BinomialHeap::extractMin() {
    assert(!trees.empty());
    auto min = getMinIter();
    BinomialHeap minChildrenHeap;
    std::list<BinomialTree> minChildren(min->children.begin(), min->children.end());
    minChildrenHeap.trees = minChildren;
    trees.erase(min);
    meld(minChildrenHeap);
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
    auto curr = --trees.end();
    auto prev = curr--;
    while(prev != trees.begin()) {
        while(prev != trees.end() && curr->children.size() == prev->children.size()) {
            *curr = meldTrees(*curr, *prev);
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
