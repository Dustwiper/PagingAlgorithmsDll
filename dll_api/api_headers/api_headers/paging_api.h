#ifndef PAGING_API_H
#define PAGING_API_H

#include "simulation_input.h"
#include "simulation_output.h"
#include "paging_export.h"

/* Совместимость для компиляторов С++ и С */

#ifdef __cplusplus
    extern"C"{
#endif

PAGING_API int runFifo(const SimulationInput* inputData, SimulationOutput** result);

PAGING_API int runLRU(const SimulationInput* inputData, SimulationOutput** result);

PAGING_API void freeSimulationOutput(SimulationOutput* result);

#ifdef __cplusplus
    }
#endif


#endif