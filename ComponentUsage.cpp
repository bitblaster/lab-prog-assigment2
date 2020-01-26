//
// Created by mozzicator on 16/01/20.
//

#include "Component.h"
#include "ComponentUsage.h"

ComponentUsage::ComponentUsage(const Component &component, const std::string nameInModel, int quantity)
        : component{component}, name_in_model{nameInModel}, quantity{quantity} {

}
