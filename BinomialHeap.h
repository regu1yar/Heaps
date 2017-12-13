//
// Created by Роман Климовицкий on 07.12.2017.
//

#ifndef IHEAP_BINOMIALHEAP_H
#define IHEAP_BINOMIALHEAP_H


#include <list>
#include "IHeap.h"
#include "BinomialTree.h"

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


#endif //IHEAP_BINOMIALHEAP_H
