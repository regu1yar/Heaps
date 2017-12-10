//
// Created by Роман Климовицкий on 10.12.2017.
//

#include "StandartHeap.h"

StandartHeap::StandartHeap() { }

void StandartHeap::insert(int key) {
    data.insert(key);
}

int StandartHeap::getMin() const {
    return *data.begin();
}

void StandartHeap::extractMin() {
    data.erase(data.begin());
}

void StandartHeap::meld(IHeap &heap) {
    if(this == &heap) {
        return;
    }
    StandartHeap& newHeap = dynamic_cast<StandartHeap&>(heap);
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