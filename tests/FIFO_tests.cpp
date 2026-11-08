#include <algorithm>
#include <deque>
#include <vector>

#include "gtest/gtest.h"
#include "FIFO.hpp"

namespace {

using paging::FIFO;
using paging::SimulationData;
using paging::SimulationResult;

TEST(FIFOTest, RecordsStateBeforeEachRequestAndEvictsInArrivalOrder) {
    FIFO fifo;
    SimulationData input;
    input.memorySlots = 3;
    input.memoryQueue = {1, 2, 3, 1, 4};

    const std::vector<SimulationResult> history = fifo.runSimulation(input);

    ASSERT_EQ(history.size(), input.memoryQueue.size() + 1);
    EXPECT_EQ(history[0].memoryState, (std::deque<int>{}));
    EXPECT_EQ(history[1].memoryState, (std::deque<int>{1}));
    EXPECT_EQ(history[2].memoryState, (std::deque<int>{1, 2}));
    EXPECT_EQ(history[3].memoryState, (std::deque<int>{1, 2, 3}));
    EXPECT_EQ(history[4].memoryState, (std::deque<int>{1, 2, 3}));
    EXPECT_EQ(history.back().memoryState, (std::deque<int>{4, 2, 3}));

    EXPECT_TRUE(history[0].isPageFault);
    EXPECT_TRUE(history[1].isPageFault);
    EXPECT_TRUE(history[2].isPageFault);
    EXPECT_FALSE(history[3].isPageFault);
    EXPECT_TRUE(history[4].isPageFault);
    EXPECT_EQ(
        std::count_if(history.begin(), history.end(), [](const SimulationResult& step) {
            return step.isPageFault;
        }),
        4);
}

TEST(FIFOTest, EmptyRequestQueuePreservesInitialMemory) {
    FIFO fifo;
    SimulationData input;
    input.initialMemoryState = {7, 8};
    input.memorySlots = 3;

    const std::vector<SimulationResult> history = fifo.runSimulation(input);

    ASSERT_EQ(history.size(), 1);
    EXPECT_EQ(history.front().memoryState, (std::deque<int>{7, 8}));
    EXPECT_FALSE(history.front().isPageFault);
}

}  // namespace
