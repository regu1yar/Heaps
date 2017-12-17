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
    std::multiset<int> data_;

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
    data_.insert(key);
}

int StandardHeap::getMin() const {
    assert(!data_.empty());
    return *data_.begin();
}

void StandardHeap::extractMin() {
    assert(!data_.empty());
    data_.erase(data_.begin());
}

void StandardHeap::meld(IHeap &heap) {
    StandardHeap& newHeap = dynamic_cast<StandardHeap&>(heap);
    if(this == &newHeap || newHeap.empty()) {
        return;
    }
    if(data_.empty()) {
        data_ = newHeap.data_;
        return;
    }
    data_.insert(newHeap.data_.begin(), newHeap.data_.end());
}

void StandardHeap::print() const {
    for(auto iter = data_.begin(); iter != data_.end(); ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << std::endl;
}

void StandardHeap::clear() { data_.clear(); }

bool StandardHeap::empty() const { return data_.empty(); }

StandardHeap::~StandardHeap() { }


#endif //IHEAP_STANDARTHEAP_H
