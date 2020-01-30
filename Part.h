/**
 * Part.h
 * Scopo: definire una superclasse per le classi Model e Component
 *
 * @author Giacomo Seno, 1187124
 * @version 1.0 29/01/20
 */

#ifndef INC_PART_H
#define INC_PART_H


#include <string>
#include <utility>

class Part {
protected:
    int id;
    std::string name;

    /**
     * Costruttore di Part
     * protected perché deve venir chiamato solamente dalle sue sottoclassi
     * @param entity_id
     * @param entity_name
     */
    Part(int entity_id, std::string entity_name) : id {entity_id}, name { std::move(entity_name) } {}

public:

    /**
     * @return id dell'oggetto
     */
    int get_id() const {
        return id;
    }

    /**
     * @return name dell'oggetto
     */
    const std::string &get_name() const {
        return name;
    }
};


#endif //INC_PART_H
