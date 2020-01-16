//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_02_APPROVVIGIONAMENTO_ENTITY_H
#define INC_02_APPROVVIGIONAMENTO_ENTITY_H

#include <string>

class Entity {
protected:
    const int id;
    const std::string name;

    Entity(int entity_id, std::string entity_name) : id {entity_id}, name {entity_name} {}

public:
    int getId() const {
        return id;
    }

    const std::string &getName() const {
        return name;
    }
};


#endif //INC_02_APPROVVIGIONAMENTO_ENTITY_H
