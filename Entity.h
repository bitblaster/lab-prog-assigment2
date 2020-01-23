//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_ENTITY_H
#define INC_ENTITY_H

#include <string>

class Entity {
protected:
    int id;
    std::string name;

    Entity() = default;
    Entity(const int entity_id, const std::string &entity_name) : id {entity_id}, name {entity_name} {}
    //Entity(const Entity &) = default;
    //Entity(Entity &&) = default;

public:
    int get_id() const {
        return id;
    }

    const std::string &get_name() const {
        return name;
    }

    //Entity& operator=(const Entity &) = default;
};


#endif //INC_ENTITY_H
