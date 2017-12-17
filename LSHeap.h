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
    int key_;
    int rank_ = 0;
    Node* leftNode_;
    Node* rightNode_;

public:
    Node(int key, Node* node1 = nullptr, Node* node2 = nullptr, int rank = 0);
    void update();
    void swapChildren();
    int getKey() const { return key_; }
    Node* getRightNode() const { return rightNode_; }
    void setRightNode(Node* node) { rightNode_ = node; }
    void print();

    friend class LSHeap;
};

Node::Node(int key, Node *node1,
                         Node *node2, int rank) : key_(key), leftNode_(node1),
                                                                rightNode_(node2), rank_(rank) {}

void Node::update() {
    if(leftNode_ == nullptr) {
        std::swap(leftNode_, rightNode_);
        rank_ = 1;
        return;
    }
    if(rightNode_ == nullptr) {
        rank_ = 1;
        return;
    }
    if(leftNode_->rank_ < rightNode_->rank_) {
        std::swap(leftNode_, rightNode_);
    }
    rank_ = rightNode_->rank_ + 1;
}

void Node::swapChildren() {
    std::swap(leftNode_, rightNode_);
}

void Node::print() {
    std::cout << '(';
    if(leftNode_ != nullptr) {
        leftNode_->print();
    }
    std::cout << ' ' << key_ << ' ';
    if(rightNode_ != nullptr) {
        rightNode_->print();
    }
    std::cout << ')';
}


class LSHeap : public IHeap {
private:
    Node* root_;

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

LSHeap::LSHeap() : root_(nullptr) { }

void LSHeap::clearNode(Node *node) {
    if(node != nullptr) {
        clearNode(node->leftNode_);
        clearNode(node->rightNode_);
        delete node;
    }
}

void LSHeap::insert(int key) { root_ = systemMeld(root_, new Node(key)); }

int LSHeap::getMin() const {
    assert(root_ != nullptr);
    return root_->key_;
}

void LSHeap::extractMin() {
    assert(root_ != nullptr);
    Node* oldRoot = root_;
    root_ = systemMeld(root_->leftNode_, root_->rightNode_);
    delete oldRoot;
}

void LSHeap::meld(IHeap &heap) {
    LSHeap& newHeap = dynamic_cast<LSHeap&>(heap);
    if(this == &heap) {
        return;
    }
    root_ = systemMeld(root_, newHeap.root_);
    newHeap.root_ = nullptr;
}

void LSHeap::clear() {
    clearNode(root_);
    root_ = nullptr;
}

void LSHeap::print() const {
    if(root_ != nullptr) {
        root_->print();
    }
}

bool LSHeap::empty() const { return root_ == nullptr; }

LSHeap::~LSHeap() { clear(); }

#endif //IHEAP_LSHEAP_H
