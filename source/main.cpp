#include <iostream>
#include <vector>

#include "simulation_data.hpp"
#include "FIFO.hpp"
#include "LRU.hpp"
#include "output_handler.hpp"
#include "initialization_error.hpp"

int main(){
    
    paging::SimulationData data;
    data.memorySlots = 4;
    data.initialMemoryState = {};
    data.memoryQueue = {
        2, 5, 1, 3, 5, 2, 4, 1, 5, 6,
        2, 4, 5, 1, 7, 3, 5, 2, 6, 1
    };

    paging::FIFO fifo;

    OHandler Omanager;

    auto fifoResult = fifo.runSimulation(data);

    Omanager.showResult(fifoResult);
}   
