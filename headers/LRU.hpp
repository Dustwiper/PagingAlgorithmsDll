#pragma once 

#include <vector>
#include "paging_algorithm.hpp"
#include "simulation_data.hpp"



namespace paging{

  /**
  * @brief Алгоритм LRU
  */

  class LRU : public PagingAlgorithm{
  private:
    std::vector<SimulationResult> executeAlgorithm(
                                const SimulationData& parameters) const override;
  };
}