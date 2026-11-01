#include <deque>
#include <algorithm>

#include "LRU.hpp"

namespace paging {
    std::vector<std::unique_ptr<SimulationResult>> LRU::executeAlgorithm(
        SimulationData &parameters){
        
        // Создание модели памяти как двухсторонней очереди.
        std::deque<int> memory;
        // Вставка начального состояния памяти в созданную модель.
        memory.assign(parameters.initialMemoryState.begin(), parameters.initialMemoryState.end());
        
        // Хранилище результатов каждой операции.
        std::vector<std::unique_ptr<SimulationResult>> historyStorage;
        
        // Проход по каждому элемету очереди.
        for(int element : parameters.memoryQueue){

            // Создание структуры, для сохранения информации о каждой итерации.
            std::unique_ptr<SimulationResult> iteraionResult = std::make_unique<SimulationResult>();
            
            // Запись исходного состояния памятию
            iteraionResult->memoryState = memory;
            // Запись следующего входящей страницы.
            iteraionResult->incomingPage = element;

            auto elementItr = std::find(memory.begin(), memory.end(), element);

            /* Если страницы в памяти не оказалось */
            if(elementItr == memory.end()){
                // Запись маркера о страничном прерывании.
                iteraionResult->isPageFault = true;

                // Если пустых слотов не оказалось.
                if(memory.size() == parameters.memorySlots){
                    // Удаление самую редко используемую страницу (находится в начале очереди).
                    memory.erase(memory.begin());
                    // Запись в конец очереди пришедшую страницу.
                    memory.push_back(element);
                } else{
                    // Обычная вставка страницы в конец очереди.
                    memory.push_back(element);
                }
            // Если страница оказалась в памяти.
            } else{
                // Удаление страницы с её текущего местоположения.
                memory.erase(elementItr);
                // Вставка страницы с тем же номером в конец очереди.
                memory.push_back(element);
            }

            // Сохранение результата итераций
            historyStorage.push_back(std::move(iteraionResult));
        }

        std::unique_ptr<SimulationResult> iteraionResult = std::make_unique<SimulationResult>();
        iteraionResult->memoryState = memory;
        historyStorage.push_back(std::move(iteraionResult));

        return historyStorage;
    }
}