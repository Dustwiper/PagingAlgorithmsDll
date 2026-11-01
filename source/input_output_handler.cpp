#include <iostream>
#include "input_output_handler.hpp"
#include "initialization_error.hpp"

template <typename T>
void print(const T& container){
    for(auto i : container){
        std::cout << i << " ";
    }

    std::cout << '\n';
}

void IOHandler::showResult(std::vector<std::unique_ptr<paging::SimulationResult>>& executionResult) const{
    int nPageFaults{0};

    for(auto i = executionResult.begin(); i < executionResult.end()-1; ++i){
        if((*i)->isPageFault) {nPageFaults += 1;}


        std::cout << "Next page: " << (*i)->incomingPage;
        std::cout << " Page fault: " << ((*i)->isPageFault ? "Yes|" : "No |");  

        std::cout << " Memory: ";
        print((*i)->memoryState);
    }

    std::cout << "Final Memory Status: "; 
    print(executionResult.back()->memoryState);
    std::cout << "Page Faults: " << nPageFaults << std::endl; 

}

paging::SimulationData IOHandler::getInputData() const {
    return *(m_inputData.get());
}


void IOHandler::setInputData(const paging::SimulationData& input){
    if(input.initialMemoryState.size() > input.memorySlots){
        throw ExceededMemoryError("Quantity of initial pages can't be more then memory slots!");
    }

    if(input.memorySlots == 0){
        throw ZeroMemorySlotsError("Memory can't be zero!");
    }

    m_inputData = std::make_unique<paging::SimulationData>(input);
}