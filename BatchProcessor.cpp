//
// Created by mozzicator on 26/01/20.
//

#include "parsers/ComponentParser.h"
#include "parsers/ModelListParser.h"
#include "BatchProcessor.h"

using namespace parsers;

void BatchProcessor::load_components(const std::string &componentsFile) {
    ComponentParser cp(componentsFile, component_map);
    cp.parse();
}

void BatchProcessor::load_models(const std::string &modelsFile) {
    ModelListParser mlp(modelsFile, model_map, component_map);
    mlp.parse();
}

void BatchProcessor::append_order(const Order &order) {
    order_queue.push(order);
}

void BatchProcessor::process_batch() {

    ++batch_period;
}

