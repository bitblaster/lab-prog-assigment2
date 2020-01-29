/**
 * Implementazione della classe ComponentUsage
 *
 * @author Giacomo Seno
 * @version 1.0 29/01/20
 */

#include "ComponentUsage.h"

ComponentUsage::ComponentUsage(std::shared_ptr<const Component> component, const std::string nameInModel, unsigned int quantity)
        : component{component}, name_in_model{nameInModel}, quantity{quantity} { }
