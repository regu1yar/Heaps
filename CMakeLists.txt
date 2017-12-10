cmake_minimum_required(VERSION 3.9)
project(IHeap)

set(CMAKE_CXX_STANDARD 11)

include_directories(~/googletest/googletest/include)
link_directories(~/googletest/googletest/cmake-build-debug)
add_executable(IHeap main.cpp IHeap.h BinTree.cpp BinTree.h BinHeap.cpp BinHeap.h LeftHeap.cpp LeftHeap.h LeftistNode.cpp LeftistNode.h SkewHeap.cpp SkewHeap.h SkewNode.cpp SkewNode.h StandartHeap.cpp StandartHeap.h)
target_link_libraries(IHeap gtestd)