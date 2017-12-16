//
// Created by Роман Климовицкий on 10.12.2017.
//

#ifndef IHEAP_SKEWHEAP_H
#define IHEAP_SKEWHEAP_H


#include <iostream>
#include <cassert>
#include "LSHeap.h"

class SkewHeap : public LSHeap {
private:
    virtual Node* systemMeld(Node* node1, Node* node2);
};

Node* SkewHeap::systemMeld(Node *node1, Node *node2) {
    if(node1 == nullptr) {
        return node2;
    }
    if(node2 == nullptr) {
        return node1;
    }
    if(node1->getKey() > node2->getKey()) {
        std::swap(node1, node2);
    }
    node1->setRightNode(systemMeld(node1->getRightNode(), node2));
    node1->swapChildren();
    return node1;
}


#endif //IHEAP_SKEWHEAP_H
