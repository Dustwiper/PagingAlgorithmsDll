#pragma once

#include <vector>
#include "simulation_data.hpp"
/**
 * @brief Абстрактный базовый класс, служащий интерфейсом реализации алгоритмов.
 */

namespace paging{

    class IAlgorithm{
    public:
        /**
         * @brief Основная функция выполнения алгоритма.
         * @param[in] parameters Ссылка на структуру исходных данных для алгоритма.
         * @return Возвращает вектор указателей на структуры, описыващие каждый из итераций алгоритма. 
         * @see Context
         * @see SimulationData
         * @see SimulationResult
         */
        
        virtual std::vector<std::unique_ptr<SimulationResult>> executeAlgorithm(
            SimulationData& parametes) = 0;

    public:
        virtual ~IAlgorithm() = default;
    };

} // namespace paging