#include <deque>
#include <vector>

#include "gtest/gtest.h"
#include "LRU.hpp"

namespace {

using paging::LRU;
using paging::SimulationData;
using paging::SimulationResult;

TEST(LRUTest, AHitMakesThePageMostRecentlyUsed) {
    LRU lru;
    SimulationData input;
    input.memorySlots = 3;
    input.memoryQueue = {1, 2, 3, 1, 4};

    const std::vector<SimulationResult> history = lru.runSimulation(input);

    ASSERT_EQ(history.size(), input.memoryQueue.size() + 1);
    EXPECT_EQ(history[0].memoryState, (std::deque<int>{}));
    EXPECT_EQ(history[1].memoryState, (std::deque<int>{1}));
    EXPECT_EQ(history[2].memoryState, (std::deque<int>{1, 2}));
    EXPECT_EQ(history[3].memoryState, (std::deque<int>{1, 2, 3}));
    EXPECT_EQ(history[4].memoryState, (std::deque<int>{2, 3, 1}));
    EXPECT_EQ(history.back().memoryState, (std::deque<int>{3, 1, 4}));

    EXPECT_TRUE(history[0].isPageFault);
    EXPECT_TRUE(history[1].isPageFault);
    EXPECT_TRUE(history[2].isPageFault);
    EXPECT_FALSE(history[3].isPageFault);
    EXPECT_TRUE(history[4].isPageFault);
}

TEST(LRUTest, AHitChangesWhichPageIsEvicted) {
    LRU lru;
    SimulationData input;
    input.memorySlots = 2;
    input.memoryQueue = {1, 2, 1, 3};

    const std::vector<SimulationResult> history = lru.runSimulation(input);

    ASSERT_EQ(history.size(), input.memoryQueue.size() + 1);
    EXPECT_EQ(history[3].memoryState, (std::deque<int>{2, 1}));
    EXPECT_FALSE(history[2].isPageFault);
    EXPECT_TRUE(history[3].isPageFault);
    EXPECT_EQ(history.back().memoryState, (std::deque<int>{1, 3}));
}

TEST(LRUTest, EmptyRequestQueuePreservesInitialMemory) {
    LRU lru;
    SimulationData input;
    input.initialMemoryState = {7, 8};
    input.memorySlots = 3;

    const std::vector<SimulationResult> history = lru.runSimulation(input);

    ASSERT_EQ(history.size(), 1);
    EXPECT_EQ(history.front().memoryState, (std::deque<int>{7, 8}));
    EXPECT_FALSE(history.front().isPageFault);
}

}  // namespace
