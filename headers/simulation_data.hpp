#pragma once

#include <vector>
#include <deque>

namespace paging{

    /**
     * @brief Структура, содержащая исходные данные для работы алгоритма. 
     * @details Содержит необхдимые пользовательские параметры для корректного моделирования
     * алгоритмов замещения страниц.   
     *  */ 

    struct SimulationData{
        std::vector<int> initialMemoryState; ///< Массив, описывающий начальное состояние памяти.
        std::vector<int> memoryQueue; ///< Очередь запрашиваемых страниц.
        size_t memorySlots{0}; ///< Количество свободных слотов в памяти.
    };

    /** @brief Структура, содержащая результат обработки очереди, а так же состояние памяти 
     * на одном шаге выполнения алгоритма.
    */

    struct SimulationResult{
        std::deque<int> memoryState; ///< Состояние памяти перед обращением.
        int incomingPage{}; ///< Номер следующей на вход страицы.
        bool isPageFault{false}; ///< Признак страничного прерывания.
    };

}

