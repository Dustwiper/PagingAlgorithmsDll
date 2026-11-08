#pragma once

#include <iostream>
#include <memory>
#include "paging_algorithm.hpp"
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
 * @see PagingAlgorithm
 */

namespace paging{

    class FIFO : public PagingAlgorithm{
    private:
        std::vector<SimulationResult> executeAlgorithm(
                                    const SimulationData& parameters) const override;
    };
}