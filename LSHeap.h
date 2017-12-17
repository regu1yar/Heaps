//
// Created by Роман Климовицкий on 16.12.2017.
//

#ifndef IHEAP_LSHEAP_H
#define IHEAP_LSHEAP_H


#include <iostream>
#include <cassert>
#include "IHeap.h"

struct LeftistNode {
    int key_;
    int rank_ = 0;
    LeftistNode* leftNode_;
    LeftistNode* rightNode_;
};

struct SkewNode {
    int key_;
    SkewNode* leftNode_;
    SkewNode* rightNode_;
};

template<class Node>
void systemPrint(Node* node) {
    std::cout << '(';
    if(node->leftNode_ != nullptr) {
        systemPrint<Node>(node->leftNode_);
    }
    std::cout << ' ' << node->key_ << ' ';
    if(node->rightNode_ != nullptr) {
        systemPrint<Node>(node->rightNode_);
    }
    std::cout << ')';
}

void update(LeftistNode* node) {
    if(node->leftNode_ == nullptr) {
        std::swap(node->leftNode_, node->rightNode_);
        node->rank_ = 1;
        return;
    }
    if(node->rightNode_ == nullptr) {
        node->rank_ = 1;
        return;
    }
    if(node->leftNode_->rank_ < node->rightNode_->rank_) {
        std::swap(node->leftNode_, node->rightNode_);
    }
    node->rank_ = node->rightNode_->rank_ + 1;
}

void update(SkewNode* node) {
    std::swap(node->leftNode_, node->rightNode_);
}


template<class Node>
class LSHeap : public IHeap {
private:
    Node* root_;

    Node* systemMeld(Node* node1, Node* node2);
    void clearNode(Node* node);

public:
    LSHeap() : root_(nullptr) { }
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void clear();
    virtual void print() const;
    virtual bool empty() const;
    virtual ~LSHeap();
};

template<class Node>
void LSHeap<Node>::clearNode(Node *node) {
    if(node != nullptr) {
        clearNode(node->leftNode_);
        clearNode(node->rightNode_);
        delete node;
    }
}

template<class Node>
void LSHeap<Node>::insert(int key) {
    Node* newNode = new Node;
    newNode->key_ = key;
    newNode->leftNode_ = nullptr;
    newNode->rightNode_ = nullptr;
    root_ = systemMeld(root_, newNode);
}

template<class Node>
int LSHeap<Node>::getMin() const {
    assert(root_ != nullptr);
    return root_->key_;
}

template<class Node>
void LSHeap<Node>::extractMin() {
    assert(root_ != nullptr);
    Node* oldRoot = root_;
    root_ = systemMeld(root_->leftNode_, root_->rightNode_);
    delete oldRoot;
}

template<class Node>
Node* LSHeap<Node>::systemMeld(Node *node1, Node *node2) {
    if(node1 == nullptr) {
        return node2;
    }
    if(node2 == nullptr) {
        return node1;
    }
    if(node1->key_ > node2->key_) {
        std::swap(node1, node2);
    }
    node1->rightNode_ = systemMeld(node1->rightNode_, node2);
    update(node1->rightNode_);
    return node1;
}

template<class Node>
void LSHeap<Node>::meld(IHeap &heap) {
    LSHeap& newHeap = dynamic_cast<LSHeap&>(heap);
    if(this == &heap) {
        return;
    }
    root_ = systemMeld(root_, newHeap.root_);
    newHeap.root_ = nullptr;
}

template<class Node>
void LSHeap<Node>::clear() {
    clearNode(root_);
    root_ = nullptr;
}

template<class Node>
void LSHeap<Node>::print() const {
    if(root_ != nullptr) {
        systemPrint<Node>(root_);
    }
}

template<class Node>
bool LSHeap<Node>::empty() const { return root_ == nullptr; }

template<class Node>
LSHeap<Node>::~LSHeap() { clear(); }

#endif //IHEAP_LSHEAP_H
