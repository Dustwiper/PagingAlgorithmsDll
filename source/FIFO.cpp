#include <algorithm>
#include <deque>
#include <iostream>

#include "FIFO.hpp"
#include "simulation_data.hpp"

namespace paging {

    std::vector<std::unique_ptr<SimulationResult>> FIFO::executeAlgorithm(SimulationData& parameters){

        // Моделирование состояния памяти как двусторонней очереди.
        std::deque<int> memory;
        // Индекс страницы, следующей на замещение.
        size_t pageToRemoveIndex{0};

        // Вставка изначально присутствующих элементов в памяти.
        memory.assign(parameters.initialMemoryState.begin(), parameters.initialMemoryState.end());

        // Создание вектора результатов
        std::vector<std::unique_ptr<SimulationResult>> historyStorage;

        // Итерация по каждому элементу в очереди.
        for(auto page : parameters.memoryQueue){

            std::unique_ptr<SimulationResult> iteraionResult = std::make_unique<SimulationResult>();
            iteraionResult->memoryState = memory;

            iteraionResult->incomingPage = page;

            // Проверка присутствия страницы из очереди в памяти
            auto pageIter = std::find(memory.begin(), memory.end(), page);
            
            // Если странцы в памяти не оказалось
            if (pageIter == memory.end()){

                // Установка маркера страничного прерывания.
                iteraionResult->isPageFault = true;
                    // Если свободного места не оказалось.
                    if(memory.size() == parameters.memorySlots){
                    // Замена страницы по индексу
                    memory[pageToRemoveIndex] = page;
                    // Обновление индекса следующей на замещение страницы.
                    pageToRemoveIndex = (pageToRemoveIndex + 1) % parameters.memorySlots;

                } else{
                    memory.push_back(page);
                }
            }
            historyStorage.push_back(std::move(iteraionResult));
        }
        // Запись финального состояния памяти.
        std::unique_ptr<SimulationResult> iteraionResult = std::make_unique<SimulationResult>();
        iteraionResult->memoryState = memory;
        historyStorage.push_back(std::move(iteraionResult));

        return historyStorage;
    }
}
