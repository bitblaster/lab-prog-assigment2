//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_PART_H
#define INC_PART_H

#include <string>

class Part {
protected:
    int id;
    std::string name;

    Part(const int entity_id, const std::string &entity_name) : id {entity_id}, name {entity_name} {}

public:
    int get_id() const {
        return id;
    }

    const std::string &get_name() const {
        return name;
    }
};


#endif //INC_PART_H
