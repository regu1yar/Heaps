//
// Created by Роман Климовицкий on 10.12.2017.
//

#include "SkewHeap.h"
#include <cassert>

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
