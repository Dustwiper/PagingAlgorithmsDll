#pragma once

#include <memory>
#include <vector>

#include "paging_algorithm_interface.hpp"
#include "simulation_data.hpp"
#include "FIFO.hpp"
#include "API.hpp"

/** 
 * @brief Класс, агрегирующий IAlgorithm.
 * 
 * @details 
 * Context хранит ссылку на объект типа IAlgorithm и реализует
 * доступ к методам производных от IAlgorthm типов.
 * @see SimulationData
*/

namespace paging{

    class PAGING_API Context{
    private:
        std::unique_ptr<paging::IAlgorithm> m_policy;

    public:
    /**
     * @brief Конструктор принимает данные, необходимые для стратегии.
     * 
     * @param[in] policy Указатель на алгоритм (стратегию / политику).
     *  */    
        Context(std::unique_ptr<paging::IAlgorithm> policy) : m_policy(std::move(policy))
        {}
    /**
     * @brief Функция, инкапсулирующая выполнение алгоритма. 
     * @details Так же как и метод класса IAlgorithm принимает исходные данные для алгоритма
     * и возвращает результат обработки.
     * 
     * @param[in] parameters Ссылка на структуру исходных данных
     * @return Вектор указателей на созданные в процессе выполнения алгоритма структуры,
     * содержащие историю выполнения на каждом шаге.
     *  */  

        std::vector<std::unique_ptr<SimulationResult>> runAlgorithm(
            SimulationData& parameters){

            return m_policy->executeAlgorithm(parameters);   
        }

        ~Context() = default;
    };

}