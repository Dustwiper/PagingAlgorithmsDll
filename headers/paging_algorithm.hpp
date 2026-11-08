#pragma once

#include <memory>
#include <vector>
#include "simulation_data.hpp"

namespace paging{

    /**
     * @brief Абстрактный базовый класс, служащий интерфейсом реализации алгоритмов.
     * 
     * @details Класс организован на основе шаблонного метода. 
    */

    class PagingAlgorithm{
    public:
        /**
         * @brief Основная функция выполнения алгоритма.
         * @param[in] parameters Ссылка на структуру исходных данных для алгоритма.
         * @return Возвращает вектор  структур, описывающие каждую итерацию алгоритма. 
         * @see Context
         * @see SimulationData
         * @see SimulationResult
         */

        /** 
         * @brief Шаблонный метод класса.
         * 
         * @details Шаблонный метод позволяетя составить общую для всех наследников 
         * последовательность выполнения открытыми невиртуальными функциями, 
         * не подлежащих переопределению. В то же время класс позволяет переопределить методы, 
         * необходимые для собственной реализации.
         */
        std::vector<SimulationResult> runSimulation(const SimulationData& inputData) const;

        virtual ~PagingAlgorithm() = default;

    private: 

    /**
     * @brief Выполняет моделирование алгоритма замещения страниц.
     *
     * @details Абстрактный метод, реализуемый конкретными алгоритмами
     * замещения страниц (FIFO, LRU).
     *
     * @param[in] parameters Входные данные симуляции.
     *
     * @pre parameters.initialMemoryState не содержит повторяющихся страниц.
     * @pre parameters.memorySlots > 0.
     * @pre parameters.initialMemoryState.size() <= parameters.memorySlots.
     *
     * @return История выполнения алгоритма, содержащая состояния
     * памяти и информацию о страничных прерываниях.
     */

        virtual std::vector<SimulationResult> executeAlgorithm(
            const SimulationData& parameters) const = 0;
        
        /** 
         * @brief Функция проверки исходных данных на соответсвие pre-условиям.
         * @throws ZeroMemorySlotsError Если число кадров памяти равно нулю.
         * @throws ExceededMemoryError Если начальное состояние
         * превышает вместимость памяти.
         * @throws DuplicatesError Если исходном контейнере начальных страниц есть дубликаты
         */
        virtual void validateData(const SimulationData& iputData) const;
            
    };


} // namespace paging