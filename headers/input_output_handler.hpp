#include <memory>

#include "simulation_data.hpp"

/** 
 * @brief Класс, отвечающий за хранение корректных исходных данных
 * и операций вывода результата.
*/

class IOHandler{
public:
/**
 * @brief Конструктор класса по умолчанию.
 */
    IOHandler() = default;

/** 
 * @brief Функция вывода результата 
 * @param[in] executionResult Массив указателей на историю итераций алгоритма.
*/
    void showResult(std::vector<std::unique_ptr<paging::SimulationResult>>& executionResult) const;

/** 
 * @brief Функция валидации и установки исходных данных.
 * @param[in] input Структура входных данных.
 * @throws ExceededMemoryError Если количество страниц в исходном состоянии памяти
 *         превышает количество кадров памяти.
 * @throws ZeroMemorySlotsError Если количество фреймов памяти = 0.
 * @see SimulationData
 * @see InitializationError
*/
    void setInputData(const paging::SimulationData& input);
    
    paging::SimulationData getInputData() const;

private:
/**
 * @brief Структура входных данных
 */
    std::unique_ptr<paging::SimulationData> m_inputData;
};