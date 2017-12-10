//
// Created by Роман Климовицкий on 09.12.2017.
//

#ifndef IHEAP_LEFTISTNODE_H
#define IHEAP_LEFTISTNODE_H

#include <iostream>

class LeftistNode {
public:
    int key;
    int rank = 0;
    LeftistNode* leftNode;
    LeftistNode* rightNode;

    LeftistNode(int key, LeftistNode* leftistNode1 = nullptr, LeftistNode* leftistNode2 = nullptr, int rank = 0);
    void update();
    void print();
};


#endif //IHEAP_LEFTISTNODE_H
