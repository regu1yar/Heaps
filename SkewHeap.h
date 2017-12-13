//
// Created by Роман Климовицкий on 10.12.2017.
//

#ifndef IHEAP_SKEWHEAP_H
#define IHEAP_SKEWHEAP_H


#include "SkewNode.h"
#include "IHeap.h"

class SkewHeap  : public IHeap {
private:
    SkewNode* root;

    SkewNode* systemMeld(SkewNode* node1, SkewNode* node2);
    void clearNode(SkewNode* node);

public:
    SkewHeap();
    SkewHeap(const SkewHeap& heap);
    SkewHeap& operator=(const SkewHeap& heap);
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
    virtual ~SkewHeap();
};


#endif //IHEAP_SKEWHEAP_H
