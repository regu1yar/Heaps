//
// Created by Роман Климовицкий on 10.12.2017.
//

#ifndef IHEAP_STANDARTHEAP_H
#define IHEAP_STANDARTHEAP_H


#include <iostream>
#include <set>
#include <cassert>
#include "IHeap.h"

class StandardHeap : public IHeap {
private:
    std::multiset<int> data;

public:
    StandardHeap();
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void print() const;
    virtual void clear();
    virtual bool empty() const;
    virtual ~StandardHeap();
};

StandardHeap::StandardHeap() { }

void StandardHeap::insert(int key) {
    data.insert(key);
}

int StandardHeap::getMin() const {
    assert(!data.empty());
    return *data.begin();
}

void StandardHeap::extractMin() {
    assert(!data.empty());
    data.erase(data.begin());
}

void StandardHeap::meld(IHeap &heap) {
    StandardHeap& newHeap = dynamic_cast<StandardHeap&>(heap);
    if(this == &newHeap || newHeap.empty()) {
        return;
    }
    if(data.empty()) {
        data = newHeap.data;
        return;
    }
    data.insert(newHeap.data.begin(), newHeap.data.end());
}

void StandardHeap::print() const {
    for(auto iter = data.begin(); iter != data.end(); ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << std::endl;
}

void StandardHeap::clear() { data.clear(); }

bool StandardHeap::empty() const { return data.empty(); }

StandardHeap::~StandardHeap() { }


#endif //IHEAP_STANDARTHEAP_H
