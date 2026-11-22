#ifndef SIMULATION_OUTPUT_H
#define SIMULATION_OUTPUT_H

#include <stddef.h>

namespace dll_api{
    #ifndef __cplusplus
        #include <stdbool.h>

        typedef struct IterationOutput IterationOutput;
        typedef struct SimulationOutput SimulationOutput;
    #endif

    struct IterationOutput{
        const int* currentMemoryState;
        unsigned int currentMemorySize;
        
        int nextPage;
        bool isPageFault;

    };


    struct SimulationOutput{
        IterationOutput* iterationsHistory;
        size_t iterationsHistoryLength;
    };

    #endif
}