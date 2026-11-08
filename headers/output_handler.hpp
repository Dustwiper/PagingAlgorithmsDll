#pragma once 

#include "simulation_data.hpp"

/** 
 * @brief Класс, отвечающий за хранение корректных исходных данных
 * и операций вывода результата.
 * 
 * @details Не включается в иходные модули библиотеки. 
 * Используется только при запуске программы как консольного приложения. 
*/

class OHandler{
public:
/**
 * @brief Конструктор класса по умолчанию.
 */
    OHandler() = default;

/** 
 * @brief Функция вывода результата 
 * @param[in] executionResult Массив истории итераций алгоритма.
*/
    void showResult(std::vector<paging::SimulationResult>& executionResult)
     const;
};