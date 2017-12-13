//
// Created by Роман Климовицкий on 09.12.2017.
//

#include "LeftistNode.h"

LeftistNode::LeftistNode(int key, LeftistNode *leftistNode1,
                         LeftistNode *leftistNode2, int rank) : key(key), leftNode(leftistNode1),
                                                                rightNode(leftistNode2), rank(rank) {}

void LeftistNode::update() {
    if(leftNode == nullptr) {
        std::swap(leftNode, rightNode);
        rank = 1;
        return;
    }
    if(rightNode == nullptr) {
        rank = 1;
        return;
    }
    if(leftNode->rank < rightNode->rank) {
        std::swap(leftNode, rightNode);
    }
    rank = rightNode->rank + 1;
}

void LeftistNode::print() {
    std::cout << '(';
    if(leftNode != nullptr) {
        leftNode->print();
    }
    std::cout << ' ' << key << ' ';
    if(rightNode != nullptr) {
        rightNode->print();
    }
    std::cout << ')';
}