//
// Created by Роман Климовицкий on 10.12.2017.
//

#ifndef IHEAP_SKEWNODE_H
#define IHEAP_SKEWNODE_H

#include <iostream>

class SkewNode {
public:
    int key;
    SkewNode* leftNode;
    SkewNode* rightNode;

    SkewNode(int key, SkewNode* leftistNode1 = nullptr, SkewNode* leftistNode2 = nullptr);
    void swapChildren();
    void print();
};


#endif //IHEAP_SKEWNODE_H
