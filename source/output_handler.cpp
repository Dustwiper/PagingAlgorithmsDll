#include <iostream>
#include "output_handler.hpp"
#include "initialization_error.hpp"

template <typename T>
void print(const T& container){
    for(auto i : container){
        std::cout << i << " ";
    }

    std::cout << '\n';
}

void OHandler::showResult(std::vector<paging::SimulationResult>& executionResult) const{
    int nPageFaults{0};

    for(auto i = executionResult.begin(); i < executionResult.end()-1; ++i){
        if(i->isPageFault) {nPageFaults += 1;}


        std::cout << "Next page: " << i->incomingPage;
        std::cout << " Page fault: " << (i->isPageFault ? "Yes|" : "No |");  

        std::cout << " Memory: ";
        print(i->memoryState);
    }

    std::cout << "Final Memory Status: "; 
    print(executionResult.back().memoryState);
    std::cout << "Page Faults: " << nPageFaults << std::endl; 

}
