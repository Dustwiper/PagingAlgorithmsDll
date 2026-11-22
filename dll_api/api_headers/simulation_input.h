#ifndef SIMULATION_INPUT_H
#define SIMULATION_INPUT_H

#include "stddef.h"

namespace dll_api {

    #ifndef __cplusplus
        typedef struct SimulationInput SimulationInput;
    #endif

    struct SimulationInput{

        const int* initialPages;
        unsigned int initialPagesNumber;

        const int* queryLine;
        unsigned int queryLineLength;

        unsigned int memoryFrames;
    };

    #endif
}