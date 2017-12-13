//
// Created by Роман Климовицкий on 04.12.2017.
//

#ifndef IHEAP_IHEAP_H
#define IHEAP_IHEAP_H


class IHeap {
public:
    virtual void insert(int key) = 0;
    virtual int getMin() const = 0;
    virtual void extractMin() = 0;
    virtual void meld(IHeap& heap) = 0;
    virtual void print() const = 0;
    virtual void clear() = 0;
    virtual bool empty() const = 0;
    virtual ~IHeap() { }
};


#endif //IHEAP_IHEAP_H
