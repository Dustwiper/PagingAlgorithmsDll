#include <vector>
#include <limits>
#include <stdexcept>

#include "paging_api.h"
#include "simulation_data.hpp"
#include "FIFO.hpp"
#include "LRU.hpp"
#include "simulation_limits.h"

// Anonymous namespace 

namespace {

    // Проверка нулевых указателей и пустых полей, переданных от клиента
    PagingStatus validateInput(const SimulationInput* inputData){
    
        if (inputData == nullptr){
            return PAGING_NULL_POINTER;
        }

        if (inputData->m_initialPagesNumber > inputData->m_memoryFrames){
            return PAGING_EXCEEDED_MEMORY;
        }

        if (inputData->m_initialPagesNumber > 0){

            if (inputData->m_initialPages == nullptr){
                return PAGING_NULL_POINTER;
            }
        }

        if (inputData->m_memoryFrames == 0) {
            return PAGING_ZERO_MEMORY_FRAMES;
        }


        if(inputData->m_memoryFrames > paging::limits::MAX_MEMORY_FRAMES){
            return PAGING_MEMORY_LIMIT_EXCEEDED;
        }

        if(inputData->m_queryLineLength > paging::limits::MAX_QUERY_LENGTH){
            return PAGING_QUERY_LIMIT_EXCEEDED;
        }

        if(inputData->m_queryLineLength > 0){

            if(inputData->m_queryLine == nullptr){
                return PAGING_NULL_POINTER;
            }
        }   

        return PAGING_SUCCESS;
    } 

    /* Преобразование входных данных из С-структуры в структуру С++. 
        ! Вызывать только после выполенния validateInpt.
    */
    paging::SimulationData convertData(const SimulationInput& inputData){

    paging::SimulationData initialData;

    if(inputData.m_initialPagesNumber > 0){

    initialData.initialMemoryState.assign(inputData.m_initialPages,
                                          inputData.m_initialPages + inputData.m_initialPagesNumber); 

    }

    if(inputData.m_queryLineLength > 0){
        initialData.memoryQueue.assign(inputData.m_queryLine, 
                                       inputData.m_queryLine + inputData.m_queryLineLength);
    }

    initialData.memorySlots = inputData.m_memoryFrames;

    return initialData;
    }


    SimulationOutput* convertOutput(
        const std::vector<paging::SimulationResult>& history
    ) {
        // Автоматическое освобождение памяти при исключениях
        std::unique_ptr<
            SimulationOutput,
            decltype(&freeSimulationOutput)
        > result(new SimulationOutput{}, &freeSimulationOutput);

        // Обработка пустой истории
        if (history.empty()) {
            return result.release();
        }

        // Создание массива структур итераций
        IterationOutput* iterHistory =
            new IterationOutput[history.size()]{};

        result->m_iterationsHistory = iterHistory;
        result->m_iterationsHistoryLength = history.size();

        // Преобразование каждой итерации
        for (std::size_t i = 0; i < history.size(); ++i) {
            const auto& memoryState = history[i].memoryState;
            auto& iteration = iterHistory[i];

            // Проверка вместимости поля размера
            if (memoryState.size() >
                std::numeric_limits<
                    decltype(iteration.m_currentMemorySize)
                >::max()) {
                throw std::length_error("Memory state size overflow");
            }

            iteration.m_currentMemorySize =
                static_cast<decltype(iteration.m_currentMemorySize)>(
                    memoryState.size()
                );

            iteration.m_isPageFault = history[i].isPageFault;
            iteration.m_nextPage = history[i].incomingPage;

            // Пустое состояние памяти не требует выделения массива
            if (memoryState.empty()) {
                continue;
            }

            // Выделение памяти для копии состояния памяти
            int* pages = new int[memoryState.size()];

            // Сразу сохраняем указатель для корректного освобождения
            iteration.m_currentMemoryState = pages;

            // Копирование элементов deque в обычный массив
            std::copy(
                memoryState.begin(),
                memoryState.end(),
                pages
            );
        }

        // Передаём владение вызывающему коду
        return result.release();
    }  
}

// Реализация публичных функций

/* Реализация функции освобождения памяти для всей структуры выходных данных*/
PAGING_API void freeSimulationOutput(SimulationOutput* result){
    if (result == nullptr){
        return;
    }

    for(size_t i = 0; i < result->m_iterationsHistoryLength; ++i){

        // Освобождение памяти каждой итерации
        delete[] result->m_iterationsHistory[i].m_currentMemoryState;
    }

    // Освобождение основного массива
    delete[] result->m_iterationsHistory;

    delete result;
}

/* Вызов функции для алгоритма fifo из ядра библиотеки и обработка результата*/
PAGING_API int runFifo(const SimulationInput* inputData, SimulationOutput** result){
    if(result == nullptr){
        return PAGING_NULL_POINTER;
    }

    *result = nullptr;


    PagingStatus status = validateInput(inputData);
   if (status != PAGING_SUCCESS){
        return status;
    }

    paging::SimulationData data = convertData(*inputData);

    paging::FIFO fifo;

    std::vector<paging::SimulationResult> history = fifo.runSimulation(data);

    *result = convertOutput(history);

    return PAGING_SUCCESS;
}

