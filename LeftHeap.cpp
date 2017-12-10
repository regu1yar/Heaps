//
// Created by Роман Климовицкий on 08.12.2017.
//

#include "LeftHeap.h"
#include <iostream>

LeftHeap::LeftHeap() : root(nullptr) { }

LeftHeap::LeftHeap(const LeftHeap &heap) {
    root = nullptr;
    *this = heap;
}

void LeftHeap::clearNode(LeftistNode *node) {
    if(node != nullptr) {
        clearNode(node->leftNode);
        clearNode(node->rightNode);
        delete node;
        node = nullptr;
    }
}

LeftHeap& LeftHeap::operator=(const LeftHeap &heap) {
    if(this != &heap) {
        clear();
        root = heap.root;
    }
    return *this;
}

void LeftHeap::insert(int key) { root = systemMeld(root, new LeftistNode(key)); }

int LeftHeap::getMin() const { return root->key; }

void LeftHeap::extractMin() {
    LeftistNode* oldRoot = root;
    root = systemMeld(root->leftNode, root->rightNode);
    delete oldRoot;
}

LeftistNode* LeftHeap::systemMeld(LeftistNode *node1, LeftistNode *node2) {
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

void LeftHeap::meld(IHeap &heap) {
    LeftHeap& newHeap = dynamic_cast<LeftHeap&>(heap);
    if(this == &heap) {
        return;
    }
    root = systemMeld(root, newHeap.root);
}

void LeftHeap::clear() {
    clearNode(root);
}

void LeftHeap::print() const {
    if(root != nullptr) {
        root->print();
    }
}

bool LeftHeap::empty() const { return root == nullptr; }

LeftHeap::~LeftHeap() {
    clear();
}

