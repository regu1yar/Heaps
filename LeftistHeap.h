//
// Created by Роман Климовицкий on 08.12.2017.
//

#ifndef IHEAP_LEFTHEAP_H
#define IHEAP_LEFTHEAP_H


#include <cassert>
#include "IHeap.h"

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

LeftistHeap::LeftistHeap() : root(nullptr) { }

void LeftistHeap::clearNode(LeftistNode *node) {
    if(node != nullptr) {
        clearNode(node->leftNode);
        clearNode(node->rightNode);
        delete node;
    }
}

void LeftistHeap::insert(int key) { root = systemMeld(root, new LeftistNode(key)); }

int LeftistHeap::getMin() const {
    assert(root != nullptr);
    return root->key;
}

void LeftistHeap::extractMin() {
    assert(root != nullptr);
    LeftistNode* oldRoot = root;
    root = systemMeld(root->leftNode, root->rightNode);
    delete oldRoot;
}

LeftistNode* LeftistHeap::systemMeld(LeftistNode *node1, LeftistNode *node2) {
    if(node1 == nullptr) {
        return node2;
    }
    if(node2 == nullptr) {
        return node1;
    }
    if(node1->key > node2->key) {
        std::swap(node1, node2);
    }
    node1->rightNode = systemMeld(node1->rightNode, node2);
    node1->update();
    return node1;
}

void LeftistHeap::meld(IHeap &heap) {
    LeftistHeap& newHeap = dynamic_cast<LeftistHeap&>(heap);
    if(this == &heap) {
        return;
    }
    root = systemMeld(root, newHeap.root);
    newHeap.root = nullptr;
}

void LeftistHeap::clear() {
    clearNode(root);
    root = nullptr;
}

void LeftistHeap::print() const {
    if(root != nullptr) {
        root->print();
    }
}

bool LeftistHeap::empty() const { return root == nullptr; }

LeftistHeap::~LeftistHeap() {
    clear();
}


#endif //IHEAP_LEFTHEAP_H
