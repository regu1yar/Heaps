//
// Created by Роман Климовицкий on 10.12.2017.
//

#ifndef IHEAP_STANDARTHEAP_H
#define IHEAP_STANDARTHEAP_H


#include <iostream>
#include <set>
#include <cassert>
#include "IHeap.h"

class StandartHeap : public IHeap {
private:
    std::multiset<int> data;

public:
    StandartHeap();
    virtual void insert(int key);
    virtual int getMin() const;
    virtual void extractMin();
    virtual void meld(IHeap& heap);
    virtual void print() const;
    virtual void clear();
    virtual bool empty() const;
    virtual ~StandartHeap();
};

StandartHeap::StandartHeap() { }

void StandartHeap::insert(int key) {
    data.insert(key);
}

int StandartHeap::getMin() const {
    assert(!data.empty());
    return *data.begin();
}

void StandartHeap::extractMin() {
    assert(!data.empty());
    data.erase(data.begin());
}

void StandartHeap::meld(IHeap &heap) {
    StandartHeap& newHeap = dynamic_cast<StandartHeap&>(heap);
    if(this == &newHeap || newHeap.empty()) {
        return;
    }
    if(data.empty()) {
        data = newHeap.data;
        return;
    }
    data.insert(newHeap.data.begin(), newHeap.data.end());
}

void StandartHeap::print() const {
    for(auto iter = data.begin(); iter != data.end(); ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << std::endl;
}

void StandartHeap::clear() { data.clear(); }

bool StandartHeap::empty() const { return data.empty(); }

StandartHeap::~StandartHeap() { }


#endif //IHEAP_STANDARTHEAP_H
