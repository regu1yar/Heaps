//
// Created by Роман Климовицкий on 10.12.2017.
//

#ifndef IHEAP_SKEWHEAP_H
#define IHEAP_SKEWHEAP_H


#include <iostream>
#include <cassert>
#include "IHeap.h"

class SkewNode {
public:
    int key;
    SkewNode* leftNode;
    SkewNode* rightNode;

    SkewNode(int key, SkewNode* leftistNode1 = nullptr, SkewNode* leftistNode2 = nullptr);
    void swapChildren();
    void print();
};

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

class SkewHeap  : public IHeap {
private:
    SkewNode* root;

    SkewNode* systemMeld(SkewNode* node1, SkewNode* node2);
    void clearNode(SkewNode* node);

public:
    SkewHeap();
    SkewHeap(const SkewHeap& heap);
    SkewHeap& operator=(const SkewHeap& heap);
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
    virtual ~SkewHeap();
};

SkewHeap::SkewHeap() : root(nullptr) { }

void SkewHeap::clearNode(SkewNode *node) {
    if(node != nullptr) {
        clearNode(node->leftNode);
        clearNode(node->rightNode);
        delete node;
    }
}

void SkewHeap::insert(int key) { root = systemMeld(root, new SkewNode(key)); }

int SkewHeap::getMin() const {
    assert(root != nullptr);
    return root->key;
}

void SkewHeap::extractMin() {
    assert(root != nullptr);
    SkewNode* oldRoot = root;
    root = systemMeld(root->leftNode, root->rightNode);
    delete oldRoot;
}

SkewNode* SkewHeap::systemMeld(SkewNode *node1, SkewNode *node2) {
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
    node1->swapChildren();
    return node1;
}

void SkewHeap::meld(IHeap &heap) {
    SkewHeap& newHeap = dynamic_cast<SkewHeap&>(heap);
    if(this == &heap) {
        return;
    }
    root = systemMeld(root, newHeap.root);
    newHeap.root = nullptr;
}

void SkewHeap::clear() {
    clearNode(root);
    root = nullptr;
}

void SkewHeap::print() const {
    if(root != nullptr) {
        root->print();
    }
}

bool SkewHeap::empty() const { return root == nullptr; }

SkewHeap::~SkewHeap() {
    clear();
}


#endif //IHEAP_SKEWHEAP_H
