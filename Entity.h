//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_ENTITY_H
#define INC_ENTITY_H

#include <string>

class Entity {
protected:
    const int id;
    const std::string name;

    Entity(int entity_id, std::string entity_name) : id {entity_id}, name {entity_name} {}

public:
    int get_id() const {
        return id;
    }

    const std::string &get_name() const {
        return name;
    }
};


#endif //INC_ENTITY_H
