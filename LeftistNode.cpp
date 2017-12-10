//
// Created by Роман Климовицкий on 09.12.2017.
//

#include "LeftistNode.h"

LeftistNode::LeftistNode(int key, LeftistNode *leftistNode1,
                         LeftistNode *leftistNode2, int rank) : key(key), leftNode(leftistNode1),
                                                                rightNode(leftistNode2), rank(rank) {}

void LeftistNode::update() {
    if(leftNode == nullptr) {
        if(rightNode != nullptr) {
            LeftistNode* tmp = rightNode;
            rightNode = leftNode;
            leftNode = tmp;
        }
        rank = 1;
        return;
    }
    if(rightNode == nullptr) {
        rank = 1;
        return;
    }
    if(leftNode->rank < rightNode->rank) {
        LeftistNode* tmp = rightNode;
        rightNode = leftNode;
        leftNode = tmp;
    }
    rank = rightNode->rank + 1;
}

void LeftistNode::print() {
    std::cout << key << ' ';
    std::cout << "TO LEFT" << std::endl;
    if(leftNode != nullptr) {
        leftNode->print();
    }
    //std::cout << std::endl;
    std::cout << "TO RIGHT" << std::endl;
    if(rightNode != nullptr) {
        rightNode->print();
    }
}