//
// Created by Роман Климовицкий on 16.12.2017.
//

#ifndef IHEAP_RANDOMTESTS_H
#define IHEAP_RANDOMTESTS_H


#include <iostream>
#include <vector>
#include <fstream>
#include "BinomialHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include "StandardHeap.h"
#include "gtest/gtest.h"
#include <time.h>

enum HeapMethods {
    AddHeap,
    Insert,
    GetMin,
    ExtractMin,
    Meld
};

class HardTest : public ::testing::Test {
public:
    static const int HEAP_TYPES = 3;
    static const int TEST_TYPES = 5;
    static const int MIN_KEY = -1000;
    static const int MAX_KEY = 1000;
    static const int TESTS = 10000;

protected:
    std::vector<IHeap*> heaps[HEAP_TYPES];
    std::vector<StandardHeap*> stdHeaps;

    void SetUp() {
        std::cout << "SET UP" << std::endl;
    }

    void TearDown() {
        for(int i = 0; i < HEAP_TYPES; ++i) {
            for(auto iter = heaps[i].rbegin(); iter != heaps[i].rend(); ++iter) {
                delete *iter;
            }
        }
        for(auto iter = stdHeaps.rbegin(); iter != stdHeaps.rend(); ++iter) {
            delete *iter;
        }
        std::cout << "TEARED DOWN" << std::endl;
    }

    void callMethod(int heapNumber, HeapMethods method, int param1 = 0, int param2 = 0) {
        switch(method) {
            case AddHeap:
                callAddHeap(heapNumber, param1);
                break;
            case Insert:
                callInsert(heapNumber, param1, param2);
                break;
            case GetMin:
                callGetMin(heapNumber, param1);
                break;
            case ExtractMin:
                callExtractMin(heapNumber, param1);
                break;
            case Meld:
                callMeld(heapNumber, param1, param2);
                break;
            default:
                std::cout << "NO SUCH METHOD " << method << std::endl;
        }
    }

    void callAddHeap(int heapNumber, int key);
    void callInsert(int heapNumber, int index, int key);
    void callGetMin(int heapNumber, int index);
    void callExtractMin(int heapNumber, int index);
    void callMeld(int heapNumber, int index1, int index2);

public:
    void testGeneration(int tests);
};

void HardTest::testGeneration(int tests) {
    std::filebuf testBuf;
    testBuf.open("tests.txt", std::ios::out);
    std::ostream testStream(&testBuf);
    std::vector<int> heaps;
    for(int i = 1; i <= tests; ++i) {
        int test = rand() % TEST_TYPES;
        switch(test) {
            case AddHeap: {
                int addKey = rand() % (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
                testStream << test << ' ' << addKey << ' ' << 0 << std::endl;
                heaps.push_back(1);
                break;
            }
            case Insert: {
                if (heaps.size() != 0) {
                    int insertIndex = rand() % heaps.size();
                    int insertKey = rand() % (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
                    testStream << test << ' ' << insertIndex << ' ' << insertKey << std::endl;
                    ++(heaps[insertIndex]);
                }
                break;
            }
            case GetMin: {
                if (heaps.size() != 0) {
                    int getIndex = rand() % heaps.size();
                    if(heaps[getIndex] != 0) {
                        testStream << test << ' ' << getIndex << ' ' << 0 << std::endl;
                    }
                }
                break;
            }
            case ExtractMin: {
                if (heaps.size() != 0) {
                    int extractIndex = rand() % heaps.size();
                    if(heaps[extractIndex] != 0) {
                        testStream << test << ' ' << extractIndex << ' ' << 0 << std::endl;
                        --(heaps[extractIndex]);
                    }
                }
                break;
            }
            case Meld: {
                if (heaps.size() != 0) {
                    int meldIndex1 = rand() % heaps.size();
                    int meldIndex2 = rand() % heaps.size();
                    testStream << test << ' ' << meldIndex1 << ' ' << meldIndex2 << std::endl;
                    if (meldIndex1 != meldIndex2) {
                        heaps[meldIndex1] += heaps[meldIndex2];
                        heaps.erase(heaps.begin() + meldIndex2);
                    }
                }
                break;
            }
            default:
                assert(false);
                break;
        }
    }
    testBuf.close();
}

void HardTest::callAddHeap(int heapNumber, int key) {
    IHeap* newHeap;
    if(heapNumber == 0) {
        newHeap = new BinomialHeap;
    } else if(heapNumber == 1) {
        newHeap = new LeftistHeap;
    } else {
        newHeap = new SkewHeap;
    }
    heaps[heapNumber].push_back(newHeap);
    StandardHeap* newStdHeap = new StandardHeap;
    stdHeaps.push_back(newStdHeap);
    heaps[heapNumber].back()->insert(key);
    stdHeaps.back()->insert(key);
    int heapMin_add = heaps[heapNumber].back()->getMin();
    int stdHeapMin_add = stdHeaps.back()->getMin();
    EXPECT_EQ(heapMin_add, stdHeapMin_add) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_add << " != "
                                           << stdHeapMin_add << " == STDHEAPMIN AFTER ADDING HEAP" << std::endl;
}

void HardTest::callInsert(int heapNumber, int index, int key) {
    if(index >= stdHeaps.size()) {
        std::cout << "UNSUCCESSFUL INSERT(" << index << ") : SIZE == " << stdHeaps.size() << " <= " << index
                  << " == INDEX" << std::endl;
        return;
    }
    heaps[heapNumber][index]->insert(key);
    stdHeaps[index]->insert(key);
    int heapMin_insert = heaps[heapNumber][index]->getMin();
    int stdHeapMin_insert = stdHeaps[index]->getMin();
    EXPECT_EQ(heapMin_insert, stdHeapMin_insert) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_insert << " != "
                                                 << stdHeapMin_insert << " == STDHEAPMIN AFTER INSERTING" << std::endl;
}

void HardTest::callGetMin(int heapNumber, int index) {
    if(index >= stdHeaps.size()) {
        std::cout << "UNSUCCESSFUL GETMIN(" << index << ") : SIZE == " << stdHeaps.size() << " <= " << index
                  << " == INDEX" << std::endl;
        return;
    }
    if(stdHeaps[index]->empty()) {
        std::cout << "UNSUCCESSFUL GETMIN(" << index << ") : HEAP IS EMPTY" << std::endl;
        return;
    }
    int heapMin_getMin = heaps[heapNumber][index]->getMin();
    int stdHeapMin_getMin = stdHeaps[index]->getMin();
    EXPECT_EQ(heapMin_getMin, stdHeapMin_getMin) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_getMin << " != "
                                                 << stdHeapMin_getMin << " == STDHEAPMIN AFTER GETTING MIN" << std::endl;
}

void HardTest::callExtractMin(int heapNumber, int index) {
    if(index >= stdHeaps.size()) {
        std::cout << "UNSUCCESSFUL EXTRACTMIN(" << index << ") : SIZE == " << stdHeaps.size() << " <= "
                  << index << " == INDEX" << std::endl;
        return;
    }
    if(stdHeaps[index]->empty()) {
        std::cout << "UNSUCCESSFUL EXTRACTMIN(" << index << ") : HEAP IS EMPTY" << std::endl;
        return;
    }
    heaps[heapNumber][index]->extractMin();
    stdHeaps[index]->extractMin();
    bool heapEmptyness = stdHeaps[index]->empty();
    bool stdHeapEmtyness = heaps[heapNumber][index]->empty();
    ASSERT_EQ(heapEmptyness, stdHeapEmtyness) << "HEAP # " << heapNumber << " HEAPEMPTY == " << heapEmptyness << " != "
                                              << stdHeapEmtyness << " == STDHEAPEMPTY AFTER EXTRACTING MIN" << std::endl;
    if(!heapEmptyness && !stdHeapEmtyness) {
        int heapMin_extractMin = heaps[heapNumber][index]->getMin();
        int stdHeapMin_extractMin = stdHeaps[index]->getMin();
        EXPECT_EQ(heapMin_extractMin, stdHeapMin_extractMin) << "HEAP # " << heapNumber << " HEAPMIN == "
                                                             << heapMin_extractMin << " != " << stdHeapMin_extractMin
                                                             << " == STDHEAPMIN AFTER EXTRACTING MIN" << std::endl;
    }
}

void HardTest::callMeld(int heapNumber, int index1, int index2) {
    if(index1 >= stdHeaps.size()) {
        std::cout << "UNSUCCESSFUL EXTRACTMIN(" << index1 << ") : SIZE == " << stdHeaps.size() << " <= "
                  << index1 << " == INDEX" << std::endl;
        return;
    }
    if(index2 >= stdHeaps.size()) {
        std::cout << "UNSUCCESSFUL EXTRACTMIN(" << index2 << ") : SIZE == " << stdHeaps.size() << " <= "
                  << index2 << " == INDEX" << std::endl;
        return;
    }
    heaps[heapNumber][index1]->meld(*heaps[heapNumber][index2]);
    stdHeaps[index1]->meld(*stdHeaps[index2]);
    bool heapEmptyness = stdHeaps[index1]->empty();
    bool stdHeapEmtyness = heaps[heapNumber][index1]->empty();
    ASSERT_EQ(heapEmptyness, stdHeapEmtyness) << "HEAP # " << heapNumber << " HEAPEMPTY == " << heapEmptyness << " != "
                                              << stdHeapEmtyness << " == STDHEAPEMPTY AFTER MELDING" << std::endl;
    if(!heapEmptyness && !stdHeapEmtyness) {
        int heapMin_meld = heaps[heapNumber][index1]->getMin();
        int stdHeapMin_meld = stdHeaps[index1]->getMin();
        EXPECT_EQ(heapMin_meld, stdHeapMin_meld) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_meld << " != "
                                                 << stdHeapMin_meld << " == STDHEAPMIN AFTER MELDING" << std::endl;
        if (index1 != index2) {
            std::swap(heaps[heapNumber][index2], heaps[heapNumber].back());
            delete heaps[heapNumber].back();
            heaps[heapNumber].pop_back();
            std::swap(stdHeaps[index2], stdHeaps.back());
            delete stdHeaps.back();
            stdHeaps.pop_back();
        }
    }
}

TEST_F(HardTest, MeldTest) {
    for(size_t i = 0; i < 100; ++i) {
        IHeap* binomialHeap = new BinomialHeap();
        IHeap* leftistHeap = new LeftistHeap();
        IHeap* skewHeap = new SkewHeap();
        StandardHeap* stdHeap = new StandardHeap();
        for(size_t j = 0; j < 100; ++j) {
            int key = rand() % (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
            binomialHeap->insert(key);
            leftistHeap->insert(key);
            skewHeap->insert(key);
            stdHeap->insert(key);
        }
        heaps[0].push_back(binomialHeap);
        heaps[1].push_back(leftistHeap);
        heaps[2].push_back(skewHeap);
        stdHeaps.push_back(stdHeap);
    }
    while(stdHeaps.size() > 1) {
        size_t heap1 = rand() % stdHeaps.size();
        size_t heap2 = rand() % stdHeaps.size();
        for(size_t i = 0; i < HEAP_TYPES; ++i) {
            heaps[i][heap1]->meld(*heaps[i][heap2]);
        }
        stdHeaps[heap1]->meld(*stdHeaps[heap2]);
        EXPECT_EQ(heaps[0][heap1]->getMin(), stdHeaps[heap1]->getMin()) << "BAD MELD ON BINOMIAL HEAP" << std::endl;
        EXPECT_EQ(heaps[1][heap1]->getMin(), stdHeaps[heap1]->getMin()) << "BAD MELD ON LEFTIST HEAP" << std::endl;
        EXPECT_EQ(heaps[2][heap1]->getMin(), stdHeaps[heap1]->getMin()) << "BAD MELD ON SKEW HEAP" << std::endl;
        if(heap1 != heap2) {
            for(size_t i = 0; i < HEAP_TYPES; ++i) {
                heaps[i].erase(heaps[i].begin() + heap2);
            }
            stdHeaps.erase(stdHeaps.begin() + heap2);
        }
    }
    std::cout << "MELD TEST PASSED" << std::endl;
}

TEST_F(HardTest, RandomTest) {
    std::filebuf timeBuf;
    timeBuf.open("time.txt", std::ios::out);
    std::ifstream in;
    std::ostream timeStream(&timeBuf);
    for(int tests = TESTS / 100; tests <= TESTS; tests += TESTS / 100) {
        testGeneration(tests);
        timeStream << tests << " operations:" << std::endl;
        for(int i = 0 ; i < 3; ++i) {
            in.open("tests.txt");
            int test, param1, param2;
            long long begin = clock();
            while(in >> test >> param1 >> param2) {
                callMethod(i, (HeapMethods)test, param1, param2);
            }
            long long end = clock();
            if(i == 0) {
                timeStream << "Binomial Heap";
            } else if(i == 1) {
                timeStream << "Leftist Heap";
            } else {
                timeStream << "Skew Heap";
            }
            timeStream << ": clocks - " << end - begin << " seconds - " << (double)(end - begin) / CLOCKS_PER_SEC
                       << std::endl;
            heaps[i].clear();
            stdHeaps.clear();
            in.close();
            in.clear();
        }
        timeStream << std::endl;
    }
    timeBuf.close();
}

#endif //IHEAP_RANDOMTESTS_H
