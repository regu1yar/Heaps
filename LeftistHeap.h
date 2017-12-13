//
// Created by Роман Климовицкий on 08.12.2017.
//

#ifndef IHEAP_LEFTHEAP_H
#define IHEAP_LEFTHEAP_H


#include "IHeap.h"
#include "LeftistNode.h"

class LeftistHeap : public IHeap {
private:
    LeftistNode* root;

    LeftistNode* systemMeld(LeftistNode* node1, LeftistNode* node2);
    void clearNode(LeftistNode* node);

public:
    LeftistHeap();
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
    virtual ~LeftistHeap();
};


#endif //IHEAP_LEFTHEAP_H
