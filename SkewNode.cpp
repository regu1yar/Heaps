//
// Created by Роман Климовицкий on 10.12.2017.
//

#include "SkewNode.h"

SkewNode::SkewNode(int key, SkewNode *skewNode1, SkewNode *skewNode2) : key(key), leftNode(skewNode1),
                                                                        rightNode(skewNode2) {}

void SkewNode::swapChildren() {
    SkewNode* tmp = leftNode;
    leftNode = rightNode;
    rightNode = tmp;
}

void SkewNode::print() {
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