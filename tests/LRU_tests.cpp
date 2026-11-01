#include "gtest/gtest.h"
#include "LRU.hpp"
#include "utilities.hpp"

/**Command to run tests:
 * cmake --build build --target dll_tests && ctest --test-dir build --output-on-failure  
*/

using namespace paging;

class LruTest : public::testing::Test{
protected:
    LRU lru;
    // Входные данные 
    SimulationData inputData; 
    // Результат
    std::vector<std::unique_ptr<SimulationResult>> result; 
    // Последняя запись в векторе, через которую можно посмотреть конечное состояние памяти
    SimulationResult finalResult; 
    // Действительное количество прерываний 
    int actualPageFaults;

    void SetUp() override{
        // Входная очередь
        inputData.memoryQueue = {
            3, 7, 1, 5, 7, 1, 3
        };
        // Количество слотов памяти 
        inputData.memorySlots = 5;
        // Результат в виде вектора структур
        result = lru.executeAlgorithm(inputData);
        // Самая последняя запись в векторе
        finalResult = *(result.back().get());

        actualPageFaults = countPageFaults(result);
    }

};

TEST_F(LruTest, EmptyMemoryTest){

    finalResult = *(result.back().get());

    // Ожидаемое состояние памяти
    std::deque<int> expectedFinalMemoryState{5, 7, 1, 3};

    // Ожидаемое количество страничных прерываний
    int expectedPageFaults{4};

    // Сравнение состояний памяти
    EXPECT_EQ(
        expectedFinalMemoryState,
        finalResult.memoryState);

    // Сравнение количества страничных прерываний
    EXPECT_EQ(
        expectedPageFaults,
        actualPageFaults);
}

TEST(LRU, RecentlyLoadedButNotUsedTest){

    LRU lru;
    std::deque<int> expectedFinalMemoryState{2, 4, 3};
    int expectedPageFaults{5};

    SimulationData input;

    input.memoryQueue = {1, 2, 3, 1, 2, 4, 3};
    input.memorySlots = 3;

    auto result = lru.executeAlgorithm(input);
    auto finalResult = *(result.back().get());

    int actualPageFaults{countPageFaults(result)};


    EXPECT_EQ(
        expectedFinalMemoryState,
        finalResult.memoryState
    );

    EXPECT_EQ(
        actualPageFaults,
        expectedPageFaults
    );

    EXPECT_EQ(
        (std::deque<int>{3, 1, 2}),
        result[5]->memoryState
    );
}

TEST(LRU, SingleMemoryFrame){

    LRU lru;

    SimulationData data;
    data.memorySlots = 1;
    data.initialMemoryState = {};
    data.memoryQueue = {3, 3, 5, 5, 3, 7, 7, 3};

    auto result = lru.executeAlgorithm(data);
    auto finalResult = *(result.back().get());

    int actualPageFaults{countPageFaults(result)};

    EXPECT_EQ(
        finalResult.memoryState,
        (std::deque<int>{3})
    );

    EXPECT_EQ(
        actualPageFaults,
        5
    );
}

TEST(LRU, EmptyInputQueue){

    LRU lru;

    SimulationData data;
    data.memorySlots = 4;
    data.initialMemoryState = {1, 2};
    data.memoryQueue = {};

     auto result = lru.executeAlgorithm(data);
    auto finalResult = *(result.back().get());

    int actualPageFaults{countPageFaults(result)};

    EXPECT_EQ(
        finalResult.memoryState,
        (std::deque<int>{1, 2})
    );

    EXPECT_EQ(
        actualPageFaults,
        0
    );

}