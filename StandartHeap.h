//
// Created by Роман Климовицкий on 10.12.2017.
//

#ifndef IHEAP_STANDARTHEAP_H
#define IHEAP_STANDARTHEAP_H


#include <iostream>
#include <set>
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


#endif //IHEAP_STANDARTHEAP_H
