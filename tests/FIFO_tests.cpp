// #include "gtest/gtest.h"
// #include "FIFO.hpp"
// #include "utilities.hpp"

// /**Command to run tests:
//  * cmake --build build --target dll_tests && ctest --test-dir build --output-on-failure  
// */

// using namespace paging;

// //** Подготовка к тесту №1*/
// class FifoTest : public::testing::Test{
// protected:
//     FIFO fifo;
//     // Входные данные 
//     SimulationData inputData; 
//     // Результат
//     std::vector<std::unique_ptr<SimulationResult>> result; 
//     // Последняя запись в векторе, через которую можно посмотреть конечное состояние памяти
//     SimulationResult finalResult; 
//     // Действительное количество прерываний 
//     int actualPageFaults;

//     void SetUp() override{
//         // Входная очередь
//         inputData.memoryQueue = {
//         3, 5, 2, 7, 1, 4, 2, 6, 3, 1,
//         5, 7, 3, 2, 4, 1, 6, 2, 3, 5
//         };
//         // Количество слотов памяти 
//         inputData.memorySlots = 5;
//         // Результат в виде вектора структур
//         result = fifo.executeAlgorithm(inputData);
//         // Самая последняя запись в векторе
//         finalResult = *(result.back().get());

//         actualPageFaults = countPageFaults(result);
//     }


// };

// // ТЕСТ №1 - Все блоки памяти изначально пустые 
// TEST_F(FifoTest, InitialEmplySlots){

//     finalResult = *(result.back().get());

//     // Ожидаемое состояние памяти
//     std::deque<int> expectedFinalMemoryState{5, 4, 1, 6, 3};

//     // Ожидаемое количество страничных прерываний
//     int expectedPageFaults{16};

//     // Сравнение состояний памяти
//     EXPECT_EQ(
//         expectedFinalMemoryState,
//         finalResult.memoryState);

//     // Сравнение количества страничных прерываний
//     EXPECT_EQ(
//         expectedPageFaults,
//         actualPageFaults);
// }

// // Тест №2


// //** Подготовка к тесту на аномалию Белади */
// class BeladiTest : public::testing::Test{
// protected:
//     FIFO fifo;
//     SimulationData inputDataFirst; 
//     SimulationData inputDataSecond; 
//     // Действительное количество прерываний 
//     int actualPageFaultsFirst;
//     int actualPageFaultsSecond;

//     // Количество блоков памяти при первом и втором прогонеы

//     void SetUp() override{
//         inputDataFirst.memoryQueue = {5, 4, 3, 2, 5, 4, 1, 5, 4, 3, 2, 1};
//         inputDataSecond.memoryQueue = {5, 4, 3, 2, 5, 4, 1, 5, 4, 3, 2, 1};
        
//         inputDataFirst.memorySlots = 3;
//         inputDataSecond.memorySlots = 4;

//     }
// };

// TEST_F(BeladiTest, BeladiAnomalyTest){

//     // Первый запуск с 3 блоками памяти
//     std::vector<std::unique_ptr<SimulationResult>> threeSlotsRun{
//         fifo.executeAlgorithm(inputDataFirst)};

//     SimulationResult threeSlotsResult = *(threeSlotsRun.back().get());
//     int threeSlotsPageFaults = countPageFaults(threeSlotsRun);

//     // Второй запуск с 4 блоками памяти 
//     std::vector<std::unique_ptr<SimulationResult>> fourSlotsRun{
//     fifo.executeAlgorithm(inputDataSecond)};

//     SimulationResult fourSlotsResult = *(fourSlotsRun.back().get());
//     int fourSlotsPageFaults = countPageFaults (fourSlotsRun);

//     std::deque<int> expectedThreeSlotsResult {1, 3, 2};
//     std::deque<int> expectedFourSlotsResult {2, 1, 4, 3};

//     // Сравнение результатов для запуска с 3 ячейками памяти
//     EXPECT_EQ(
//         threeSlotsResult.memoryState,
//         expectedThreeSlotsResult
//     );

//     EXPECT_EQ(
//         threeSlotsPageFaults,
//         9
//     );
    
//     // Сравнение результатов для запуска с 3 ячейками памяти
//         EXPECT_EQ(
//         fourSlotsResult.memoryState,
//         expectedFourSlotsResult
//     );

//     EXPECT_EQ(
//         fourSlotsPageFaults,
//         10
//     );

// }

