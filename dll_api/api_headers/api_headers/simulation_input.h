#ifndef SIMULATION_INPUT_H
#define SIMULATION_INPUT_H

#include "stddef.h"

#ifndef __cplusplus
    typedef struct SimulationInput SimulationInput;
#endif

struct SimulationInput{

    const int* initialPages;
    size_t initialPagesNumber;

    const int* queryLine;
    size_t queryLineLength;

    size_t memoryFrames;
};

#endif
