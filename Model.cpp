//
// Created by mozzicator on 16/01/20.
//
#include <ostream>
#include "Model.h"

using namespace std;

ostream& operator <<(ostream& stream, const Model& model) {
    stream << model.get_id() << "," << model.get_name() << ",price:" << model.get_price() << ",components:" << model.get_components().size();
    return stream;
}
