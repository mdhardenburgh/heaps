#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>

#include "heap.h"
//cmake -S . -B build
//cmake --build build --target transmitterTb
//cmake --build build

TEST(heapTest, test_instsiate_max_heap)
{
    std::string maxString;
    std::vector<std::tuple<std::string, uint32_t>> inputVector = 
    {
        {"maybe", 3},
        {"this", 0},
        {"is", 1},
        {"a", 2},
        {"test", 4}
    };
    maxHeap<std::string> myHeap(inputVector);
    maxString = myHeap.heapMaximum();
    std::cout<<"maxString: "<<maxString<<std::endl;
}