//
// Created by Роман Климовицкий on 16.12.2017.
//

#ifndef IHEAP_FUNCTIONALTEST_H
#define IHEAP_FUNCTIONALTEST_H


#include <iostream>
#include <vector>
#include <fstream>
#include "BinomialHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include "StandartHeap.h"
#include "gtest/gtest.h"
#include <time.h>

static int HEAP_TYPES = 3;
static int TEST_TYPES = 5;
static int MIN_KEY = -1000;
static int MAX_KEY = 1000;
static int INSERTS_TESTS = 10000;
static int INSERT_TEST_SHIFT = 100;
static int EXTRACT_TESTS = 1000;
static int EXTRACT_TESTS_SHIFT = 10;

class FunctionalTest : public ::testing::Test {
protected:
    BinomialHeap binomialHeap;
    LeftistHeap leftistHeap;
    SkewHeap skewHeap;
    StandartHeap stdHeap;

    void SetUp() {
        std::cout << "SET UP" << std::endl;
    }

    void TearDown() {
        binomialHeap.clear();
        leftistHeap.clear();
        skewHeap.clear();
        stdHeap.clear();
        std::cout << "TEARED DOWN" << std::endl;
    }
};

TEST_F(FunctionalTest, InsertTest) {
    for(size_t i = INSERTS_TESTS / INSERT_TEST_SHIFT; i <= INSERTS_TESTS; i += INSERTS_TESTS / INSERT_TEST_SHIFT) {
        for(size_t j = 0; j < i; ++j) {
            int key = rand() % (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
            binomialHeap.insert(key);
            leftistHeap.insert(key);
            skewHeap.insert(key);
            stdHeap.insert(key);
            EXPECT_EQ(binomialHeap.getMin(), stdHeap.getMin()) << "BAD INSERT ON BINOMIAL HEAP" << std::endl;
            EXPECT_EQ(leftistHeap.getMin(), stdHeap.getMin()) << "BAD INSERT ON LEFTIST HEAP" << std::endl;
            EXPECT_EQ(skewHeap.getMin(), stdHeap.getMin()) << "BAD INSERT ON SKEW HEAP" << std::endl;
        }
        binomialHeap.clear();
        leftistHeap.clear();
        skewHeap.clear();
        stdHeap.clear();
        std::cout << "INSERT TEST " << i / (INSERTS_TESTS / INSERT_TEST_SHIFT) << " PASSED" << std::endl;
    }
}

TEST_F(FunctionalTest, ExtractMinTest) {
    for(size_t i = EXTRACT_TESTS / EXTRACT_TESTS_SHIFT; i <= EXTRACT_TESTS; i += EXTRACT_TESTS / EXTRACT_TESTS_SHIFT) {
        for(size_t j = 0; j < i; ++j) {
            int key = rand() % (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
            binomialHeap.insert(key);
            leftistHeap.insert(key);
            skewHeap.insert(key);
            stdHeap.insert(key);
        }
        while(!stdHeap.empty()) {
            binomialHeap.extractMin();
            leftistHeap.extractMin();
            skewHeap.extractMin();
            stdHeap.extractMin();
            if(!stdHeap.empty()) {
                EXPECT_EQ(binomialHeap.getMin(), stdHeap.getMin()) << "BAD EXTRACTMIN ON BINOMIAL HEAP" << std::endl;
                EXPECT_EQ(leftistHeap.getMin(), stdHeap.getMin()) << "BAD EXTRACTMIN ON LEFTIST HEAP" << std::endl;
                EXPECT_EQ(skewHeap.getMin(), stdHeap.getMin()) << "BAD EXTRACTMIN ON SKEW HEAP" << std::endl;
            }
        }
        binomialHeap.clear();
        leftistHeap.clear();
        skewHeap.clear();
        stdHeap.clear();
        std::cout << "EXTRACT TEST " << i / (EXTRACT_TESTS / EXTRACT_TESTS_SHIFT) << " PASSED" << std::endl;
    }
}


#endif //IHEAP_FUNCTIONALTEST_H
