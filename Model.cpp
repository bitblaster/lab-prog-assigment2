//
// Created by mozzicator on 16/01/20.
//
#include <ostream>
#include "Model.h"

using namespace std;

ostream& operator <<(ostream& stream, const Model& model) {
    stream << "Id modello: " << model.get_id() << ", nome: " << model.get_name() << ", prezzo:" << model.get_price() << ", num componenti:" << model.get_components().size();
    return stream;
}
