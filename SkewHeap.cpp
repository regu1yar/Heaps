//
// Created by Роман Климовицкий on 10.12.2017.
//

#include "SkewHeap.h"

SkewHeap::SkewHeap() : root(nullptr) { }

SkewHeap::SkewHeap(const SkewHeap &heap) {
    root = nullptr;
    *this = heap;
}

void SkewHeap::clearNode(SkewNode *node) {
    if(node != nullptr) {
        clearNode(node->leftNode);
        clearNode(node->rightNode);
        delete node;
    }
}

SkewHeap& SkewHeap::operator=(const SkewHeap &heap) {
    if(this != &heap) {
        clear();
        root = heap.root;
    }
    return *this;
}

void SkewHeap::insert(int key) { root = systemMeld(root, new SkewNode(key)); }

int SkewHeap::getMin() const { return root->key; }

void SkewHeap::extractMin() {
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
}

void SkewHeap::clear() {
    clearNode(root);
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
