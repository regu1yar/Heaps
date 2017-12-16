cmake_minimum_required(VERSION 3.9)
project(IHeap)

set(CMAKE_CXX_STANDARD 11)

include_directories(~/googletest/googletest/include)
link_directories(~/googletest/googletest/cmake-build-debug)
add_executable(IHeap main.cpp IHeap.h BinomialHeap.h LeftistHeap.h SkewHeap.h StandardHeap.h LSHeap.h FunctionalTest.h RandomTests.h)
target_link_libraries(IHeap gtestd)