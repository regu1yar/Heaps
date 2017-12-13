//
// Created by Роман Климовицкий on 10.12.2017.
//

#include "SkewNode.h"

SkewNode::SkewNode(int key, SkewNode *skewNode1, SkewNode *skewNode2) : key(key), leftNode(skewNode1),
                                                                        rightNode(skewNode2) {}

void SkewNode::swapChildren() {
    std::swap(leftNode, rightNode);
}

void SkewNode::print() {
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