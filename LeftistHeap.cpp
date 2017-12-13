//
// Created by Роман Климовицкий on 08.12.2017.
//

#include "LeftistHeap.h"
#include <cassert>

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

