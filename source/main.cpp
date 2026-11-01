#include <iostream>
#include <vector>

#include "simulation_data.hpp"
#include "context.hpp"
#include "FIFO.hpp"
#include "LRU.hpp"
#include "input_output_handler.hpp"
#include "initialization_error.hpp"

int main(){

    std::unique_ptr<paging::IAlgorithm> fifo_uptr = std::make_unique<paging::FIFO>();
    std::unique_ptr<paging::IAlgorithm> lru_uptr = std::make_unique<paging::LRU>();
    
    paging::SimulationData data;
    data.memorySlots = 4;
    data.initialMemoryState = {};
    data.memoryQueue = {
        2, 5, 1, 3, 5, 2, 4, 1, 5, 6,
        2, 4, 5, 1, 7, 3, 5, 2, 6, 1
    };

    std::unique_ptr<paging::SimulationData> algorithmParameters = 
        std::make_unique<paging::SimulationData>(data);

    paging::Context contextFifo(std::move(fifo_uptr));
    paging::Context contextLru(std::move(lru_uptr));

    IOHandler IOmanager;
    
    // Проверка входных данных на коректность, прежде чем передать их в исполнение алгоритмам.
    try{
        IOmanager.setInputData(data);
    } catch (const ExceededMemoryError& e){
        std::cerr << e.what() << std::endl;
        exit(1);
    }catch (const ZeroMemorySlotsError& e){
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    paging::SimulationData validData {IOmanager.getInputData()};

    auto lruResult = contextLru.runAlgorithm(validData);
    auto fifoResult = contextFifo.runAlgorithm(validData);

    IOmanager.showResult(lruResult);

}   
