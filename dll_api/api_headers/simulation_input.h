#ifndef SIMULATION_INPUT_H
#define SIMULATION_INPUT_H

#include "stddef.h"


#ifndef __cplusplus
    typedef struct SimulationInput SimulationInput;
#endif

struct SimulationInput{

    const int* m_initialPages;
    unsigned int m_initialPagesNumber;

    const int* m_queryLine;
    unsigned int m_queryLineLength;

    unsigned int m_memoryFrames;
};

#endif