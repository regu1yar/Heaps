#include <iostream>
#include <vector>
#include <fstream>
#include "BinHeap.h"
#include "LeftHeap.h"
#include "SkewHeap.h"
#include "StandartHeap.h"
#include "gtest/gtest.h"
#include <time.h>

const int HEAP_TYPES = 3;
const int TEST_TYPES = 5;
const int MIN_KEY = -1000;
const int MAX_KEY = 1000;
const int TESTS = 1000;

enum Method {
    AddHeap = 0,
    Insert,
    GetMin,
    ExtractMin,
    Meld
};

class FunctionalTest : public ::testing::Test {
protected:
    std::vector<IHeap*> heaps[HEAP_TYPES];
    std::vector<StandartHeap*> stdHeaps;

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

    void callMethod(int heapNumber, Method method, int param1 = 0, int param2 = 0) {
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
};

void FunctionalTest::callAddHeap(int heapNumber, int key) {
    IHeap* newHeap;
    if(heapNumber == 0) {
        newHeap = new BinHeap;
    } else if(heapNumber == 1) {
        newHeap = new LeftHeap;
    } else {
        newHeap = new SkewHeap;
    }
    heaps[heapNumber].push_back(newHeap);
    StandartHeap* newStdHeap = new StandartHeap;
    stdHeaps.push_back(newStdHeap);
    heaps[heapNumber].back()->insert(key);
    stdHeaps.back()->insert(key);
    int heapMin_add = heaps[heapNumber].back()->getMin();
    int stdHeapMin_add = stdHeaps.back()->getMin();
    EXPECT_EQ(heapMin_add, stdHeapMin_add) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_add << " != "
                                           << stdHeapMin_add << " == STDHEAPMIN AFTER ADDING HEAP" << std::endl;
}

void FunctionalTest::callInsert(int heapNumber, int index, int key) {
    if(index >= stdHeaps.size()) {
        std::cout << "UNSUCCESSFUL INSERT(" << index << ") : SIZE == " << stdHeaps.size() << " <= "
                  << index << " == INDEX" << std::endl;
        return;
    }
    heaps[heapNumber][index]->insert(key);
    stdHeaps[index]->insert(key);
    int heapMin_insert = heaps[heapNumber][index]->getMin();
    int stdHeapMin_insert = stdHeaps[index]->getMin();
    EXPECT_EQ(heapMin_insert, stdHeapMin_insert) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_insert << " != "
                                                 << stdHeapMin_insert << " == STDHEAPMIN AFTER INSERTING" << std::endl;
}

void FunctionalTest::callGetMin(int heapNumber, int index) {
    if(stdHeaps.empty()) {
        std::cout << "UNSUCCESSFUL GETMIN() : HEAP IS EMPTY" << std::endl;
        return;
    }
    int heapMin_getMin = heaps[heapNumber][index]->getMin();
    int stdHeapMin_getMin = stdHeaps[index]->getMin();
    EXPECT_EQ(heapMin_getMin, stdHeapMin_getMin) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_getMin << " != "
                                                 << stdHeapMin_getMin << " == STDHEAPMIN AFTER GETTING MIN" << std::endl;
}

void FunctionalTest::callExtractMin(int heapNumber, int index) {
    if(index >= stdHeaps.size()) {
        std::cout << "UNSUCCESSFUL EXTRACTMIN(" << index << ") : SIZE == " << stdHeaps.size() << " <= "
                  << index << " == INDEX" << std::endl;
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

void FunctionalTest::callMeld(int heapNumber, int index1, int index2) {
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
    int heapMin_meld = heaps[heapNumber][index1]->getMin();
    int stdHeapMin_meld = stdHeaps[index1]->getMin();
    EXPECT_EQ(heapMin_meld, stdHeapMin_meld) << "HEAP # " << heapNumber << " HEAPMIN == " << heapMin_meld << " != "
                                             << stdHeapMin_meld << " == STDHEAPMIN AFTER MELDING" << std::endl;
    if(index1 != index2) {
        std::swap(heaps[heapNumber][index2], heaps[heapNumber].back());
        delete heaps[heapNumber].back();
        heaps[heapNumber].pop_back();
        std::swap(stdHeaps[index2], stdHeaps.back());
        delete stdHeaps.back();
        stdHeaps.pop_back();
    }
}

TEST_F(FunctionalTest, test) {
    freopen("tests.txt", "r", stdin);
    std::filebuf timeBuf;
    timeBuf.open("time.txt", std::ios::out);
    std::ostream timeStream(&timeBuf);
    for(int i = 0 ; i < 3; ++i) {
        int test, param1, param2;
        long long begin = clock();
        while(std::cin >> test >> param1 >> param2) {
            callMethod(i, (Method)test, param1, param2);
        }
        long long end = clock();
        timeStream << "Heap # " << i << ": clocks - " << end - begin << " time - " << (end - begin) / CLOCKS_PER_SEC
                   << std::endl;
        stdHeaps.clear();
    }
}

void testGeneration() {
    std::filebuf testBuf;
    testBuf.open("tests.txt", std::ios::out);
    std::ostream testStream(&testBuf);
    int heapsSize = 0;
    for(int i = 1; i <= TESTS; ++i) {
        int test = rand() % TEST_TYPES;
        switch(test) {
            case 0: {
                int addKey = rand() % (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
                testStream << test << ' ' << addKey << ' ' << 0 << std::endl;
                ++heapsSize;
                break;
            }
            case 1: {
                if (heapsSize != 0) {
                    int insertIndex = rand() % heapsSize;
                    int insertKey = rand() % (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
                    testStream << test << ' ' << insertIndex << ' ' << insertKey << std::endl;
                }
                break;
            }
            case 2: {
                if (heapsSize != 0) {
                    int getIndex = rand() % heapsSize;
                    testStream << test << ' ' << getIndex << ' ' << 0 << std::endl;
                }
                break;
            }
            case 3: {
                if (heapsSize != 0) {
                    int extractIndex = rand() % heapsSize;
                    testStream << test << ' ' << extractIndex << ' ' << 0 << std::endl;
                }
                break;
            }
            case 4: {
                if (heapsSize != 0) {
                    int melIndex1 = rand() % heapsSize;
                    int melIndex2 = rand() % heapsSize;
                    testStream << test << ' ' << melIndex1 << ' ' << melIndex2 << std::endl;
                    if (melIndex1 != melIndex2) {
                        --heapsSize;
                    }
                }
                break;
            }
            default:
                testStream << 0 << ' ' << 0 << ' ' << 0 << std::endl;
        }
    }
    testBuf.close();
}

//int main(int argc, char **argv) {
//    srand(time(NULL));
//    testGeneration();
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}

int main() {
    srand(time(NULL));
    BinHeap heap1;
    StandartHeap heap2;
    for(int i = 10; i >= 0; --i) {
        int tmp = rand() % 20;
        heap1.insert(tmp);
        std::cout << tmp << ' ' << heap1.getMin() << std::endl;
    }
    heap1.print();
    for(int i = 10; i >= 0; --i) {
        heap1.extractMin();
        std::cout << heap1.getMin() << std::endl;
    }
//    for(int i = 0; i < 9; ++i) {
//        heap1.extractMin();
//        heap1.print();
//    }
//    for(int i = 0; i < 10; ++i) {
//        heap2.insert(rand() % 20);
//    }
//    heap2.print();
//    heap1.meld(heap2);
//    heap1.print();
}

