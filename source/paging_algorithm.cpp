#include <iostream>
#include <unordered_set>

#include "paging_algorithm.hpp"
#include "initialization_error.hpp"

namespace {
    // Поиск дублирующих номеров страниц
    bool findDuplicates(const std::vector<int>& initialPages){
        std::unordered_set<int> seen;

        for (const int& x : initialPages){
            if(!seen.insert(x).second){
                return true;
            }
        }

        return false;
    }
}

namespace paging{

    std::vector<SimulationResult> PagingAlgorithm::runSimulation(const SimulationData& inputData) const {
        try{
            validateData(inputData);
        } catch (const ExceededMemoryError& e){
            std::cerr << e.what() << std::endl;
            exit(1);
        }catch (const ZeroMemorySlotsError& e){
            std::cerr << e.what() << std::endl;
            exit(1);
        }catch (const DuplicatesError& e){
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        
        return executeAlgorithm(inputData);
    }

    void PagingAlgorithm::validateData(const SimulationData& inputData) const {

        if(inputData.initialMemoryState.size() > inputData.memorySlots){
            throw ExceededMemoryError("Quantity of initial pages can't be more then memory slots!");
        }

        if(inputData.memorySlots == 0){
            throw ZeroMemorySlotsError("Memory must have at least one frame!");
        }

        if(findDuplicates(inputData.initialMemoryState)){
            throw DuplicatesError("Initial memory must contain only unique page numbers!");
        }

    }

}