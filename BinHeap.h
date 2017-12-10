//
// Created by Роман Климовицкий on 07.12.2017.
//

#ifndef IHEAP_BINHEAP_H
#define IHEAP_BINHEAP_H


#include "IHeap.h"
#include "BinTree.h"

class BinHeap : public IHeap {
private:
    BinTree* firstTree;

    void addTree(BinTree* bTree);

public:
    BinHeap();
    explicit BinHeap(int key);
    explicit BinHeap(BinTree* tree);
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
};


#endif //IHEAP_BINHEAP_H
