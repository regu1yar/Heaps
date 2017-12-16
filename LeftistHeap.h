//
// Created by Роман Климовицкий on 08.12.2017.
//

#ifndef IHEAP_LEFTHEAP_H
#define IHEAP_LEFTHEAP_H


#include "LSHeap.h"

class LeftistHeap : public LSHeap {
private:
    virtual Node* systemMeld(Node* node1, Node* node2);
};

Node* LeftistHeap::systemMeld(Node *node1, Node *node2) {
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
    node1->update();
    return node1;
}


#endif //IHEAP_LEFTHEAP_H
