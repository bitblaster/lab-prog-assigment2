/**
 * Implementazione della classe Model
 *
 * @author Giacomo Seno
 * @version 1.0 29/01/20
 */

#include <ostream>
#include "Model.h"

using namespace std;

Model::Model(const int id, const string name, const double price)
    : Part(id, name), price {price}, components(), max_delivery_months {0} { }

ostream& operator <<(ostream& stream, const Model& model) {
    stream << "id modello: " << model.get_id() << ", nome: " << model.get_name() << ", prezzo:" << model.get_price() << ", num componenti:" << model.get_components().size();
    return stream;
}
