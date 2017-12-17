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
    int key_;
    std::vector<BinomialTree> children_;

public:
    explicit BinomialTree(int key);
    BinomialTree(const BinomialTree& bTree);
    BinomialTree& operator=(const BinomialTree& bTree);
    bool operator<(const BinomialTree& b) const;
    void print() const;

    friend class BinomialHeap;
    friend BinomialTree& meldTrees(BinomialTree &bTree1, BinomialTree &bTree2);
};

BinomialTree::BinomialTree(int key) : key_(key) { }

BinomialTree::BinomialTree(const BinomialTree& bTree) : key_(bTree.key_), children_(bTree.children_) { }

BinomialTree& BinomialTree::operator=(const BinomialTree &bTree) {
    if(this == &bTree) {
        return *this;
    }
    key_ = bTree.key_;
    children_ = bTree.children_;
    return *this;
}

bool BinomialTree::operator<(const BinomialTree &b2) const {
    return children_.size() < b2.children_.size();
}

void BinomialTree::print() const {
    std::cout << key_ << ' ';
    for(size_t i = 0; i < children_.size(); ++i) {
        children_[i].print();
    }
}

BinomialTree& meldTrees(BinomialTree &bTree1, BinomialTree &bTree2) {
    if(&bTree1 == &bTree2) {
        return bTree1;
    }
    if(bTree1.key_ > bTree2.key_) {
        bTree2.children_.push_back(bTree1);
        return bTree2;
    } else {
        bTree1.children_.push_back(bTree2);
        return bTree1;
    }
}

class BinomialHeap : public IHeap {
private:
    std::list<BinomialTree> trees_;
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
    trees_.push_back(firstTree);
}

BinomialHeap::BinomialHeap(BinomialTree& tree) {
    trees_.clear();
    trees_.push_back(tree);
}

std::list<BinomialTree>::const_iterator BinomialHeap::getMinIter() const {
    std::list<BinomialTree>::const_iterator iter = trees_.begin();
    std::list<BinomialTree>::const_iterator min = iter;
    while(iter != trees_.end()) {
        if(min->key_ > iter->key_) {
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
    return getMinIter()->key_;
}

void BinomialHeap::extractMin() {
    assert(!trees_.empty());
    auto min = getMinIter();
    BinomialHeap minChildrenHeap;
    std::list<BinomialTree> minChildren(min->children_.begin(), min->children_.end());
    minChildrenHeap.trees_ = minChildren;
    trees_.erase(min);
    meld(minChildrenHeap);
}

void BinomialHeap::meld(IHeap& heap) {
    BinomialHeap& binHeap = dynamic_cast<BinomialHeap&>(heap);
    if(this == &binHeap || binHeap.empty()) {
        return;
    }
    if(empty()) {
        trees_ = binHeap.trees_;
        return;
    }
    trees_.merge(binHeap.trees_);
    auto curr = --trees_.end();
    auto prev = curr--;
    while(prev != trees_.begin()) {
        while(prev != trees_.end() && curr->children_.size() == prev->children_.size()) {
            *curr = meldTrees(*curr, *prev);
            trees_.erase(prev);
            prev = std::next(curr);
        }
        prev = curr--;
    }
}

void BinomialHeap::clear() { trees_.clear(); }

void BinomialHeap::print() const {
    for(auto iter = trees_.begin(); iter != trees_.end(); ++iter) {
        std::cout << "TREE ";
        iter->print();
    }
    std::cout << std::endl;
}

bool BinomialHeap::empty() const { return trees_.empty(); }

BinomialHeap::~BinomialHeap() { }


#endif //IHEAP_BINOMIALHEAP_H
