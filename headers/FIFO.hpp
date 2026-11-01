#pragma once

#include <iostream>
#include <memory>
#include "paging_algorithm_interface.hpp"
#include "simulation_data.hpp"

/**
 * @brief 
 * Класс, реализующий модель алгоритма замещения страниц FIFO.
 * 
 * @details 
 * FIFO (First In, First Out) предполагает обработку
 * элементов в порядке их поступления:
 * первый добавленный элемент обрабатывается первым.
 *
 * @see IAlgorithm
 */

namespace paging{

    class FIFO : public IAlgorithm{
    public:
        std::vector<std::unique_ptr<SimulationResult>> executeAlgorithm(
                                    SimulationData& parameters) override;
    };
}