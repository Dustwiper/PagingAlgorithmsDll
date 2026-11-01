#include <vector>
#include <memory>
#include "paging_algorithm_interface.hpp"
#include "simulation_data.hpp"

/**
 * @brief Алгоритм LRU
 */

namespace paging{

  class LRU : public IAlgorithm{
  public:
    std::vector<std::unique_ptr<SimulationResult>> executeAlgorithm(
                                SimulationData& parameters) override;
  };
}