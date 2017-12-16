//
// Created by Роман Климовицкий on 16.12.2017.
//

#ifndef IHEAP_LSHEAP_H
#define IHEAP_LSHEAP_H


#include <iostream>
#include <cassert>
#include "IHeap.h"

class Node {
private:
    int key;
    int rank = 0;
    Node* leftNode;
    Node* rightNode;

public:
    Node(int key, Node* node1 = nullptr, Node* node2 = nullptr, int rank = 0);
    void update();
    void swapChildren();
    int getKey() const { return key; }
    Node* getRightNode() const { return rightNode; }
    void setRightNode(Node* node) { rightNode = node; }
    void print();

    friend class LSHeap;
};

Node::Node(int key, Node *node1,
                         Node *node2, int rank) : key(key), leftNode(node1),
                                                                rightNode(node2), rank(rank) {}

void Node::update() {
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

void Node::swapChildren() {
    std::swap(leftNode, rightNode);
}

void Node::print() {
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


class LSHeap : public IHeap {
private:
    Node* root;

    virtual Node* systemMeld(Node* node1, Node* node2) = 0;
    void clearNode(Node* node);

public:
    LSHeap();
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
    virtual ~LSHeap();
};

LSHeap::LSHeap() : root(nullptr) { }

void LSHeap::clearNode(Node *node) {
    if(node != nullptr) {
        clearNode(node->leftNode);
        clearNode(node->rightNode);
        delete node;
    }
}

void LSHeap::insert(int key) { root = systemMeld(root, new Node(key)); }

int LSHeap::getMin() const {
    assert(root != nullptr);
    return root->key;
}

void LSHeap::extractMin() {
    assert(root != nullptr);
    Node* oldRoot = root;
    root = systemMeld(root->leftNode, root->rightNode);
    delete oldRoot;
}

void LSHeap::meld(IHeap &heap) {
    LSHeap& newHeap = dynamic_cast<LSHeap&>(heap);
    if(this == &heap) {
        return;
    }
    root = systemMeld(root, newHeap.root);
    newHeap.root = nullptr;
}

void LSHeap::clear() {
    clearNode(root);
    root = nullptr;
}

void LSHeap::print() const {
    if(root != nullptr) {
        root->print();
    }
}

bool LSHeap::empty() const { return root == nullptr; }

LSHeap::~LSHeap() { clear(); }

#endif //IHEAP_LSHEAP_H
