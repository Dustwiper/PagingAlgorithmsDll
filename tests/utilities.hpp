// Функция для подсчёта количества страничных прерываний. 
#include <memory>
#include "simulation_data.hpp"

inline int countPageFaults(std::vector<std::unique_ptr<paging::SimulationResult>>& res){
     int nPageFaults{0};

    for(auto i = res.begin(); i < res.end(); ++i){
        if((*i)->isPageFault) {nPageFaults += 1;}
    }

    return nPageFaults;
}