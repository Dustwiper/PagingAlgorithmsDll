#include <vector>
#include <iostream>
#include "paging_api.h"

using namespace dll_api;

PAGING_API int runFifo(const SimulationInput* inputData, SimulationOutput** result){

    if (inputData == nullptr){
        //Throwing an error
    }

    if(result == nullptr){
        // Throwing an error
    }

    if (inputData->initialPagesNumber > 0){

        if (inputData->initialPages == nullptr){
            // Throwing an error
        }
    }

    if(inputData->queryLineLength > 0){
        if(inputData->queryLine == nullptr){
            // Throwing an error
        }
    }

    // Количество исходных страниц в памяти
    unsigned int initPagesQuantity = inputData->initialPagesNumber;

    std::vector<int> initialMemoryVector(inputData->initialPages, 
                                         inputData->initialPages + initPagesQuantity);

    // Количество элементов очереди
    unsigned int queryLength = inputData->queryLineLength;

    std::vector<int> pageQuerryVector(inputData->queryLine,
                                      inputData->queryLine + queryLength);

}
