#ifndef SIMULATION_OUTPUT_H
#define SIMULATION_OUTPUT_H

#include <stddef.h>

#ifndef __cplusplus
    #include <stdbool.h>

    typedef struct IterationOutput IterationOutput;
    typedef struct SimulationOutput SimulationOutput;
#endif

struct IterationOutput{
    const int* m_currentMemoryState;
    unsigned int m_currentMemorySize;
        
    int m_nextPage;
    bool m_isPageFault;

};


struct SimulationOutput{
    IterationOutput* m_iterationsHistory;
    unsigned int m_iterationsHistoryLength;
};

#endif
