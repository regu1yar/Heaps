//
// Created by Роман Климовицкий on 08.12.2017.
//

#ifndef IHEAP_LEFTHEAP_H
#define IHEAP_LEFTHEAP_H


#include "IHeap.h"
#include "LeftistNode.h"

class LeftHeap : public IHeap {
private:
    LeftistNode* root;

    LeftistNode* systemMeld(LeftistNode* node1, LeftistNode* node2);
    void clearNode(LeftistNode* node);

public:
    LeftHeap();
    LeftHeap(const LeftHeap& heap);
    LeftHeap& operator=(const LeftHeap& heap);
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
    ~LeftHeap();
};


#endif //IHEAP_LEFTHEAP_H
